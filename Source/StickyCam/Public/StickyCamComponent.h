// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include <GameFramework/SpringArmComponent.h>
#include "Kismet/GameplayStatics.h"
#include "StickyCamPoint.h"
#include "TimerManager.h"
#include "StickyCamComponent.generated.h"

UENUM()
enum EReturnType
{
	None                UMETA(DisplayName = "Don't Change Camera"),
	TransientNone       UMETA(DisplayName = "Don't Change Camera - Don't Save Current Camera"),
	LastCam             UMETA(DisplayName = "Go To Last Camera"),
	TransientLastCam    UMETA(DisplayName = "Go To Last Cam - Don't Save Current Camera"),
	FollowCam	        UMETA(DisplayName = "Player's Follow Camera"),
	TransientFollowCam	UMETA(DisplayName = "Player's Follow Camera - Don't Save Current Camera")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class STICKYCAM_API UStickyCamComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStickyCamComponent();

	UPROPERTY(EditAnywhere, Category="StickyCam")
	bool bAllowUseOfCameraComponent;
	
	// Assumed true until we do checks to verify it's not
	bool bSetupCorrectly;

	// About actor
	APlayerController* PlayerController;
	// Components
	UCameraComponent* CameraComponent;
	USpringArmComponent* SpringArmComponent;
	// StickyCam
	AStickyCamPoint* LastPoint;

	// This is used for time limited points
	AStickyCamPoint* TempPointStorage;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Internal only
	void SetNewPointAfterSetTime(AStickyCamPoint* NewPoint, bool bIsTransient, EReturnType ReturnType, float BlendTime, EViewTargetBlendFunction BlendFunction);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Sticky Cam")
	void SetCamCompAsActiveCam(float BlendTime, EViewTargetBlendFunction BlendFunction);
	UFUNCTION(BlueprintCallable, Category = "Sticky Cam")
	void SetNewPoint(AStickyCamPoint* NewPoint, EReturnType ReturnType, float TimeLimit, float BlendTime, EViewTargetBlendFunction BlendFunction);

private:
	void SetupCheck();
};
