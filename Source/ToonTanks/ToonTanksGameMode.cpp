// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"


void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	UE_LOG(LogTemp, Warning, TEXT("A Pawn Died"));

	if (DeadActor == Tank) {
		GameOver(false);
		Tank->DisableInput(Tank->GetTankPlayerController());
		Tank->GetTankPlayerController()->bShowMouseCursor = false;
		Tank->HandleDestruction();
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor)){
		DestroyedTower->HandleDestruction();
		if (--TowersInWorld <= 0) {
			GameOver(true);
		}
	}
}

void AToonTanksGameMode::BeginPlay() {
	Super::BeginPlay();
	HandleGameStart();


}

void AToonTanksGameMode::HandleGameStart() {
	TowersInWorld = GetTowersInWorld();

	Tank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(GetWorld()->GetFirstPlayerController());

	StartGame();

	if (ToonTanksPlayerController) {
		ToonTanksPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);
		GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
	}
}

int32 AToonTanksGameMode::GetTowersInWorld() {
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
	return Towers.Num();
}