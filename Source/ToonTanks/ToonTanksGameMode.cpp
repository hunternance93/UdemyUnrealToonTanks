// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Tank.h"
#include "Tower.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	UE_LOG(LogTemp, Warning, TEXT("A Pawn Died"));

	if (DeadActor == Tank) {
		Tank->DisableInput(Tank->GetTankPlayerController());
		Tank->GetTankPlayerController()->bShowMouseCursor = false;
		Tank->HandleDestruction();
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor)){
		DestroyedTower->HandleDestruction();
	}
}

void AToonTanksGameMode::BeginPlay() {
	Super::BeginPlay();

	Tank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}