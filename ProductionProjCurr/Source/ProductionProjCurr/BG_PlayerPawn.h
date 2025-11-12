// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputAction.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "BG_PlayerPawn.generated.h"

UCLASS()
class PRODUCTIONPROJCURR_API ABG_PlayerPawn : public APawn
{
	GENERATED_BODY()

public:

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	class USpectatorPawnMovement* SpectatorMovementComponent;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* moveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* lookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* clickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* scrollAction;

protected:
	/** Called for movement input */
	void MoveCallback(const FInputActionValue& Value);

	/** Called for looking input */
	void LookCallback(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void clickCallback();

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void scrollCallback(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoMove(float Right, float Forward);

public:
	// Sets default values for this pawn's properties
	ABG_PlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	float TargetFOV = 90.0f;     
	float CurrentFOV = 90.0f;    
	float ZoomSpeed = 10.0f;      
	float ZoomInterpSpeed = 10.0f; 
};
