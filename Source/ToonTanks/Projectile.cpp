// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/DamageType.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->InitialSpeed = 2000.f;
	ProjectileMovementComponent->MaxSpeed = 2000.f;

	//ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	auto MyOwner = GetOwner();
	if (!MyOwner) {
		Destroy();
		return;
	}
	auto MyOwnerInstigator = MyOwner->GetInstigatorController();

	if (OtherActor && OtherActor != this && OtherActor != MyOwner) {
		//FDamageEvent Event = new FDamageEvent(UDamageType::StaticClass());
		FDamageEvent Event(UDamageType::StaticClass());
		OtherActor->TakeDamage(Damage, Event, MyOwnerInstigator, this);
		if (HitParticles) UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, GetActorLocation());
	}
	Destroy();
}

