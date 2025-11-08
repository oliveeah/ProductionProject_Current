// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "testInterface.h"

#include "NPC_BaseClass.generated.h"

UCLASS()
class PRODUCTIONPROJCURR_API ANPC_BaseClass : public AActor, public ItestInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANPC_BaseClass();

	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* sceneRoot;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* staticMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Talk();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact_Implementation() override;

private:

	
};
