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
	GetCharacterMovement()->bNotifyApex = true;

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



//	AxeInstance = CreateDefaultSubobject<AAToolBase>(TEXT("Pickaxe Subclass Instance"));


	//HammerInstance = CreateDefaultSubobject<AAToolBase>(TEXT("Hammer Subclass Instance"));






	//DEPRECEATED
	//axeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AXEMESH"));

	//if (axeMesh)
	//{
	//	axeMesh->SetupAttachment(GetMesh(), TEXT("axesocket"));
	//	axeMesh->SetVisibility(false);
	//}

	//pickaxeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PICKAXEMESH"));

	//if (pickaxeMesh)
	//{
	//	pickaxeMesh->SetupAttachment(GetMesh(), TEXT("pickaxesocket"));

	//	axeMesh->SetVisibility(false);

	//}

	//hammerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HAMMERMESH"));

	//if (hammerMesh)
	//{
	//	hammerMesh->SetupAttachment(GetMesh(), TEXT("hammersocket"));
	//	hammerMesh->SetVisibility(false);
	//}

	_handState = unequipped;


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


	GetCharacterMovement()->GetCurrentAcceleration();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AProductionProjCurrCharacter::player_OverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AProductionProjCurrCharacter::player_OverlapEnd);



	FActorSpawnParameters spawnParams;

	spawnParams.Owner = this;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	PickaxeInstance = GetWorld()->SpawnActor<AAToolBase>(PickaxeClass, FVector::ZeroVector, FRotator::ZeroRotator, spawnParams);
	PickaxeInstance->AttachToComponent(
		GetMesh(), 
		FAttachmentTransformRules::SnapToTargetIncludingScale,
		FName("HandGrip_R_Pickaxe") 
	); 
	PickaxeInstance->SetActorHiddenInGame(true);

	HammerInstance = GetWorld()->SpawnActor<AAToolBase>(HammerClass, FVector::ZeroVector, FRotator::ZeroRotator, spawnParams);
	HammerInstance->AttachToComponent(
		GetMesh(),
		FAttachmentTransformRules::SnapToTargetIncludingScale,
		FName("HandGrip_R_Hammer")
	);
	HammerInstance->SetActorHiddenInGame(true);

	AxeInstance = GetWorld()->SpawnActor<AAToolBase>(AxeClass, FVector::ZeroVector, FRotator::ZeroRotator, spawnParams);
	AxeInstance->AttachToComponent(
		GetMesh(),
		FAttachmentTransformRules::SnapToTargetIncludingScale,
		FName("HandGrip_R_Axe")
	);
	AxeInstance->SetActorHiddenInGame(true);

	toolArray.Add(AxeInstance);
	toolArray.Add(PickaxeInstance);
	toolArray.Add(HammerInstance);
	//if (IsValid(myWidget))
	//{
	//	myWidget->AddToViewport();
	//}

	//if (GetClass()->ImplementsInterface(UInteraction_Interface::StaticClass()))
	//{
		//UE_LOG(LogTemp, Log, TEXT("This object implements MyInterface!"));
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
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AProductionProjCurrCharacter::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AProductionProjCurrCharacter::DoJumpEnd);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AProductionProjCurrCharacter::Move);

		//tools
		EnhancedInputComponent->BindAction(toggleAxeAction, ETriggerEvent::Started, this, &AProductionProjCurrCharacter::AxePressed);
		EnhancedInputComponent->BindAction(togglePickaxeAction, ETriggerEvent::Started, this, &AProductionProjCurrCharacter::PickaxePressed);

		//use
		EnhancedInputComponent->BindAction(useAction, ETriggerEvent::Started, this, &AProductionProjCurrCharacter::UsePressed);

		//toggle build
		EnhancedInputComponent->BindAction(toggleBuildAction, ETriggerEvent::Started, this, &AProductionProjCurrCharacter::toggleBuildModeFn);
		EnhancedInputComponent->BindAction(interactAction, ETriggerEvent::Started, this, &AProductionProjCurrCharacter::interactCallback);


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

void AProductionProjCurrCharacter::Landed(const FHitResult& Hit)
{
	bIsJumping = false;
	bIsFalling = false;


}

void AProductionProjCurrCharacter::NotifyJumpApex()
{
	bIsFalling = true;

	Super::NotifyJumpApex();

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

	bIsJumping = true;

	GetCharacterMovement()->bNotifyApex = true;
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

void AProductionProjCurrCharacter::AxePressed()
{

	if (unequipCheck(axe))
	{
		_handState = unequipped;
		toggleHandState();
	}
	else
	{
		_handState = axe;

		toggleHandState();
	}
}

void AProductionProjCurrCharacter::PickaxePressed()
{


	if (unequipCheck(pickaxe))
	{
		_handState = unequipped;
		toggleHandState();
	}
	else
	{
		_handState = pickaxe;

		toggleHandState();
	}

}

void AProductionProjCurrCharacter::toggleBuildModeFn()
{


	if (unequipCheck(building))
	{
		_handState = unequipped;
		toggleHandState();
	}
	else
	{
		_handState = building;
		toggleHandState();
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


void AProductionProjCurrCharacter::interactCallback()
{
	if (overlappingActor)
	{
		if (overlappingActor && overlappingActor->GetClass()->ImplementsInterface(UtestInterface::StaticClass()))
		{
			//UE_LOG(LogTemp, Display, TEXT("does implement"));
			ItestInterface::Execute_Interact(overlappingActor);//call interact on overlapping actor implementing interface
			//ItestInterface::Execute_Interact(this); //call player interface if i need
		}
		else
		{
			//UE_LOG(LogTemp, Display, TEXT("doesnt implement"));
		}
	}

}

void AProductionProjCurrCharacter::toggleHandState()
{

	switch (_handState)
	{
	case unequipped:
		UE_LOG(LogTemp, Warning, TEXT("unequipped"));


		break;
	case axe:
		UE_LOG(LogTemp, Warning, TEXT("axe"));
		activeTool = AxeInstance;


		break;
	case pickaxe:
		UE_LOG(LogTemp, Warning, TEXT("pickaxe"));
		activeTool = PickaxeInstance;


		break;
	case building:
		UE_LOG(LogTemp, Warning, TEXT("building"));
		activeTool = HammerInstance;

		break;


	}
	deactivateUneqippedTools();
	


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

void AProductionProjCurrCharacter::player_OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("player overlap event begin"));
	bIsOverlapping = true;
	overlappingActor = OtherActor;
}

void AProductionProjCurrCharacter::player_OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("player overlap event end"));
	bIsOverlapping = false;
	overlappingActor = nullptr;
}

void AProductionProjCurrCharacter::Interact_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("player interface implementation"));

}

bool AProductionProjCurrCharacter::unequipCheck(handState _state)
{
	if (_state == _handState) //if weapon swapping 2 is same as holding
	{
		return true;
	}
	else
	{
		return false;
	}
}

void AProductionProjCurrCharacter::deactivateUneqippedTools()
{
	if (_handState == unequipped) 
	{ 
		activeTool->Deactivate(); 
		activeTool = nullptr;

	}

	for (AAToolBase* Tool : toolArray)
	{
		if (!Tool) continue;

		if (Tool == activeTool)
		{
			//Tool->SetActorHiddenInGame(false);
			Tool->Activate();
		}
		else
		{
			//Tool->SetActorHiddenInGame(true);
			Tool->Deactivate();
		}
	}
}



