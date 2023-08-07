// Fill out your copyright notice in the Description page of Project Settings.


#include "SecurityCameraScreen.h"
#include "Kismet/KismetSystemLibrary.h"

USecurityCameraScreen::USecurityCameraScreen(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void USecurityCameraScreen::BeginPlay()
{
	ZoomedCamBorder->SetVisibility(ESlateVisibility::Hidden);
	Zoomed->SetVisibility(ESlateVisibility::Hidden);
}

void USecurityCameraScreen::ZoomIn(int index)
{
	if (Cameras.GetAllocatedSize() == 0)
		return;

	if (index >= NumberOfCams || index < 0)
		return;

	MainScreen->SetVisibility(ESlateVisibility::Hidden);
	ZoomedCamBorder->SetVisibility(ESlateVisibility::Visible);
	Zoomed->SetVisibility(ESlateVisibility::Visible);
	CamIndex = index;
	FString LogString = "Cam 0" + FString::FromInt(index + 1);
	CamName->SetText(FText::FromString(LogString));
	GetWorld()->GetFirstPlayerController()->Possess(Cameras[index]);
	IsZoomed = true;

	UKismetSystemLibrary::PrintString(GetWorld(), "Zoom In " + LogString, true, true, FLinearColor::Green, 2.0f);
}

void USecurityCameraScreen::ZoomOut()
{
	MainScreen->SetVisibility(ESlateVisibility::Visible);
	ZoomedCamBorder->SetVisibility(ESlateVisibility::Hidden);
	Zoomed->SetVisibility(ESlateVisibility::Hidden);
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("ZoomOut"), true, true, FLinearColor::Green, 2.0f);
	CamIndex = -1;
	IsZoomed = false;
}

void USecurityCameraScreen::LeftButtonClicked()
{
	int LIndex = (CamIndex == 0) ? NumberOfCams - 1 : CamIndex - 1;
	CamIndex = LIndex;
	USecurityCameraScreen::ZoomIn(LIndex);
}

void USecurityCameraScreen::RightButtonClicked()
{
	int RIndex = (CamIndex == NumberOfCams - 1) ? 0 : CamIndex + 1;
	CamIndex = RIndex;
	USecurityCameraScreen::ZoomIn(RIndex);
}

void USecurityCameraScreen::SetImageBrush(TArray<UTexture2D*> texes)
{
	if (CamScreens.GetAllocatedSize() < NumberOfCams)
		return;

	if (texes.GetAllocatedSize() < NumberOfCams)
		return;

	for (int i = 0; i < NumberOfCams; i++)
		CamScreens[i]->SetBrushFromTexture(texes[i]);
}

void USecurityCameraScreen::MoveStart(int index)
{
	if (ZoomedCamBorders.GetAllocatedSize() == 0)
		return;

	if (index >= NumberOfCams || index < 0)
		return;

	FLinearColor yellow(1.0, 1.0, 0.0, 1.0);

	if (IsZoomed)
	{
		if (index == CamIndex)
		{
			for (int i = 0; i < 4; i++)
			{
				ZoomedCamBorders[i]->SetBrushColor(yellow);
			}
		}
	}
	else
		CamBorders[index]->SetBrushColor(yellow);
}

void USecurityCameraScreen::MoveEnd(int index)
{
	if (ZoomedCamBorders.GetAllocatedSize() == 0)
		return;

	if (index >= NumberOfCams || index < 0)
		return;

	FLinearColor black(0.0, 0.0, 0.0, 1.0);

	if (IsZoomed)
	{
		if (index == CamIndex)
		{
			for (int i = 0; i < 4; i++)
			{
				ZoomedCamBorders[i]->SetBrushColor(black);
			}
		}
	}
	else 
		CamBorders[index]->SetBrushColor(black);
}