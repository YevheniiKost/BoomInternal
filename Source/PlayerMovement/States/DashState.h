// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovementStateBase.h"
#include "DashState.generated.h"

/**
 * 
 */
UCLASS()
class PLAYERMOVEMENT_API UDashState : public UMovementStateBase
{
	GENERATED_BODY()

public:
	virtual void TickState(float DeltaTime) override;
	virtual void OnExitState() override;
	virtual void OnEnterState(AActor* Owner) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DashVelocity = 1000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DashTime = 1.f;
	
private:
	FTimerHandle DashTimerHandle;
	void OnTimerExpired();
};
