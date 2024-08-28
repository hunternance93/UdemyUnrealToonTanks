// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Pawn Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	void RotateTurret(FVector LookAtTarget);


private:
	UPROPERTY(VisibleAnywhere, Category = "Pawn Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, Category = "Pawn Components")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, Category = "Pawn Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	float TurretRotationSpeed = 18.f;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

};
