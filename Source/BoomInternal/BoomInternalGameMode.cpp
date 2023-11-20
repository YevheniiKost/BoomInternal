// Copyright Epic Games, Inc. All Rights Reserved.

#include "BoomInternalGameMode.h"
#include "BoomInternalCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABoomInternalGameMode::ABoomInternalGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
