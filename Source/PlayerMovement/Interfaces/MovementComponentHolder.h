#pragma once

#include "CoreMinimal.h"
#include "PlayerMovement/BoomMovementComponent.h"
#include "UObject/Interface.h"
#include "MovementComponentHolder.generated.h"

UINTERFACE(MinimalAPI)
class UMovementComponentHolder : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PLAYERMOVEMENT_API IMovementComponentHolder
{
	GENERATED_BODY()

public:
	virtual  UBoomMovementComponent* GetBoomMovementComponent() = 0;
};
