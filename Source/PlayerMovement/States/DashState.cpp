// Fill out your copyright notice in the Description page of Project Settings.


#include "DashState.h"

#include "StateManagerComponent.h"
#include "GameFramework/Character.h"
#include "PlayerMovement/BoomMovementComponent.h"
#include "PlayerMovement/MovementConfig.h"

void UDashState::OnEnterState(AActor* Owner)
{
	Super::OnEnterState(Owner);
	
	GetWorld()->GetTimerManager().SetTimer(DashTimerHandle, this, &UDashState::OnTimerExpired, DashTime,
										   false);
}

void UDashState::TickState(float DeltaTime)
{
	Super::TickState(DeltaTime);

	const FVector DashDirection = MovementComponent->GetDashDirection();
	Character->AddActorWorldOffset(DashDirection * DashVelocity * DeltaTime, true);
}

void UDashState::OnExitState()
{
	Super::OnExitState();
}

void UDashState::OnTimerExpired()
{
	StateManagerComponent->SwitchStateByKey(MovementConfig::IdleMovementStateName);
}
