// Fill out your copyright notice in the Description page of Project Settings.


#include "AToolBase_Hammer.h"

#include "UObject/ConstructorHelpers.h"


AAToolBase_Hammer::AAToolBase_Hammer()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> hammerMesh(
        TEXT("/Game/MyStuff/Models/Tools/workshop-tools-hand-painted-stylized-pack/Tool_7_002.Tool_7_002")
    );

    if (hammerMesh.Succeeded())
    {
        ToolMesh->SetStaticMesh(hammerMesh.Object);
    }
}

void AAToolBase_Hammer::Activate()
{
}

void AAToolBase_Hammer::Deactivate()
{
}

void AAToolBase_Hammer::UseTool()
{
}
