// Fill out your copyright notice in the Description page of Project Settings.

#include "CSheepCharacter.h"
#include "CSheepAIController.h"
#include "..\Public\CSheepCharacter.h"
#include "Astrosheep/Public/CPlayerController.h"
#include "Astrosheep/Public/CPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Astrosheep/Public/CLevelScriptActor.h"

// Sets default values
ACSheepCharacter::ACSheepCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	bSelected = false;
	XMoveDepth = 0;
}

// Called when the game starts or when spawned
void ACSheepCharacter::BeginPlay()
{
	Super::BeginPlay();

	LevelScriptActor = (ACLevelScriptActor*)(GetWorld()->GetLevelScriptActor());
	MovementComponent = GetCharacterMovement();
	SheepController = (ACSheepAIController*)Controller;
	CPawn = (ACPawn*)UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	OnClicked.AddUniqueDynamic(this, &ACSheepCharacter::OnActorClicked);
}

void ACSheepCharacter::OnActorClicked(AActor* Target, FKey ButtonPressed)
{
	// TODO: should unselect on click anywhere else
	if (!CPawn) { return; }
	if (!bSelected) {
		OnSelected();
		CPawn->SetActiveSheep(this); // TODO: move this to a playercontroller action
	}
	else {
		OnDeselected();
		CPawn->DeselectSheep();
	}
}

void ACSheepCharacter::OnSelected()
{
	UE_LOG(LogTemp, Warning, TEXT("Selected!"));
	if (CPawn) {
		CPawn->SetActiveSheep(this);
	}
	GetMesh()->SetRenderCustomDepth(true);
	bSelected = true;
}

void ACSheepCharacter::OnDeselected()
{
	if (CPawn) {
		CPawn->DeselectSheep();
	}
	GetMesh()->SetRenderCustomDepth(false);
	bSelected = false;
}

void ACSheepCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACSheepCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACSheepCharacter::MoveToLocation(FVector& Location) {
	if (SheepController) {
		//UKismetSystemLibrary::DrawDebugSphere(GetWorld(), Location, 100, 12, FLinearColor::Green, 1, 1);
		//UKismetSystemLibrary::DrawDebugSphere(GetWorld(), FVector(XMoveDepth, Location.Y, Location.Z), 100, 12, FLinearColor::Blue, 1, 1);
		
		FVector RequestedLocation = FVector(XMoveDepth, Location.Y, Location.Z);
		
		if (LevelScriptActor) {
			float Z = LevelScriptActor->GetBoundedOrigin(RequestedLocation);
			RequestedLocation.Z = Z;
		}

		SheepController->RequestMoveToLocation(RequestedLocation);
	}
}

