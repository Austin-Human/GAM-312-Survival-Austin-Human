// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Included files.
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Resource_M.h"
#include "Kismet/GameplayStatics.h"
#include "BuildingPart.h"
#include "PlayerWidget.h"
#include "ObjectiveWidget.h"
#include "PlayerChar.generated.h"

UCLASS()
class A_HUMAN_SURVIVAL_312_API APlayerChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION() // Unreal Function
		void ForwardandBackward(float axisValue); // Player forward/backward movement.

	UFUNCTION() // Unreal Function
		void LeftandRight(float axisValue); // Player left/right movement.

	UFUNCTION() // Unreal Function
		void StartJump(); // Player jump start.

	UFUNCTION() // Unreal Function
		void StopJump(); // Player stop jumping.

	UFUNCTION() // Unreal Function
		void FindObject(); // Player ability to detect and interact with/pick up objects.

	UPROPERTY(VisibleAnywhere) // Unreal Property
		UCameraComponent* PlayerCamComp; // Player camera. This is where the player sees from.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats") // Unreal Property
		float Health = 100.0f; // Player Health stat

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats") // Unreal Property
		float Stamina = 100.0f; // Player Stamina stat

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats") // Unreal Property
		float Hunger = 100.0f; // Player Hunger stat

	UPROPERTY(EditAnywhere, Category = "Resources") // Unreal Property
		int Wood; // Stores player's wood resources

	UPROPERTY(EditAnywhere, Category = "Resources") // Unreal Property
		int Stone; // Stores player's stone resources

	UPROPERTY(EditAnywhere, Category = "Resources") // Unreal Property
		int Berry; // Stores player's berry resources

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources") // Unreal Property
		TArray<int> ResourceArray; // Stores total count of player's resources

	UPROPERTY(EditAnywhere, Category = "Resources") // Unreal Property
		TArray<FString> ResourceNameArray; // Total resources

	UPROPERTY(EditAnywhere, Category = "HitMarker") // Unreal Property
		UMaterialInterface* hitDecal; // Sets material to use

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Supplies") // Unreal Property
		TArray<int> BuildingArray; // Array for what the player can build

	UPROPERTY() // Unreal Property
		bool isBuilding; // Boolean for player building status
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) // Unreal Property
		TSubclassOf<ABuildingPart> BuildPartClass; // Used for determining what player wants to build

	UPROPERTY() // Unreal Property
		ABuildingPart* spawnedPart; // Spawns the correct part relative to what the player wants

	UPROPERTY(EditAnywhere, BlueprintReadWrite) // Unreal Function
		UPlayerWidget* playerUI; // Set widget to use for player UI

	UPROPERTY(EditAnywhere, BlueprintReadWrite) // Unreal Property
		UObjectiveWidget* objWidget; // Sets the objective widget

	UPROPERTY() // Unreal Property
		float objectsBuilt; // Float for total objects built

	UPROPERTY() // Unreal Property
		float matsCollected; // Float for total materials collected

	UFUNCTION(BlueprintCallable) // Unreal Function
		void SetHealth(float amount); // Function call to SetHealth

	UFUNCTION(BlueprintCallable) // Unreal Function
		void SetHunger(float amount); // Function call to SetHunger

	UFUNCTION(BlueprintCallable) // Unreal Function
		void SetStamina(float amount); // Function call to SetStamina

	UFUNCTION() // Unreal Function
		void DecreaseStats(); // Function call to DecreaseStats

	UFUNCTION() // Unreal Function
		void GiveResource(float amount, FString resourceType); // Adds resources to player's inventory via function call to GiveResources

	UFUNCTION(BlueprintCallable) // Unreal Function
		void UpdateResources(float woodAmount, float stoneAmount, FString buildingObject); // Function call to update player's current resources

	UFUNCTION(BlueprintCallable) // Unreal Function
		void SpawnBuilding(int buildingID, bool& isSuccess); // Function call to spawn, or "build", the building that the player wants to build

	UFUNCTION() // Unreal Function
		void RotateBuilding(); // Function call to allow player to rotate what they are building on input

};
