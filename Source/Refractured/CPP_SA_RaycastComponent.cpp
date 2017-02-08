// Fill out your copyright notice in the Description page of Project Settings.

#include "Refractured.h"
#include "CPP_SA_RaycastComponent.h"


// Sets default values for this component's properties
UCPP_SA_RaycastComponent::UCPP_SA_RaycastComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCPP_SA_RaycastComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCPP_SA_RaycastComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UCPP_SA_RaycastComponent::Raycast(UCameraComponent* Camera)
{
	UWorld* const World = GetWorld();
	if (World == nullptr) return;
	FHitResult HitResult;
	FVector StartTrace = Camera->GetComponentLocation();
	FVector ForwardVector = Camera->GetForwardVector();
	FVector EndTrace = StartTrace + (ForwardVector * RayLength);
	FCollisionQueryParams CQP;
	// Make sure actors that want to recieve the hit
	// Are set to block Visibility in Collision
	// Settings
	if (World->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, CQP))
	{
		UE_LOG(LogTemp, Warning, TEXT("Raycast Fired Successfully"));
		DrawDebugLine(World, StartTrace, EndTrace, FColor::Red, true, 5.0f);
		AActor* HitActor = HitResult.GetActor();
		if (HitActor != nullptr)
		{
			HitActor->Destroy();
		}
	}

		//AMyClassType* Tank = Cast<AMyClassType>(HitResult.GetActor());
		//if (Tank != nullptr)
		//{
		//	Tank->Destroy();
		//}
	

}
