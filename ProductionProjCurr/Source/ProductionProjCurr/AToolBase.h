// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AToolBase.generated.h"

UCLASS(Abstract)
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

protected:
	virtual void Activate() PURE_VIRTUAL(AAToolBase::Activate, UE_LOG(LogTemp, Display, TEXT("default implementation of activate")););
	virtual void Deactivate() PURE_VIRTUAL(AAToolBase::Deactivate, UE_LOG(LogTemp, Display, TEXT("default implementation of deactivate")););
	virtual void UseTool() PURE_VIRTUAL(AAToolBase::UseTool, UE_LOG(LogTemp, Display, TEXT("default implementation of use tool")););


public:	


};
