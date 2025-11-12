// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AToolBase.h"
#include "MyAToolBase_Pickaxe.generated.h"

/**
 * 
 */
UCLASS()
class PRODUCTIONPROJCURR_API AMyAToolBase_Pickaxe : public AAToolBase
{
	GENERATED_BODY()

public:
	AMyAToolBase_Pickaxe();
	
protected:
	virtual void Activate() override;
	virtual void Deactivate() override;
	virtual void UseTool() override;

};
