// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimNotifyState.h"


void UMyAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	if (collisionSucceeded)
	{
		return;
	}

	AActor* owner = MeshComp->GetOwner();
	UWorld* world = MeshComp->GetWorld();
	FName boneName = TEXT("hand_r");
	FVector boneLocation = MeshComp->GetBoneLocation(boneName, EBoneSpaces::WorldSpace);

	TArray<FHitResult> HitResults;

	if (!world)//if null ptr
	{
		UE_LOG(LogTemp, Display, TEXT("world is a null pointer"));
		return;
	}

	DrawDebugSphere(world, boneLocation, 50, 16, FColor::Blue, false, 0.0f, 0.0f, 2.0f);
	bool bHit = world->SweepMultiByChannel(//collision true/false
		HitResults,
		boneLocation,
		boneLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,  //trace channel
		FCollisionShape::MakeSphere(50)
	);

	if (bHit)
	{
			for (FHitResult hit : HitResults)
			{
				AActor* hitActor = hit.GetActor();
				if (hitActor)
				{
					UE_LOG(LogTemp, Display, TEXT("hit actor : %s"), *hitActor->GetName());
					if (hitActor->ActorHasTag("breakable"))
					{
						UE_LOG(LogTemp, Warning, TEXT("Hit breakable object"));//apply damage here
						collisionSucceeded = true;
						break;
					}
				}
			}
	}
}

void UMyAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	collisionSucceeded = false;//reset collision
}
