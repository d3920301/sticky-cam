// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "StickyCamComponent.h"
#include "StickyCamPoint.h"
#include "StickyCamVolume.generated.h"

UENUM()
enum EReturnType
{
	None                UMETA(DisplayName = "No Return Camera"),
	TransientNone       UMETA(DisplayName = "Camera Not Saved - No Return Camera"),
	LastCam             UMETA(DisplayName = "Last Camera"),
	TransientLastCam    UMETA(DisplayName = "Camera Not Saved - Return to Last Cam"),
	FollowCam	        UMETA(DisplayName = "Follow Camera"),
	TransientFollowCam	UMETA(DisplayName = "Camera Not Saved - Return to Follow Camera")
};

UCLASS()
class STICKYCAM_API AStickyCamVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStickyCamVolume();

	UPROPERTY(EditAnywhere, Category = "StickyCam")
	AStickyCamPoint* CameraPoint;
	// Blend
	UPROPERTY(EditAnywhere, Category = "StickyCam")
	float BlendTimeTo;
	UPROPERTY(EditAnywhere, Category = "StickyCam")
	float BlendTimeFrom;
	UPROPERTY(EditAnywhere, Category = "StickyCam")
	TEnumAsByte<EViewTargetBlendFunction> BlendFunction;
	// Return to previous camera after leaving the volume
	UPROPERTY(EditAnywhere, Category = "StickyCam")
	TEnumAsByte<EReturnType> ReturnType;

	// Default to Character class
	UPROPERTY(EditAnywhere, Category = "StickyCam")
	TSubclassOf<class ACharacter> ClassToEffect = ACharacter::StaticClass();

	UBoxComponent* BoxComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
