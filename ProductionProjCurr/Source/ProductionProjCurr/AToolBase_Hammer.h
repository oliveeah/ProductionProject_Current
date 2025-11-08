// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AToolBase.h"
#include "AToolBase_Hammer.generated.h"

/**
 * 
 */
UCLASS()
class PRODUCTIONPROJCURR_API AAToolBase_Hammer : public AAToolBase
{
	GENERATED_BODY()


	
protected:
	virtual void Activate() override;
	virtual void Deactivate() override;
	virtual void UseTool() override;
	
};
