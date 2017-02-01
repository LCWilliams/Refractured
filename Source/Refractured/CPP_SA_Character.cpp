// Fill out your copyright notice in the Description page of Project Settings.

#include "Refractured.h"
#include "CPP_SA_Character.h"
#include "CPP_SA_RaycastComponent.h"

// Sets default values
ACPP_SA_Character::ACPP_SA_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	RaycastComponent = CreateDefaultSubobject<UCPP_SA_RaycastComponent>(TEXT("RaycastComponent"));
}

// Called when the game starts or when spawned
void ACPP_SA_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_SA_Character::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ACPP_SA_Character::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	InputComponent->BindAxis("MoveForward", this, &ACPP_SA_Character::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ACPP_SA_Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &ACPP_SA_Character::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &ACPP_SA_Character::LookUpAtRate);

	InputComponent->BindAction("Raycast", IE_Pressed, this, &ACPP_SA_Character::Raycast);
}

void ACPP_SA_Character::Raycast()
{
	if (RaycastComponent != nullptr)
	{
		if (FirstPersonCameraComponent != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("RaycastFired : From character"));
			RaycastComponent->Raycast(FirstPersonCameraComponent);

		}
	}
}

void ACPP_SA_Character::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ACPP_SA_Character::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ACPP_SA_Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ACPP_SA_Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}