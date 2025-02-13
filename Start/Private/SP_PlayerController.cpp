// Fill out your copyright notice in the Description page of Project Settings.
#include "SP_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "MyGameState.h"
#include "Blueprint/UserWidget.h"

ASP_PlayerController::ASP_PlayerController()
:	InputMappingContext(nullptr),
	MoveAction(nullptr),
	MoveForwardAction(nullptr),
	MoveRightAction(nullptr),
	SprintAction(nullptr),
	LookAction(nullptr),
	JumpAction(nullptr),
	MoveUpAction(nullptr),
	RotateRollAction(nullptr),
	FlightHoldAction(nullptr),
	HUDWidgetClass(nullptr),
	HUDWidgetInstance(nullptr)
{
}

void ASP_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem=
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}
	if (HUDWidgetClass)
	{
		HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		if (HUDWidgetInstance) HUDWidgetInstance->AddToViewport(); // 뷰포트에 렌더링 해달라
	}
	AMyGameState* MyGameState = GetWorld() ? GetWorld()->GetGameState<AMyGameState>() : nullptr;
	if (MyGameState)
	{
		MyGameState->UpdateHUD();
	}
}

UUserWidget* ASP_PlayerController::GetHUDWidget() const
{
	return HUDWidgetInstance;
}