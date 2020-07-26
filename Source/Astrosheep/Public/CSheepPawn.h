// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CSheepPawn.generated.h"

UCLASS()
class ASTROSHEEP_API ACSheepPawn : public APawn
{
	GENERATED_BODY()

public:
	ACSheepPawn();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class USkeletalMeshComponent* SkeletalMeshComp;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
