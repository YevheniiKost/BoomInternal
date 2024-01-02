#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MovementHandler.generated.h"

UINTERFACE(MinimalAPI)
class UMovementHandler : public UInterface
{
	GENERATED_BODY()
};

DECLARE_MULTICAST_DELEGATE(FMovementActionEvent)

class CHARACTERINTERFACES_API IMovementHandler
{
	GENERATED_BODY()

public:
	virtual FMovementActionEvent* GetOnHangLedgeEvent() = 0;
	
};
