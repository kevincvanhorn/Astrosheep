// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "CLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class ASTROSHEEP_API ACLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:

	ACLevelScriptActor();

public:
	/** Find the contained bounding box and get it's stored origin value. */
	float GetBoundedOrigin(const FVector& QueryPoint);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class ACBoundingRegions* NavBoundingRegions;
};
