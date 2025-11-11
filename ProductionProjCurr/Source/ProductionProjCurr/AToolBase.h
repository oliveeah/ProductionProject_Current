// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AToolBase.generated.h"

UCLASS()
class PRODUCTIONPROJCURR_API AAToolBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAToolBase();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tool")
	UStaticMeshComponent* ToolMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Activate();
	virtual void Deactivate();
	virtual void UseTool();

	
public:	


};
