// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_BaseClass.h"

#include "Components/StaticMeshComponent.h"

// Sets default values
ANPC_BaseClass::ANPC_BaseClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	sceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(sceneRoot);

	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	staticMesh->SetupAttachment(sceneRoot);

}

// Called when the game starts or when spawned
void ANPC_BaseClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPC_BaseClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANPC_BaseClass::Interact_Implementation()
{	
	Talk();
}

void ANPC_BaseClass::Talk()
{
	UE_LOG(LogTemp, Warning, TEXT("TALK Called"));
}


