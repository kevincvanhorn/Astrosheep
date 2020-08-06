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
	PanMidPoint = 0.25f;
	PanMidPointConvInv = 1.0f / (1.0f - PanMidPoint);
}

void ACPawn::BeginPlay()
{
	Super::BeginPlay();
	CController = Cast<ACPlayerController>(Controller);

	int32 ViewportX, ViewportY;
	if (CController) {
		CController->GetViewportSize(ViewportX, ViewportY);
	}
	ViewportXHalfInv = 1.0f / ((float)ViewportX / 2.0f);
	ViewportMidX = ViewportX / 2.0f;
}

void ACPawn::MouseAxisX(float AxisValue)
{
	SetActorLocation(GetActorLocation() + AxisValue * FVector::RightVector * CameraPanSpeed);
}

void ACPawn::DoSelectedAction() {
	if (ActiveSheep && CController) {
		float LocX = 0, LocY = 0;
		CController->GetMousePosition(LocX, LocY);
		FVector WorldDir, WorldLoc;
		UGameplayStatics::DeprojectScreenToWorld(CController, FVector2D(LocX, LocY), WorldLoc, WorldDir);

		float Length = -1*(FVector::DotProduct(WorldLoc, FVector(-1, 0, 0))) / FVector::DotProduct(-WorldDir, FVector(-1, 0, 0));
		WorldLoc = WorldLoc - WorldDir*Length;
		ActiveSheep->MoveToLocation(WorldLoc);
	}
}

void ACPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CController) {
		CController->GetMousePosition(MouseX, MouseY);
		float AxisValue = -1 * (ViewportMidX - MouseX) * ViewportXHalfInv; // -1 to 1
		if (FMath::Abs(AxisValue) >= PanMidPoint) {
			AxisValue = (AxisValue - PanMidPoint*FMath::Sign(AxisValue)) * PanMidPointConvInv;
			SetActorLocation(GetActorLocation() + AxisValue * FVector::RightVector * CameraPanSpeed);
		}
	}
}

void ACPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	InputComponent->BindAction("MouseR", EInputEvent::IE_Released, this, &ACPawn::DoSelectedAction);
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
