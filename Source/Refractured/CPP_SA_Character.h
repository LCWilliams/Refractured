// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "CPP_SA_Character.generated.h"

UCLASS()
class REFRACTURED_API ACPP_SA_Character : public ACharacter
{
	GENERATED_BODY()
private:

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	//UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	//	class USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "C++ Variables", meta = (AllowPrivateAccess = "true"))
		class UCPP_SA_RaycastComponent* RaycastComponent;
private:

	UFUNCTION()
		void Raycast();
public:

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	///** Sound to play each time we fire */
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	//	class USoundBase* FireSound;

	///** AnimMontage to play each time we fire */
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	//	class UAnimMontage* FireAnimation;
public:

	// Sets default values for this character's properties
	ACPP_SA_Character();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	/** Returns Mesh1P subobject **/
	//FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

protected:

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);
	
	/**
	* Called via input to turn at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

	/**
	* Called via input to turn look up/down at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void LookUpAtRate(float Rate);
};
