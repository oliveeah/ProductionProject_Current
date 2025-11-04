// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProductionProjCurrCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AProductionProjCurrCharacter::AProductionProjCurrCharacter()
{
	APlayerController* myController = GetWorld()->GetFirstPlayerController();
	myController->bShowMouseCursor = true;
	myController->bEnableClickEvents = true;
	myController->bEnableMouseOverEvents = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 250.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 350.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bEnableCameraLag = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	axeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AXEMESH"));

	if (axeMesh)
	{
		axeMesh->SetupAttachment(GetMesh(), TEXT("axesocket"));
		axeMesh->SetVisibility(false);
	}

	pickaxeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PICKAXEMESH"));

	if (pickaxeMesh)
	{
		pickaxeMesh->SetupAttachment(GetMesh(), TEXT("pickaxesocket"));

		axeMesh->SetVisibility(false);

	}

	hammerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HAMMERMESH"));

	if (hammerMesh)
	{
		hammerMesh->SetupAttachment(GetMesh(), TEXT("hammersocket"));
		hammerMesh->SetVisibility(false);
	}

	handState::unequipped;



	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AProductionProjCurrCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(myWidget) && myWidgetClass)
	{
		myWidget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), myWidgetClass);
	}

	//if (IsValid(myWidget))
	//{
	//	myWidget->AddToViewport();
	//}
}

void AProductionProjCurrCharacter::Tick(float DeltaTime)
{
	FVelocity = RootComponent->GetComponentVelocity();

}



void AProductionProjCurrCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AProductionProjCurrCharacter::Move);

		//tools
		EnhancedInputComponent->BindAction(toolOneAction, ETriggerEvent::Started, this, &AProductionProjCurrCharacter::ToolOnePressed);
		EnhancedInputComponent->BindAction(toolTwoAction, ETriggerEvent::Started, this, &AProductionProjCurrCharacter::ToolTwoPressed);

		//use
		EnhancedInputComponent->BindAction(useAction, ETriggerEvent::Started, this, &AProductionProjCurrCharacter::UsePressed);

		//toggle build
		EnhancedInputComponent->BindAction(toggleBuildAction, ETriggerEvent::Started, this, &AProductionProjCurrCharacter::toggleBuildModeFn);


	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}





void AProductionProjCurrCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}


void AProductionProjCurrCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);


	

	}
}


void AProductionProjCurrCharacter::DoJumpStart()
{
	// signal the character to jump
	Jump();
}

void AProductionProjCurrCharacter::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}


//////////////////////////////////////////
/// <summary>
/// HAND STATE STUFF 
/// </summary>

void AProductionProjCurrCharacter::ToolOnePressed()
{
	if (isBuilding) { return; }
	if (axeIsHeld)
	{
		toggleHandState(handState::unequipped);
	}
	else
	{
		toggleHandState(handState::axe);

	}

}

void AProductionProjCurrCharacter::ToolTwoPressed()
{
	if (isBuilding) { return; }

	if (pickaxeIsHeld)
	{
		toggleHandState(handState::unequipped);
	}
	else
	{
		toggleHandState(handState::pickaxe);

	}

}

/// <summary>
/// HAND STATE STUFF 
/// </summary>

void AProductionProjCurrCharacter::UsePressed()
{
	UE_LOG(LogTemp, Display, TEXT("swing"));

	if (swingMontage && GetMesh() && GetMesh()->GetAnimInstance() && !noItemIsHeld && !isBuilding)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		AnimInstance->Montage_Play(swingMontage);
	}
}

void AProductionProjCurrCharacter::toggleBuildModeFn()
{
	isBuilding = !isBuilding; 
	
	if (isBuilding)
	{
		UE_LOG(LogTemp, Display, TEXT("buliding"));

	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("not building"));

	}
	isBuilding ? toggleHandState(handState::building) : toggleHandState(handState::unequipped);
	isBuilding ? toggleBuildWidget(true) : toggleBuildWidget(false);


}

void AProductionProjCurrCharacter::toggleHandState(handState state)
{

	switch(state)
	{

		case(axe):
				axeMesh->SetVisibility(true);
				pickaxeMesh->SetVisibility(false);
				axeIsHeld = true;
				pickaxeIsHeld = false;
				noItemIsHeld = false;

				UE_LOG(LogTemp, Warning, TEXT("holding axe"));

			
		
		break;

		case(pickaxe):
				axeMesh->SetVisibility(false);
				pickaxeMesh->SetVisibility(true);
				axeIsHeld = false;
				pickaxeIsHeld = true;
				UE_LOG(LogTemp, Warning, TEXT("holding pickaxe"));
				noItemIsHeld = false;

			

		break;
		case(unequipped):
			axeMesh->SetVisibility(false);
			pickaxeMesh->SetVisibility(false);
			hammerMesh->SetVisibility(false);

			axeIsHeld = false;
			pickaxeIsHeld = false;
			noItemIsHeld = true;

			UE_LOG(LogTemp, Warning, TEXT("holding nothing"));

		break;

		case(building):
			UE_LOG(LogTemp, Display, TEXT("buliding case called"));
			hammerMesh->SetVisibility(true);
			axeMesh->SetVisibility(false);
			pickaxeMesh->SetVisibility(false);
			axeIsHeld = false;
			pickaxeIsHeld = false;
			noItemIsHeld = false;
			break;

	}


	


}

void AProductionProjCurrCharacter::toggleBuildWidget(bool _isBuilding)
{
	if (IsValid(myWidget))
	{
		APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		if (_isBuilding)
		{
			myWidget->AddToViewport();
			playerController->bShowMouseCursor = true; 
		}
		else
		{
			myWidget->RemoveFromParent();
			playerController->bShowMouseCursor = false;

		}
	}
}
