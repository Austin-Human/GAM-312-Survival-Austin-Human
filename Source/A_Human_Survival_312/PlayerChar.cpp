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

// Called when the game starts or when spawned.
void APlayerChar::BeginPlay()
{
	Super::BeginPlay();

	// In-game tick timer
	FTimerHandle StatsTimerHandle; // Tick timer object
	GetWorld()->GetTimerManager().SetTimer(StatsTimerHandle, this, & APlayerChar::DecreaseStats, 2.0f, true); // Decreases stat values over time.
	

	BuildingArray.SetNum(3); // Sets number of building types that can be built by the player.
	ResourceArray.SetNum(3); // Sets number of item types that can be in the player's inventory.
	ResourceNameArray.Add(TEXT("Wood")); // Adds wood as a type of item the player can carry.
	ResourceNameArray.Add(TEXT("Stone")); // Adds stone as a type of item the player can carry.
	ResourceNameArray.Add(TEXT("Berry")); // Adds berries as a type of item the player can carry.
}

// Called every frame
void APlayerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	playerUI->UpdateBars(Health, Hunger, Stamina); // Updates player UI bars with current stats.

	if (isBuilding) { // Check if the player is trying to build.

		if (spawnedPart) {

			FVector StartLocation = PlayerCamComp->GetComponentLocation();
			FVector Direction = PlayerCamComp->GetForwardVector() * 400.0f;
			FVector EndLocation = StartLocation + Direction;
			spawnedPart->SetActorLocation(EndLocation);

		}

	}

}

// Called to bind functionality to input.
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

	// Rotation input.
	PlayerInputComponent->BindAction("RotateItem", IE_Released, this, &APlayerChar::RotateBuilding);
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
	
	// Where the player can interact from and how interaction is checked.
	FHitResult HitResult;
	FVector StartLocation = PlayerCamComp->GetComponentLocation();
	FVector Direction = PlayerCamComp->GetForwardVector() * 800.0f;
	FVector EndLocation = StartLocation * Direction;

	// Parameters for what can be interacted with.
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = true;
	QueryParams.bReturnFaceIndex = true;

	if (!isBuilding) { // Check if the player is not trying to build.

		if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, QueryParams)) {

			AResource_M* HitResource = Cast<AResource_M>(HitResult.GetActor()); // Check which resource type was interacted with.

			if (Stamina > 5.0f) {

				if (HitResource) { // Activates if a resource object was interacted with.

					FString hitName = HitResource->resourceName; // Resource name to be added.
					int resourceValue = HitResource->resourceAmount; // Resource amount to be added.

					HitResource->totalResources = HitResource->totalResources - resourceValue;

					if (HitResource->totalResources > resourceValue) {

						// Add resource to player's inventory.
						GiveResource(resourceValue, hitName);

						// Display debug message.
						check(GEngine != nullptr);
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Resource Collected"));

						// Creates a mark where the player interacts.
						UGameplayStatics::SpawnDecalAtLocation(GetWorld(), hitDecal, FVector(10.0f, 10.0f, 10.0f), HitResult.Location, FRotator(-90, 0, 0), 2.0f);

						SetStamina(-5.0f); // Stamina decreases when interacting with a resource object.

					}
					else {

						// Destroy resource object when depleted.
						HitResource->Destroy();

						// Display debug message.
						check(GEngine != nullptr);
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Resource Depleted"));

					}
				}
			}
		}
	}

	else {
		
		isBuilding = false;
	
	}
}

// Health setter. Updates player's current health.
void APlayerChar::SetHealth(float amount)
{
	if (Health + amount < 100) {
		
		Health = Health + amount;
	
	}
}

// Hunger setter. Updates player's current hunger.
void APlayerChar::SetHunger(float amount)
{
	if (Hunger + amount < 100) {
		
		Hunger = Hunger + amount;
	
	}
}

// Stamina setter. Updates player's current stamina.
void APlayerChar::SetStamina(float amount)
{
	if (Stamina + amount < 100) {
		
		Stamina = Stamina + amount;
	
	}
}

// Setter for decreasing player stats.
void APlayerChar::DecreaseStats()
{
	if (Hunger > 0) {
		
		SetHunger(-3.0f); // If player has hunger, slowly drain hunger overtime.
	
	}

	SetStamina(10.0f); // Stamina regenerates overtime.

	if (Hunger <= 0) {

		SetHealth(-3.0f); // Health drains if player's hunger is empty.

	}


}

void APlayerChar::GiveResource(float amount, FString resourceType)
{

	if (resourceType == "Wood") { // Checks if acquired resource is wood.

		ResourceArray[0] = ResourceArray[0] + amount; // Add wood to current wood amount in player's inventory.

	}

	if (resourceType == "Stone") { // Checks if acquired resource is stone.

		ResourceArray[1] = ResourceArray[1] + amount; // Add stone to current wood amount in player's inventory.

	}

	if (resourceType == "Berry") { // Checks if acquired resource is berries.

		ResourceArray[2] = ResourceArray[2] + amount; // Add berries to current wood amount in player's inventory.

	}
}

void APlayerChar::UpdateResources(float woodAmount, float stoneAmount, FString buildingObject)
{
	if (woodAmount <= ResourceArray[0]) { // Check if player has enough wood.

		if (stoneAmount <= ResourceArray[1]) { // Check if player has enough stone.

			ResourceArray[0] = ResourceArray[0] - woodAmount; // Subtract wood from player's inventory.
			ResourceArray[1] = ResourceArray[1] - stoneAmount; // Subtract stone from player's inventory.

			if (buildingObject == "Wall") { // Check if player built a wall.

				BuildingArray[0] += 1; // Add 1 wall to the player's building inventory.

			}

			if (buildingObject == "Floor") { // Check if player built a floor.

				BuildingArray[1] += 1; // Add 1 floor to the player's building inventory.

			}

			if (buildingObject == "Ceiling") { // Check if player built a ceiling.

				BuildingArray[2] += 1; // Add 1 ceiling to the player's building inventory.

			}

		}
	}
}

void APlayerChar::SpawnBuilding(int buildingID, bool& isSuccess)
{
	if (!isBuilding) { // Check if player is not building.

		if (BuildingArray[buildingID] >= 1) { // Check if player has building they want to build.

			isBuilding = true; // If so, set building mode equal to true.

			// Where the player wants to place. Building will be at least 400 world units away from the player.
			FActorSpawnParameters SpawnParam;
			FVector StartLocation = PlayerCamComp->GetComponentLocation();
			FVector Direction = PlayerCamComp->GetForwardVector() * 400.0f;
			FVector EndLocation = StartLocation + Direction;
			FRotator myRot(0, 0, 0);

			BuildingArray[buildingID] = BuildingArray[buildingID] - 1; // Subtract 1 from the building type the player just placed

			spawnedPart = GetWorld()->SpawnActor<ABuildingPart>(BuildPartClass, EndLocation, myRot, SpawnParam); // Spawn the building the player placed.

			isSuccess = true; // True upon successful place.
		}

		isSuccess = false; // Return to false after placement is complete so the player can place again.

	}


}

void APlayerChar::RotateBuilding()
{

	if (isBuilding) { // Check if player is in building mode.

		spawnedPart->AddActorWorldRotation(FRotator(0, 90, 0)); // Rotation for object player wants to build.

	}

}
