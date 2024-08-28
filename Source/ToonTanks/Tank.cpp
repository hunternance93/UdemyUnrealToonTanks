// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ATank::ATank()
{

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::Move(float Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Move C++: %f"), Value);
	// Calculate the direction to move the tank
	FVector MoveDirection = FVector(Value * GetWorld()->DeltaTimeSeconds * MoveSpeed, 0, 0);
	// Move the tank
	AddActorLocalOffset(MoveDirection, true);
}

void ATank::Turn(float Value) {
	// Calculate the direction to move the tank
	FRotator Rotation = FRotator(0, Value * GetWorld()->DeltaTimeSeconds * TurnRate, 0);
	// Move the tank
	AddActorLocalRotation(Rotation, true);
}