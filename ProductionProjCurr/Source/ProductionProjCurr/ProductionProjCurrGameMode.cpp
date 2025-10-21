// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProductionProjCurrGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Actor.h"


void AProductionProjCurrGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (!GEngine)
	{
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("GameMode running. GEngine Too!"));


}

AProductionProjCurrGameMode::AProductionProjCurrGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/MyStuff/Blueprints/Player/BP_Bunnt.BP_Bunnt"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	//static ConstructorHelpers::FClassFinder<UUserWidget> PlayerWidgetClassFinder(TEXT("/Game/MyStuff/Blueprints/UI/Player_Widget.Player_Widget"));
	//HUDClass = PlayerWidgetClassFinder.Class;
}
