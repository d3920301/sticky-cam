// Fill out your copyright notice in the Description page of Project Settings.


#include "StickyCamPoint.h"

// Sets default values
AStickyCamPoint::AStickyCamPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Viewfinder Camera");
	RootComponent = CameraComponent;
}

// Called when the game starts or when spawned
void AStickyCamPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStickyCamPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
