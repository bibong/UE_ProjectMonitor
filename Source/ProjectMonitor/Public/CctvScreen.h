// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "SecurityCamera.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CctvScreen.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMONITOR_API UCctvScreen : public UUserWidget
{
	GENERATED_BODY()
	

private:
	const int NumberOfCams = 9;

public:
	UCctvScreen(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
		void BeginPlay();

	UFUNCTION(BlueprintCallable)
		void ZoomIn(int index);

	UFUNCTION(BlueprintCallable)
		void ZoomOut();

	UFUNCTION(BlueprintCallable)
		void LeftButtonClicked();

	UFUNCTION(BlueprintCallable)
		void RightButtonClicked();

	UFUNCTION(BlueprintCallable)
		void SetImageBrush(TArray<UTexture2D*> texes);

	UFUNCTION(BlueprintCallable)
		void MoveDetected(int index);


	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget), Category = "Cctv")
		UCanvasPanel* Zoomed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget), Category = "Cctv")
		UCanvasPanel* MainScreen;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget), Category = "Cctv")
		TArray<UImage*> CamScreens;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cctv")
		TArray<ASecurityCamera*> Cameras;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget), Category = "Cctv")
		UTextBlock* CamName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget), Category = "Cctv")
		TArray<UBorder*> CamBorders;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cctv")
		int CamIndex = -1;
};
