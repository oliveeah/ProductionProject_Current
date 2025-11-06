// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interaction_Interface.h"

#include "InteractionSphereReciever.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRODUCTIONPROJCURR_API UInteractionSphereReciever : public UActorComponent, public IInteraction_Interface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionSphereReciever();

	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* sceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* staticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Math")
	class UBoxComponent* boxCollider;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void interactionSphere_OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void interactionSphere_OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
		
};
