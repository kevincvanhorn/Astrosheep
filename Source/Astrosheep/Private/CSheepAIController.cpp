// Fill out your copyright notice in the Description page of Project Settings.


#include "CSheepAIController.h"
#include "Astrosheep/Public/CSheepAIController.h"
#include "AI/NavigationSystemBase.h"
#include "NavigationSystem.h"
#include "Astrosheep/Public/CSheepCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

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
		UKismetSystemLibrary::DrawDebugSphere(GetWorld(), Location, 100, 12, FLinearColor::Green, 1, 1);
		bool bCanRequestMove = Navigation->ProjectPointToNavigation(Location, ProjectedPoint);
		UKismetSystemLibrary::DrawDebugSphere(GetWorld(), ProjectedPoint.Location, 100, 12, FLinearColor::Red, 1, 1);
		if (bCanRequestMove) {
			MoveToLocation(ProjectedPoint.Location);
		}
	}
}

void ACSheepAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
}