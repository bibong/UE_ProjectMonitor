// Fill out your copyright notice in the Description page of Project Settings.


#include "SecurityCamera.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"

// Sets default values
ASecurityCamera::ASecurityCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
}

// Called when the game starts or when spawned
void ASecurityCamera::BeginPlay()
{
	Super::BeginPlay();
	
	InitialRotator = GetActorRotation();
}

// Called every frame
void ASecurityCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASecurityCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ASecurityCamera::NormalizeAngle(const float Angle) const
{
    if (Angle >= 180.0f)
	{
		return Angle - 360.0f;
	}
	else if (Angle <= -180.0f)
	{
		return Angle + 360.0f;
	}
	else 
	{
		return Angle;
	}
}

void ASecurityCamera::TurnRight(const float AxisValue)
{
	FRotator Rotator = GetActorRotation();
	float DeltaYaw = Rotator.Yaw - InitialRotator.Yaw;
	DeltaYaw = NormalizeAngle(DeltaYaw);
	if (AxisValue > 0.0f && DeltaYaw >= MaxDeltaYaw) 
	{
		return;
	}
	else if (AxisValue < 0.0f && DeltaYaw <= MinDeltaYaw) 
	{
		return;
	}
	FRotator DeltaRotation = UKismetMathLibrary::RotatorFromAxisAndAngle(FVector::UpVector, AxisValue * RotationSpeed);
	AddActorWorldRotation(DeltaRotation, false, 0, ETeleportType::None);
}

void ASecurityCamera::TurnUp(const float AxisValue)
{
	FRotator Rotator = GetActorRotation();
	float DeltaPitch = Rotator.Pitch - InitialRotator.Pitch;
	DeltaPitch = NormalizeAngle(DeltaPitch);
	if (AxisValue > 0.0f && DeltaPitch >= MaxDeltaPitch) 
	{
		return;
	}
	else if (AxisValue < 0.0f && DeltaPitch <= MinDeltaPitch) 
	{
		return;
	}
	FVector AxisX, AxisY, AxisZ;
	UKismetMathLibrary::GetAxes(Rotator, AxisX, AxisY, AxisZ);
	FRotator DeltaRotation = UKismetMathLibrary::RotatorFromAxisAndAngle(AxisY, -(AxisValue * RotationSpeed));
	AddActorWorldRotation(DeltaRotation, false, 0, ETeleportType::None);
}

void ASecurityCamera::Zoom(const float AxisValue)
{
	float FieldOfView = CameraComponent->FieldOfView - ZoomSpeed * AxisValue;
	CameraComponent->FieldOfView = FMath::Clamp(FieldOfView, MinFieldOfView, MaxFieldOfView);
}