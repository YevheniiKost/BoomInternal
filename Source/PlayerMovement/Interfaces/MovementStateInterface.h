#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MovementStateInterface.generated.h"

UINTERFACE(MinimalAPI)
class UMovementStateInterface : public UInterface
{
	GENERATED_BODY()
};

class PLAYERMOVEMENT_API IMovementStateInterface
{
	GENERATED_BODY()

public:

	virtual void OnLookInput(const FVector2D InputDirection) = 0;
	virtual void OnMoveInput(const FVector2D InputDirection) = 0;
	virtual void OnJumpInput() = 0;
	virtual void OnDashInput() = 0;

	virtual void UseTriggered() = 0;
	virtual void UseReleased() = 0;
};
