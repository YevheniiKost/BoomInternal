// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovementStateBase.h"
#include "PullUpState.generated.h"

/**
 * 
 */
UCLASS()
class PLAYERMOVEMENT_API UPullUpState : public UMovementStateBase
{
	GENERATED_BODY()

public:
	virtual void TickState(float DeltaTime) override;
	virtual void OnEnterState(AActor* Owner) override;
	virtual void OnExitState() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Climb")
	float ClimbSpeed = 100.f;

private:
	const float ClimbPositionThreshold = 10.f;

};
