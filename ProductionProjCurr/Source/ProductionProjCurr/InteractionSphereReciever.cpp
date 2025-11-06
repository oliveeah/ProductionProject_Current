// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionSphereReciever.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values for this component's properties
UInteractionSphereReciever::UInteractionSphereReciever()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	boxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("boxCollision"));
}


// Called when the game starts
void UInteractionSphereReciever::BeginPlay()
{
	Super::BeginPlay();

	AActor* owningActor = GetOwner();

	boxCollider = NewObject<UBoxComponent>(owningActor, UBoxComponent::StaticClass(), TEXT("InteractionBox"));

	if (!boxCollider) return;

	boxCollider->AttachToComponent(owningActor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	boxCollider->RegisterComponent();

	boxCollider->OnComponentBeginOverlap.AddDynamic(this, &UInteractionSphereReciever::interactionSphere_OverlapBegin);
	boxCollider->OnComponentEndOverlap.AddDynamic(this, &UInteractionSphereReciever::interactionSphere_OverlapEnd);

	boxCollider->SetActive(true);

	UE_LOG(LogTemp, Warning, TEXT("InteractionReceiver: %s has box: %s, registered: %d, active: %d"),
		*GetOwner()->GetName(),
		*boxCollider->GetName(),
		boxCollider->IsRegistered(),
		boxCollider->IsActive());
}


// Called every frame
void UInteractionSphereReciever::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractionSphereReciever::interactionSphere_OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("overlap begin (AC)!"));
	}
}

void UInteractionSphereReciever::interactionSphere_OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("overlap end (AC)!"));
	}
}

