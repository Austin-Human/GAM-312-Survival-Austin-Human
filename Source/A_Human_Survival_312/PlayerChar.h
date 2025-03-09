// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Included files.
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
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
};
