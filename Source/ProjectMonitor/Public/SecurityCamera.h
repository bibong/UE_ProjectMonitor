// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "SecurityCamera.generated.h"

UCLASS()
class PROJECTMONITOR_API ASecurityCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASecurityCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float NormalizeAngle(const float Angle) const;

	UFUNCTION(BlueprintCallable)
	void TurnRight(const float AxisValue);

	UFUNCTION(BlueprintCallable)
	void TurnUp(const float AxisValue);

	UFUNCTION(BlueprintCallable)
	void Zoom(const float AxisValue);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RotationSpeed = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ZoomSpeed = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxDeltaPitch = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinDeltaPitch = -30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxDeltaYaw = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinDeltaYaw = -30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxFieldOfView = 90.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinFieldOfView = 30.0f;

private:
	UPROPERTY()
	FRotator InitialRotator;
};
