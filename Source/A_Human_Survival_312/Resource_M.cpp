// Fill out your copyright notice in the Description page of Project Settings.


#include "Resource_M.h"

// Sets default values
AResource_M::AResource_M()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Adds text to the static mesh. This is a placeholder for now
	ResourceNameTxt = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text Render"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	// Root component is the mesh model
	RootComponent = Mesh;

	// Attach the temporary text to the mesh model
	ResourceNameTxt->SetupAttachment(Mesh);

}

// Called when the game starts or when spawned
void AResource_M::BeginPlay()
{
	Super::BeginPlay();
	
	// Temporary text
	tempText = tempText.FromString(resourceName);

	// Sets what the text says
	ResourceNameTxt->SetText(tempText);

}

// Called every frame
void AResource_M::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

