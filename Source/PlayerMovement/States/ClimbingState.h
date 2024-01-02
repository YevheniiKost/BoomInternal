// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovementStateBase.h"
#include "ClimbingState.generated.h"

/**
 * 
 */
UCLASS()
class PLAYERMOVEMENT_API UClimbingState : public UMovementStateBase
{
	GENERATED_BODY()

public:
	virtual void OnEnterState(AActor* Owner) override;
	void RotateToWall(float DeltaTime, FHitResult HitResult);
	void KeepDistanceToWall(float DeltaTime, FHitResult HitResult);
	virtual void TickState(float DeltaTime) override;
	virtual void OnExitState() override;

	virtual void OnLookInput(const FVector2D Input) override;
	virtual void OnMoveInput(const FVector2D Input) override;
	virtual void OnJumpInput() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Climb")
	float ForwardTraceDistance = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Climb")
	float SideCheckDistance = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Climb")
	float UpCheckDistance = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Climb")
	float DownCheckDistance = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Climb")
	float ClimbingSpeed = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Climb")
	float DistanceToWall = 70.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Climb")
	float LaunchForce = 500.f;
	
private:
	bool CheckClimbSurface(const FVector& StartLocation, FHitResult& HitResult) const;

	FVector2D InputDirection;
};
