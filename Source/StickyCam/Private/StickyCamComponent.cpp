// Fill out your copyright notice in the Description page of Project Settings.


#include "StickyCamComponent.h"

// Sets default values for this component's properties
UStickyCamComponent::UStickyCamComponent(): bAllowUseOfCameraComponent(true), bSetupCorrectly(true)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStickyCamComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	SetupCheck();

	// Assign Controller stuff
	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
}


// Called every frame
void UStickyCamComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStickyCamComponent::SetCamCompAsActiveCam(float BlendTime, EViewTargetBlendFunction BlendFunction)
{
	// Does this work?
	if (PlayerController->IsLookInputIgnored())
	{
		PlayerController->ResetIgnoreLookInput();
		UE_LOG(LogTemp, Warning, TEXT("Look input unlocked"));
	}
	
	PlayerController->SetViewTargetWithBlend(GetOwner(), BlendTime);
}

void UStickyCamComponent::SetNewPoint(AStickyCamPoint* NewPoint, float BlendTime, EViewTargetBlendFunction BlendFunction)
{
	// Does this work?
	if (!PlayerController->IsLookInputIgnored())
	{
		PlayerController->SetIgnoreLookInput(true);
		UE_LOG(LogTemp, Warning, TEXT("Look input locked"));
	}

	double OldViewTargetRotYaw = PlayerController->GetViewTarget()->GetActorRotation().Yaw;

	PlayerController->SetViewTargetWithBlend(NewPoint, BlendTime);

	double NewViewTargetRotYaw = PlayerController->GetViewTarget()->GetActorRotation().Yaw;

	// It looks like NewViewTargetRotYaw - OldViewTargetRotYaw just works? @TODO THE MATHS DOES NOT WORK!
	FRotator NewControlRotation = FRotator(PlayerController->GetControlRotation().Pitch, /*PlayerController->GetControlRotation().Yaw*/ NewViewTargetRotYaw, PlayerController->GetControlRotation().Roll);
	PlayerController->SetControlRotation(NewControlRotation);

}

void UStickyCamComponent::SetupCheck()
{
	if (!GetOwner()->GetComponentByClass<UCameraComponent>())
	{
		bSetupCorrectly = false;

		UE_LOG(LogScript, Warning, TEXT("No Camera component found on owner. Please attach one to use this actor with the plugin."));
	}
	if (!GetOwner()->GetComponentByClass<USpringArmComponent>())
	{
		bSetupCorrectly = false;

		UE_LOG(LogScript, Warning, TEXT("No Spring Arm component found on owner. Please attach one to use this actor with the plugin."));
	}

	CameraComponent = GetOwner()->GetComponentByClass<UCameraComponent>();
	SpringArmComponent = GetOwner()->GetComponentByClass<USpringArmComponent>();

	if (CameraComponent->GetAttachParent() != SpringArmComponent)
	{
		// Set SetupCorrectly even though we have valid components to show the user the plugin's functionality wont work unless setup correctly 
		bSetupCorrectly = false;

		UE_LOG(LogScript, Warning, TEXT("Camera component is not a child of Spring Arm component. Please make the Camera a child of the Spring Arm to use this actor with the plugin"));
	}

	// Check if we're still good to go
	if (bSetupCorrectly)
	{
		UE_LOG(LogTemp, Display, TEXT("StickyCam component setup correctly"));
	}
}

