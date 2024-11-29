// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include <GameFramework/SpringArmComponent.h>
#include "Kismet/GameplayStatics.h"
#include "StickyCamPoint.h"
#include "StickyCamComponent.generated.h"


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


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetCamCompAsActiveCam(float BlendTime = 0, EViewTargetBlendFunction BlendFunction = VTBlend_Linear);
	void SetNewPoint(AStickyCamPoint* NewPoint, float BlendTime = 0, EViewTargetBlendFunction BlendFunction = VTBlend_Linear);

private:
	void SetupCheck();
};
