// Fill out your copyright notice in the Description page of Project Settings.


#include "CSheepPawn.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ACSheepPawn::ACSheepPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	if (SkeletalMeshComp) {
		SkeletalMeshComp->SetupAttachment(RootComponent);
	}
}

// Called when the game starts or when spawned
void ACSheepPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACSheepPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACSheepPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

