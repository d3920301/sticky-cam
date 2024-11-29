// Fill out your copyright notice in the Description page of Project Settings.


#include "StickyCamVolume.h"

// Sets default values
AStickyCamVolume::AStickyCamVolume(): BlendTimeTo(0), BlendTimeFrom(0), BlendFunction(VTBlend_Linear), ReturnType(EReturnType::LastCam)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Box Collider");
	BoxComponent->InitBoxExtent(FVector(100, 100, 100));
	RootComponent = BoxComponent;

	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	BoxComponent->SetGenerateOverlapEvents(true);

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AStickyCamVolume::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AStickyCamVolume::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AStickyCamVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStickyCamVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStickyCamVolume::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	// Do we need to check actor class AND if that class has the component? YES! It might be a subclass of Character, but not have the component.
	if (OtherActor->IsA(ClassToEffect) && OtherActor->FindComponentByClass<UStickyCamComponent>() && CameraPoint != nullptr)
	{
		UStickyCamComponent* StickyCamComponent = OtherActor->FindComponentByClass<UStickyCamComponent>();
		StickyCamComponent->SetNewPoint(CameraPoint, BlendTimeTo, BlendFunction);
	}
}

void AStickyCamVolume::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Check if actor is one we want to affect
	if (OtherActor->IsA(ClassToEffect) && OtherActor->FindComponentByClass<UStickyCamComponent>())
	{
		switch (ReturnType)
		{
		case EReturnType::None:
			UE_LOG(LogTemp, Display, TEXT("Hit None!"));
			OtherActor->FindComponentByClass<UStickyCamComponent>()->LastPoint = CameraPoint;
			break;
		case EReturnType::TransientNone:
			UE_LOG(LogTemp, Display, TEXT("Hit TransientNone!"));
			break;
		case EReturnType::LastCam:
			UE_LOG(LogTemp, Display, TEXT("Hit LastCam!"));
			if (OtherActor->FindComponentByClass<UStickyCamComponent>()->LastPoint == nullptr)
			{
				UE_LOG(LogScript, Error, TEXT("Last Point is NULL"));
			}
			else
			{
				OtherActor->FindComponentByClass<UStickyCamComponent>()->SetNewPoint(OtherActor->FindComponentByClass<UStickyCamComponent>()->LastPoint, BlendTimeFrom, BlendFunction);
				OtherActor->FindComponentByClass<UStickyCamComponent>()->LastPoint = CameraPoint;
			}
			break;
		case EReturnType::TransientLastCam:
			UE_LOG(LogTemp, Display, TEXT("Hit TransientLastCam!"));
			if (OtherActor->FindComponentByClass<UStickyCamComponent>()->LastPoint == nullptr)
			{
				UE_LOG(LogScript, Error, TEXT("Last Point is NULL"));
			}
			else
			{
				OtherActor->FindComponentByClass<UStickyCamComponent>()->SetNewPoint(OtherActor->FindComponentByClass<UStickyCamComponent>()->LastPoint, BlendTimeFrom, BlendFunction);
			}
			break;
		case EReturnType::FollowCam:
			UE_LOG(LogTemp, Display, TEXT("Hit FollowCam!"));
			if (!OtherActor->FindComponentByClass<UStickyCamComponent>()->bAllowUseOfCameraComponent)
			{
				UE_LOG(LogScript, Error, TEXT("Use of Camera Component is not allowed. Check actor component."));
			}
			else
			{
				OtherActor->FindComponentByClass<UStickyCamComponent>()->SetCamCompAsActiveCam(BlendTimeFrom, BlendFunction);
				OtherActor->FindComponentByClass<UStickyCamComponent>()->LastPoint = CameraPoint;
			}
			break;
		case EReturnType::TransientFollowCam:
			UE_LOG(LogTemp, Display, TEXT("Hit TransientFollowCam!"));
			if (!OtherActor->FindComponentByClass<UStickyCamComponent>()->bAllowUseOfCameraComponent)
			{
				UE_LOG(LogScript, Error, TEXT("Use of Camera Component is not allowed. Check actor component."));
			}
			else
			{
				OtherActor->FindComponentByClass<UStickyCamComponent>()->SetCamCompAsActiveCam(BlendTimeFrom, BlendFunction);
			}
			break;
		default:
			UE_LOG(LogScript, Error, TEXT("Unhandled case!"));
			break;
		}
	}
}

