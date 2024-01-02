#pragma once

#include "CoreMinimal.h"
#include "MovementHandler.h"
#include "Components/ActorComponent.h"
#include "BoomMovementComponent.generated.h"

class UStateManagerComponent;
class IInputHandler;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PLAYERMOVEMENT_API UBoomMovementComponent : public UActorComponent, public IMovementHandler
{
	GENERATED_BODY()

public:
	UBoomMovementComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void SetCharacter(ACharacter* NewCharacter);
	void SetInputComponent(IInputHandler* InputHandler);
	void SetMovementStateManager(UStateManagerComponent* NewStateManager);

	void SetDashDirection(const FVector& NewDashDirection) { DashDirection = NewDashDirection; }
	FVector GetDashDirection() const { return DashDirection; }

	virtual FMovementActionEvent* GetOnHangLedgeEvent() override { return &OnHangLedgeEvent; }

	void SetClimbLocation(const FVector& NewClimbLocation) { ClimbLocation = NewClimbLocation; }
	FVector GetClimbLocation() const { return ClimbLocation; }

protected:
	virtual void BeginPlay() override;

private:
	TObjectPtr<UStateManagerComponent> StateManager;
	TObjectPtr<ACharacter> Character;
	TObjectPtr<AController> Controller;
	IInputHandler* InputComponent;

	FVector DashDirection;
	FVector ClimbLocation;

	bool bClimbing = false;

	FMovementActionEvent OnHangLedgeEvent;

	void Move(const FVector2D InputDirection);
	void MoveRelease();
	void Look(const FVector2D InputDirection);
	void Jump() const;
	void Dash();
	void DashRelease();
	void JumpRelease();
	void UseTriggered();
	void UseReleased();

	bool ForwardTrace(FHitResult& HitResult) const;
};
