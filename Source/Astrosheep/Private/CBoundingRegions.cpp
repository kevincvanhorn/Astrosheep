// Fill out your copyright notice in the Description page of Project Settings.


#include "Astrosheep/Public/CBoundingRegions.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACBoundingRegions::ACBoundingRegions()
{
	
}

// Called when the game starts or when spawned
void ACBoundingRegions::BeginPlay()
{
	Super::BeginPlay();

	TArray<UActorComponent*> ActorComponents;
	ActorComponents = GetComponentsByClass(UBoxComponent::StaticClass());
	for (UActorComponent* ActorComp : ActorComponents) {
		BoxComponents.Emplace(Cast<UBoxComponent>(ActorComp));
	}
}

float ACBoundingRegions::GetBoundedOrigin(const FVector & QueryPoint)
{
	for (int i = 0; i < BoxComponents.Num(); ++i) {
		if (UKismetMathLibrary::IsPointInBox(QueryPoint, BoxComponents[i]->GetComponentLocation(), BoxComponents[i]->GetScaledBoxExtent())) {
			if (i < BoundingOrigins.Num()) {
				return BoundingOrigins[i];
			}
			else { break; }
		}
	}
	return QueryPoint.Z;
}
