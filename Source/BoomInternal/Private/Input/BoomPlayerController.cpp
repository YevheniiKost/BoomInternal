#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "BoomInternal/Public/Input/BoomPlayerController.h"
#include "BoomInternal/Public/PlayerCharacter/BoomCharacter.h"

void ABoomInternalPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	BoomCharacter = Cast<ABoomCharacter>(InPawn);
	checkf(BoomCharacter, TEXT("Possessed pawn is not a BoomCharacter"));

	EnhancedInputComponent = Cast<UEnhancedInputComponent>(BoomCharacter->InputComponent);
	checkf(EnhancedInputComponent, TEXT("Character does not have an EnhancedInputComponent"));

	if(JumpAction)
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ABoomInternalPlayerController::OnJumpAction);
	}

	if(MoveAction)
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABoomInternalPlayerController::OnMoveAction);
	}

	if(LookAction)
	{
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABoomInternalPlayerController::OnLookAction);
	}
}

void ABoomInternalPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);

		UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	}
}

void ABoomInternalPlayerController::OnJumpAction(const FInputActionValue& Value)
{
	BoomCharacter->Jump();
}

void ABoomInternalPlayerController::OnMoveAction(const FInputActionValue& Value)
{
	BoomCharacter->Move(Value);
}

void ABoomInternalPlayerController::OnLookAction(const FInputActionValue& Value)
{
	BoomCharacter->Look(Value);
}
