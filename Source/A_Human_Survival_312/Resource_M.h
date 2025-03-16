// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Resource_M.generated.h"

UCLASS()
class A_HUMAN_SURVIVAL_312_API AResource_M : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResource_M();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere) // Unreal Property
		FString resourceName = "Wood"; // Resource name

	UPROPERTY(EditAnywhere) // Unreal Property
		int resourceAmount = 5; // Resource amount per object

	UPROPERTY(EditAnywhere) // Unreal Property
		int totalResources = 100; // Total amount of this resource player can carry

	UPROPERTY() // Unreal Property
		FText tempText; // Temporary text

	UPROPERTY(EditAnywhere) // Unreal Property
		UTextRenderComponent* ResourceNameTxt; // Render the temporary text in game

	UPROPERTY(EditAnywhere) // Unreal Property
		UStaticMeshComponent* Mesh; // Render the mesh model in game

};
