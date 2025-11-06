// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProductionProjCurrGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Actor.h"


void AProductionProjCurrGameMode::BeginPlay()
{
	Super::BeginPlay();



}

AProductionProjCurrGameMode::AProductionProjCurrGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/RefactoredStuff/Blueprints/Animation/ABP_TestCharacter.ABP_TestCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	//static ConstructorHelpers::FClassFinder<UUserWidget> PlayerWidgetClassFinder(TEXT("/Game/MyStuff/Blueprints/UI/Player_Widget.Player_Widget"));
	//HUDClass = PlayerWidgetClassFinder.Class;
}
