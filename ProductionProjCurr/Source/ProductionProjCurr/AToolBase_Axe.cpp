// Fill out your copyright notice in the Description page of Project Settings.


#include "AToolBase_Axe.h"

#include "UObject/ConstructorHelpers.h"


AAToolBase_Axe::AAToolBase_Axe()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> axeMesh(
        TEXT("/Game/MyStuff/Models/Tools/workshop-tools-hand-painted-stylized-pack/axe.axe") 
    );

    if (axeMesh.Succeeded())
    {
        ToolMesh->SetStaticMesh(axeMesh.Object);
    }
}

void AAToolBase_Axe::Activate()
{
    SetActorHiddenInGame(false);

}

void AAToolBase_Axe::Deactivate()
{
    SetActorHiddenInGame(true);

}

void AAToolBase_Axe::UseTool()
{
}

