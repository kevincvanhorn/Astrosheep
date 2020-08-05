// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CSheepAIController.generated.h"

/**
 * 
 */
UCLASS()
class ASTROSHEEP_API ACSheepAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ACSheepAIController();

	virtual void BeginPlay() override;

	UFUNCTION()
		void RequestMoveToLocation(FVector Location);

protected:

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

protected:
	class ACSheepCharacter* Sheep;
	
	class UNavigationSystemV1* Navigation;
};