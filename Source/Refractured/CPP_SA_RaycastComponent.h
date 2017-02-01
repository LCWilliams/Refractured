// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CPP_SA_RaycastComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REFRACTURED_API UCPP_SA_RaycastComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Raycast Variables", meta = (AllowPrivateAccess = "true"))
		float RayLength = 5000.0f;
public:	
	// Sets default values for this component's properties
	UCPP_SA_RaycastComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void Raycast(UCameraComponent* Camera);
	
};
