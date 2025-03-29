// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class A_HUMAN_SURVIVAL_312_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

	public: // Public class
		
		UFUNCTION(BlueprintImplementableEvent) // Unreal Function
			void UpdateBars(float health1, float hunger1, float stamina1); // Function to update Player UI bars.
	
};
