// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CSheepCharacter.generated.h"

UCLASS()
class ASTROSHEEP_API ACSheepCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACSheepCharacter();

protected:
	virtual void BeginPlay() override;
	
protected:
	UCharacterMovementComponent* MovementComponent;

	class ACSheepAIController* SheepController;
	class ACPawn* CPawn;

protected:
	UFUNCTION()
		void OnActorClicked(AActor* Target, FKey ButtonPressed);

	void OnSelected();

	void OnDeselected();

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	bool bSelected;

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		float XMoveDepth;
	
	void MoveToLocation(FVector& Location);
};
