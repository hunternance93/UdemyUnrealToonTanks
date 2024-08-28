// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"



void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (PlayerTank) {
		float Distance = FVector::Dist(PlayerTank->GetActorLocation(), GetActorLocation());
		if (Distance < FireRange) {
			RotateTurret(PlayerTank->GetActorLocation());
		}
	}
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
}