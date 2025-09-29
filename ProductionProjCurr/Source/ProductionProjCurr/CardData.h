// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CardData.generated.h"

/**
 * 
 */
UCLASS()
class PRODUCTIONPROJCURR_API UCardData : public UPrimaryDataAsset
{
	GENERATED_BODY()

	public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card")
	FText cardName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card")
	FText factionName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card")
	UTexture2D* factionImage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card")
	UTexture2D* cardImage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card")
	FText cardDescription;

};
