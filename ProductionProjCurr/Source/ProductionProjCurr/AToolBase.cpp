// Fill out your copyright notice in the Description page of Project Settings.


#include "AToolBase.h"

#include "UObject/ConstructorHelpers.h"

// Sets default values
AAToolBase::AAToolBase()
{
    ToolMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ToolMesh"));
    SetRootComponent(ToolMesh);

    ToolMesh->SetCollisionProfileName(TEXT("NoCollision"));

}

// Called when the game starts or when spawned
void AAToolBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAToolBase::Activate()
{
    //SetActorHidde
}

void AAToolBase::Deactivate()
{
}

void AAToolBase::UseTool()
{
}


