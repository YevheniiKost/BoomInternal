#include "MovementStateBase.h"

#include "GameFramework/Character.h"
#include "PlayerMovement/Interfaces/MovementComponentHolder.h"

void UMovementStateBase::OnEnterState(AActor* Owner)
{
	Super::OnEnterState(Owner);

	if(!Owner)
	{
		return;
	}

	if(ACharacter* CharacterOwner = Cast<ACharacter>(Owner))
	{
		Character = CharacterOwner;
		Controller = Character->GetController();
	}

	if(IMovementComponentHolder* MovementComponentHolder = Cast<IMovementComponentHolder>(Owner))
	{
		MovementComponent = MovementComponentHolder->GetBoomMovementComponent();
	}
}

void UMovementStateBase::ProcessLook(FVector2D InputDirection)
{
	if (Controller)
	{
		Character->AddControllerYawInput(InputDirection.X);
		Character->AddControllerPitchInput(InputDirection.Y);
		MovementComponent->SetDashDirection(Character->GetActorForwardVector());
	}
}

void UMovementStateBase::OnLookInput(const FVector2D InputDirection)
{
}

void UMovementStateBase::OnMoveInput(const FVector2D InputDirection)
{
}

void UMovementStateBase::OnJumpInput()
{
}

void UMovementStateBase::OnDashInput()
{
}

void UMovementStateBase::UseTriggered()
{
}

void UMovementStateBase::UseReleased()
{
}
