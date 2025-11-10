// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAToolBase_Pickaxe.h"

#include "UObject/ConstructorHelpers.h"


AMyAToolBase_Pickaxe::AMyAToolBase_Pickaxe()
{


    static ConstructorHelpers::FObjectFinder<UStaticMesh> pickaxeMesh(
        TEXT("'StaticMesh'/Game/MyStuff/Models/Tools/stylized-pickaxe/RetopoFlow_002.RetopoFlow_002")
    );

    if (pickaxeMesh.Succeeded())
    {
        UE_LOG(LogTemp, Display, TEXT("mesh succeeded!"));

        ToolMesh->SetStaticMesh(pickaxeMesh.Object);
    }
    else
    {
        UE_LOG(LogTemp, Display, TEXT("mesh failed!"));
    }

    ToolMesh->SetVisibility(true);
    ToolMesh->SetHiddenInGame(false);
    ToolMesh->SetRelativeScale3D(FVector(3.0f));
}

void AMyAToolBase_Pickaxe::Activate()
{
}

void AMyAToolBase_Pickaxe::Deactivate()
{
}

void AMyAToolBase_Pickaxe::UseTool()
{
}
