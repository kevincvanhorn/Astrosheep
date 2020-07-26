// Fill out your copyright notice in the Description page of Project Settings.


#include "CSheepAIController.h"
#include "..\Public\CSheepAIController.h"
#include "AI/NavigationSystemBase.h"
#include "NavigationSystem.h"
#include "Astrosheep/Public/CSheepCharacter.h"

ACSheepAIController::ACSheepAIController() {
}

void ACSheepAIController::BeginPlay()
{
	Super::BeginPlay();
	Sheep = (ACSheepCharacter*)GetPawn();
	Navigation = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
}

void ACSheepAIController::RequestMoveToLocation(FVector Location)
{
	// Move if a sheep is selected
	if (Sheep && Navigation) {
		FNavLocation ProjectedPoint;
		bool bCanRequestMove = Navigation->ProjectPointToNavigation(Location, ProjectedPoint);
		if (bCanRequestMove) {
			MoveToLocation(ProjectedPoint.Location);
		}
	}
}

void ACSheepAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
}