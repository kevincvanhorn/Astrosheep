// Fill out your copyright notice in the Description page of Project Settings.


#include "Astrosheep/Public/CLevelScriptActor.h"
#include "Astrosheep/Public/CBoundingRegions.h"

ACLevelScriptActor::ACLevelScriptActor() {

}

float ACLevelScriptActor::GetBoundedOrigin(const FVector& QueryPoint)
{
	if (NavBoundingRegions) {
		return NavBoundingRegions->GetBoundedOrigin(QueryPoint);
	}
	return QueryPoint.Z;
}
