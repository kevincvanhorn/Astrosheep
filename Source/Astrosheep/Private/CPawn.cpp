// Fill out your copyright notice in the Description page of Project Settings.


#include "CPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "..\Public\CPawn.h"
#include "Astrosheep/Public/CPlayerController.h"
#include "Astrosheep/Public/CSheepPawn.h"
#include "Astrosheep/Public/CSheepAIController.h"
#include "Astrosheep/Public/CSheepCharacter.h"

// Sets default values
ACPawn::ACPawn()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	if (SpringArm) {
		SpringArm->SetupAttachment(RootComponent);
		SpringArm->bEnableCameraLag = false;
	}

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	if (Camera) {
		Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	}

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
	CameraPanSpeed = 1.0f;
	bCameraPanning = false;
}

void ACPawn::BeginPlay()
{
	Super::BeginPlay();
	CController = Cast<ACPlayerController>(Controller);
}

void ACPawn::PanCamera(float AxisValue)
{
	SetActorLocation(GetActorLocation() + AxisValue*FVector::RightVector*CameraPanSpeed);
}

void ACPawn::MouseAxisX(float AxisValue)
{
	// TODO: Camera should continue panning at screen edges. (Query mouse position)
	if (bCameraPanning) {
		SetActorLocation(GetActorLocation() + AxisValue * FVector::RightVector * CameraPanSpeed);
	}
}

void ACPawn::StartPanning()
{
	bCameraPanning = true;
}

void ACPawn::StopPanning()
{
	bCameraPanning = false;
}

void ACPawn::DoSelectedAction() {
	if (ActiveSheep && CController) {
		float LocX = 0, LocY = 0;
		CController->GetMousePosition(LocX, LocY);
		FVector WorldDir, WorldLoc = FVector::ZeroVector;
		UGameplayStatics::DeprojectScreenToWorld(CController, FVector2D(LocX, LocY), WorldLoc, WorldDir);
		ActiveSheep->MoveToLocation(WorldLoc);
	}
}

void ACPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("MouseR", EInputEvent::IE_Pressed, this, &ACPawn::StartPanning);
	InputComponent->BindAction("MouseR", EInputEvent::IE_Released, this, &ACPawn::StopPanning);
	InputComponent->BindAction("MouseR", EInputEvent::IE_Released, this, &ACPawn::DoSelectedAction);

	InputComponent->BindAxis("Pan", this, &ACPawn::PanCamera);
	InputComponent->BindAxis("MouseX", this, &ACPawn::MouseAxisX);
}


void ACPawn::SetActiveSheep(ACSheepCharacter* SheepIn) {
	ActiveSheep = SheepIn;
}

ACSheepCharacter* ACPawn::GetActiveSheep()
{
	return ActiveSheep;
}

void ACPawn::DeselectSheep() {
	ActiveSheep = nullptr;
}
