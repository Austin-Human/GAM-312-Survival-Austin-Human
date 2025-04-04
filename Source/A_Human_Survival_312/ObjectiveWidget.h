// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObjectiveWidget.generated.h"

/**
 * 
 */
UCLASS()
class A_HUMAN_SURVIVAL_312_API UObjectiveWidget : public UUserWidget
{
	GENERATED_BODY()

	public:

		UFUNCTION(BlueprintImplementableEvent) // Unreal Function
			void UpdateMatOBJ(float matsCollected); // Function to update material objective progress.

		UFUNCTION(BlueprintImplementableEvent) // Unreal Function
			void UpdateBuildOBJ(float objectsBuilt); // Function to update building objective progress.
	
};
