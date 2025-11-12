// Fill out your copyright notice in the Description page of Project Settings.


#include "BG_Tile.h"


#include "Components/InstancedStaticMeshComponent.h"
// Sets default values
ABG_Tile::ABG_Tile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//rootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	staticMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = staticMesh;

}

// Called when the game starts or when spawned
void ABG_Tile::BeginPlay()
{
	Super::BeginPlay();


}

void ABG_Tile::OnConstruction(const FTransform& transform)
{
	UE_LOG(LogTemp, Display, TEXT("on construction called"));

	Super::OnConstruction(transform);

	// Clear old instances so we don’t duplicate
	staticMesh->ClearInstances();


	float hexWidth = tileWidth;
	float hexHeight = hexWidth * 0.866f; // sqrt(3)/2 for perfect hex spacing

	//loop create instances
	for (int32 rows = 1; rows < numberOfRows+1; rows++)
	{
		//ySpawnOffset = ySpawnOffset * rows;

		for (int32 cols = 0; cols < numberOfColumns; cols++)
		{
			float xOffset = (rows % 2 == 0) ? 0.0f : (hexWidth * 0.5f);



			float X = cols * hexWidth;
			float Y = rows * hexHeight;

			FVector spawnLocation(X + xOffset, Y, 0.0f);
			FTransform instanceTransform(FRotator::ZeroRotator, spawnLocation);
			staticMesh->AddInstance(instanceTransform);
		}
	}
}

// Called every frame
void ABG_Tile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

