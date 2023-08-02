// Fill out your copyright notice in the Description page of Project Settings.


#include "CctvScreen.h"

UCctvScreen::UCctvScreen(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCctvScreen::BeginPlay()
{
	Zoomed->SetVisibility(ESlateVisibility::Hidden);
}

void UCctvScreen::ZoomIn(int index)
{
	if (index >= NumberOfCams || index < 0)
		return;

	MainScreen->SetVisibility(ESlateVisibility::Hidden);
	Zoomed->SetVisibility(ESlateVisibility::Visible);
	CamIndex = index;
	FString LogString = "Cam 0" + FString::FromInt(index + 1);
	CamName->SetText(FText::FromString(LogString));
	GetWorld()->GetFirstPlayerController()->Possess(Cameras[index]);

	UKismetSystemLibrary::PrintString(GetWorld(), "Zoom In " + LogString, true, true, FLinearColor::Green, 2.0f);
}

void UCctvScreen::ZoomOut()
{
	MainScreen->SetVisibility(ESlateVisibility::Visible);
	Zoomed->SetVisibility(ESlateVisibility::Hidden);
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("ZoomOut"), true, true, FLinearColor::Green, 2.0f);
	CamIndex = -1;
}

void UCctvScreen::LeftButtonClicked()
{
	int LIndex = (CamIndex == 0) ? NumberOfCams - 1 : CamIndex - 1;
	UCctvScreen::ZoomIn(LIndex);
}

void UCctvScreen::RightButtonClicked()
{
	int RIndex = (CamIndex == NumberOfCams - 1) ? 0 : CamIndex + 1;
	UCctvScreen::ZoomIn(RIndex);
}

void UCctvScreen::SetImageBrush(TArray<UTexture2D*> texes)
{
	for (int i = 0; i < NumberOfCams; i++)
		CamScreens[i]->SetBrushFromTexture(texes[i]);
	//CamScreens[0]->SetBrushFromMaterial();
}

void UCctvScreen::MoveDetected(int index)
{
	if (index >= NumberOfCams || index < 0)
		return;

	FLinearColor yellow(1.0, 1.0, 0.0, 1.0);
	CamBorders[index]->SetBrushColor(yellow);
}