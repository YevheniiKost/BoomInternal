// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InputHandler.generated.h"

UINTERFACE(MinimalAPI)
class UInputHandler : public UInterface
{
	GENERATED_BODY()
};

DECLARE_MULTICAST_DELEGATE(FInputActionEvent)
DECLARE_MULTICAST_DELEGATE_OneParam(FInputActionEventVector2D, FVector2D)
DECLARE_MULTICAST_DELEGATE_OneParam(FInputActionEventInt, int)

class CHARACTERINTERFACES_API IInputHandler
{
	GENERATED_BODY()

public:
	virtual FInputActionEvent* GetFireHoldEvent() = 0;
	virtual FInputActionEvent* GetFireReleaseEvent() = 0;
	virtual FInputActionEvent* GetAdditionalFireHoldEvent() = 0;
	virtual FInputActionEvent* GetAdditionalFireReleaseEvent() = 0;
	
	virtual FInputActionEventVector2D* GetMoveActionEvent() = 0;
	virtual FInputActionEvent* GetMoveReleaseEvent() = 0;

	virtual FInputActionEventVector2D* GetLookActionEvent() = 0;

	virtual FInputActionEvent* GetJumpTriggerEvent() = 0;
	virtual FInputActionEvent* GetJumpReleaseEvent() = 0;

	virtual FInputActionEvent* GetDashTriggerEvent() = 0;
	virtual FInputActionEvent* GetDashReleaseEvent() = 0;

	virtual FInputActionEvent* GetUseTriggerEvent() = 0;
	virtual FInputActionEvent* GetUseReleaseEvent() = 0;

	virtual FInputActionEventInt* GetWeaponSwitchEvent() = 0;
};
