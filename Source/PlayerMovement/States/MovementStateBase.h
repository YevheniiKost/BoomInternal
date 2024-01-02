#pragma once

#include "CoreMinimal.h"
#include "StateBase.h"
#include "PlayerMovement/Interfaces/MovementStateInterface.h"
#include "MovementStateBase.generated.h"

class UBoomMovementComponent;

UCLASS()
class PLAYERMOVEMENT_API UMovementStateBase : public UStateBase, public IMovementStateInterface
{
	GENERATED_BODY()

public:
	virtual void OnLookInput(const FVector2D InputDirection) override;
	virtual void OnMoveInput(const FVector2D InputDirection) override;
	virtual void OnJumpInput() override;
	virtual void OnDashInput() override;

	virtual void OnEnterState(AActor* Owner) override;
	
	virtual void UseTriggered() override;
	virtual void UseReleased() override;

protected:
	TObjectPtr<ACharacter> Character;
	TObjectPtr<AController> Controller;
	TObjectPtr<UBoomMovementComponent> MovementComponent;

	void ProcessLook(FVector2D InputDirection);
};
