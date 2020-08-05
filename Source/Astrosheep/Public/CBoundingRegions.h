// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBoundingRegions.generated.h"

UCLASS()
class ASTROSHEEP_API ACBoundingRegions : public AActor
{
	GENERATED_BODY()
	
public:	
	ACBoundingRegions();

protected:
	virtual void BeginPlay() override;

public:
	/** Find the contained bounding box and get it's stored origin value. */
	float GetBoundedOrigin(const FVector& QueryPoint);

protected:
	/** Z value that defines the expected level of the navigational volume in a region mapped to NavBoundingRegions. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<float> BoundingOrigins;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<class UBoxComponent*> BoxComponents;
};
