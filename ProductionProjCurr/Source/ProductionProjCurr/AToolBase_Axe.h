// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AToolBase.h"
#include "AToolBase_Axe.generated.h"

/**
 * 
 */
UCLASS()
class PRODUCTIONPROJCURR_API AAToolBase_Axe : public AAToolBase
{
	GENERATED_BODY()
	
protected:
	virtual void Activate() override;
	virtual void Deactivate() override;
	virtual void UseTool() override;
};
