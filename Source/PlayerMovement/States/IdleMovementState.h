#pragma once

#include "CoreMinimal.h"
#include "MovementStateBase.h"
#include "IdleMovementState.generated.h"


UCLASS()
class PLAYERMOVEMENT_API UIdleMovementState : public UMovementStateBase
{
	GENERATED_BODY()

public:
	virtual void OnEnterState(AActor* Owner) override;
	virtual void OnMoveInput(const FVector2D InputDirection) override;
	virtual void OnJumpInput() override;
	virtual void OnDashInput() override;
	virtual void OnLookInput(const FVector2D InputDirection) override;

	virtual void UseTriggered() override;
	virtual void UseReleased() override;
	virtual void TickState(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Climb")
	float TraceSphereRadius = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Climb")
	float HeightTraceVerticalOffset = 300.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Climb")
	float HeightTraceForwardOffset = 75.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Climb")
	float MaxHeightForClimb = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Climb")
	float ClimbFinalPositionForwardOffset = 20.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Climb")
	float ForwardTraceDistance = 100.f;
	
private:
	bool bUseHold = false;
	
	void ProcessLedgeDetection();
	void ProcessClimbDetection();
	bool HeightTrace(FHitResult& HitResult) const;
	bool ForwardTrace(FHitResult& HitResult) const;
};
