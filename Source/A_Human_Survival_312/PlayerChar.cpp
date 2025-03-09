// Fill out your copyright notice in the Description page of Project Settings.

// Included files.
#include "PlayerChar.h"

// Sets default values
APlayerChar::APlayerChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	PlayerCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera")); // Sets default player camera (where player sees from).
	PlayerCamComp->SetupAttachment(GetMesh(), "head"); // Attaches camera to mesh component. In this case, the player's point of view is from the head.
	PlayerCamComp->bUsePawnControlRotation = true; // Allows camera to rotate with player input.

}

// Called when the game starts or when spawned
void APlayerChar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Directional movement inputs.
	PlayerInputComponent->BindAxis("ForwardandBackward", this, &APlayerChar::ForwardandBackward);
	PlayerInputComponent->BindAxis("LeftandRight", this, &APlayerChar::LeftandRight);

	// Rotational mouse axis inputs.
	PlayerInputComponent->BindAxis("LookUpDown", this, &APlayerChar::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookLeftRight", this, &APlayerChar::AddControllerYawInput);

	// Jump inputs.
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerChar::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerChar::StopJump);

	// Interaction input.
	PlayerInputComponent->BindAction("Interact1", IE_Released, this, &APlayerChar::FindObject);

}

void APlayerChar::ForwardandBackward(float axisValue) // Function for player to move forward and backward.
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, axisValue);
}

void APlayerChar::LeftandRight(float axisValue) // Function for player to move left and right.
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, axisValue);
}

void APlayerChar::StartJump() // Function for player to start jumping.
{
	bPressedJump = true; // When true, player is jumping. Can only jump so high before losing altitude.
}

void APlayerChar::StopJump() // Function for player to stop jumping.
{
	bPressedJump = false; // When false, player has stopped jumping. Set to false when player releases jump button.
						  // Will cause player to fall prematurely if not at max altitude.
}

void APlayerChar::FindObject() // Function for player object interaction.
{
	// CURRENTLY EMPTY
}
