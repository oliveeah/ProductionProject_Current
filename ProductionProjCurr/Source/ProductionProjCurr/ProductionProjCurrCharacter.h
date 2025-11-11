// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "testInterface.h"
#include "AToolBase.h"
#include "ProductionProjCurrCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;


DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);


UCLASS(abstract)
class AProductionProjCurrCharacter : public ACharacter, public ItestInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tools")
	TSubclassOf<AAToolBase> PickaxeClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tools")
	TSubclassOf<AAToolBase> HammerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tools")
	TSubclassOf<AAToolBase> AxeClass;

	//Spawned instances
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tools")
	AAToolBase* PickaxeInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tools")
	AAToolBase* HammerInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tools")
	AAToolBase* AxeInstance;

protected:

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* MoveAction;

	//tool1//
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* toggleAxeAction;

	//tool2//
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* togglePickaxeAction;

	//use//
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* useAction;

	//toggle build
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* toggleBuildAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* interactAction;

public:

	/** Constructor */
	AProductionProjCurrCharacter();	


protected:

	/** Initialize input action bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	virtual void Landed(const FHitResult& Hit) override;

	virtual void NotifyJumpApex() override;



public:

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void AxePressed();

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void PickaxePressed();

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void UsePressed();

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void toggleBuildModeFn();


	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void interactCallback();





public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/*UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* axeMesh;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* pickaxeMesh;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* hammerMesh;*/

	enum handState 
	{
		unequipped, axe, pickaxe, building,
	};

	handState _handState;


	void toggleHandState();

	bool axeIsHeld = false;
	bool pickaxeIsHeld = false;
	bool noItemIsHeld = true;
	bool isBuilding = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)	
	UAnimMontage* swingMontage;

	UPROPERTY()
	UUserWidget* myWidget;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UUserWidget> myWidgetClass;

	void toggleBuildWidget(bool isbuilding);

	public:

		UPROPERTY(BlueprintReadOnly)
		FVector FVelocity;

		UPROPERTY(BlueprintReadWrite)
		float movementSpeed;

		UPROPERTY(BlueprintReadOnly)
		bool bIsJumping = false;

		UPROPERTY(BlueprintReadOnly)
		bool bIsFalling = false;

		bool bIsOverlapping = false;
		AActor* overlappingActor = nullptr;

	public:
		
		UFUNCTION()
		void player_OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

		UFUNCTION()
		void player_OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

		void Interact_Implementation() override;


		bool unequipCheck(handState _state);

		void deactivateUneqippedTools();

		TArray<AAToolBase*> toolArray;

		AAToolBase* activeTool = nullptr;

};

