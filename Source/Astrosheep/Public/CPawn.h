// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CPawn.generated.h"

UCLASS()
class ASTROSHEEP_API ACPawn : public APawn
{
	GENERATED_BODY()

public:
	ACPawn();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
		class UCameraComponent* Camera;

	//  INPUT MOVEMENT
	UFUNCTION()
		void MouseAxisX(float AxisValue);

	UFUNCTION()
		void DoSelectedAction();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float CameraPanSpeed;

protected:
	class ACPlayerController* CController;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// ACTIVE SHEEP
public:
	void SetActiveSheep(class ACSheepCharacter* SheepIn);

	ACSheepCharacter* GetActiveSheep();

	void DeselectSheep();

protected:
	class ACSheepCharacter* ActiveSheep;


// PANNING
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float PanMidPoint;

private:
	float MouseX;
	float MouseY;
	float ViewportMidX;
	float ViewportXHalfInv;
	float PanMidPointConvInv;
};
