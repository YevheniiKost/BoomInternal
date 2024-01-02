#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AnimationHandler.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAnimationHandler : public UInterface
{
	GENERATED_BODY()
};

class CHARACTERINTERFACES_API IAnimationHandler
{
	GENERATED_BODY()

public:
	virtual void PlayMontageSection(UAnimMontage* MontageToPlay, float PlayDuration, FName StartSectionName = NAME_None) = 0;
};
