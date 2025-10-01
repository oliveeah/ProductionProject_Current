// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProductionProjCurrGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"


void AProductionProjCurrGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (!GEngine)
	{
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("GameMode running. GEngine Too!"));

	if (widgetPtr)
	{
		currentWidget = CreateWidget(GetWorld(), widgetPtr);

	}
	if (currentWidget)
	{
		currentWidget->AddToViewport();
	}

}

AProductionProjCurrGameMode::AProductionProjCurrGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/MyStuff/Blueprints/Player/BP_Mushroom.BP_Mushroom"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	//static ConstructorHelpers::FClassFinder<UUserWidget> PlayerWidgetClassFinder(TEXT("/Game/MyStuff/Blueprints/UI/Player_Widget.Player_Widget"));
	//HUDClass = PlayerWidgetClassFinder.Class;
}
