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

	//loop create instances
	for (int32 i = 0; i < numberOfTiles; i++)
	{
		float _ySpawnOffset;

		if (i % 2 == 0)//even
		{
			_ySpawnOffset = 0.0f;
		}
		else//odd
		{
			_ySpawnOffset = ySpawnOffset;

		}
		FVector spawnlocation(_ySpawnOffset, i * tileWidth, 0.0f);
		FTransform instanceTransform(FRotator::ZeroRotator, spawnlocation);
		staticMesh->AddInstance(instanceTransform);

	}
}

// Called every frame
void ABG_Tile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

