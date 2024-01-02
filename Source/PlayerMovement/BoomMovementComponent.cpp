#include "BoomMovementComponent.h"
#include "InputHandler.h"

#include "GameFramework/Character.h"

#include "DrawDebugHelpers.h"
#include "StateManagerComponent.h"
#include "Interfaces/MovementStateInterface.h"


UBoomMovementComponent::UBoomMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBoomMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBoomMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UBoomMovementComponent::SetCharacter(ACharacter* NewCharacter)
{
	checkf(NewCharacter, TEXT("CharacterMovementComponent::SetCharacter: NewCharacter is null"));
	Character = NewCharacter;
	Controller = Character->Controller;
	DashDirection = Character->GetActorForwardVector();
	Character->JumpMaxCount = 2;
}

void UBoomMovementComponent::SetInputComponent(IInputHandler* InputHandler)
{
	InputComponent = InputHandler;
	InputComponent->GetMoveActionEvent()->AddUObject(this, &UBoomMovementComponent::Move);
	InputComponent->GetLookActionEvent()->AddUObject(this, &UBoomMovementComponent::Look);
	InputComponent->GetJumpTriggerEvent()->AddUObject(this, &UBoomMovementComponent::Jump);
	InputComponent->GetDashTriggerEvent()->AddUObject(this, &UBoomMovementComponent::Dash);
	InputComponent->GetMoveReleaseEvent()->AddUObject(this, &UBoomMovementComponent::MoveRelease);
	InputComponent->GetDashReleaseEvent()->AddUObject(this, &UBoomMovementComponent::DashRelease);
	InputComponent->GetJumpReleaseEvent()->AddUObject(this, &UBoomMovementComponent::JumpRelease);
	InputComponent->GetUseTriggerEvent()->AddUObject(this, &UBoomMovementComponent::UseTriggered);
	InputComponent->GetUseReleaseEvent()->AddUObject(this, &UBoomMovementComponent::UseReleased);
}

void UBoomMovementComponent::SetMovementStateManager(UStateManagerComponent* NewStateManager)
{
	StateManager = NewStateManager;
	StateManager->InitStateManager();
}

void UBoomMovementComponent::Look(const FVector2D InputDirection)
{
	UStateBase* CurrentState = StateManager->CurrentState;
	if(!CurrentState) return;

	if(IMovementStateInterface* MovementStateInterface = Cast<IMovementStateInterface>(CurrentState))
	{
		MovementStateInterface->OnLookInput(InputDirection);
	}
}

void UBoomMovementComponent::Move(const FVector2D InputDirection)
{
	UStateBase* CurrentState = StateManager->CurrentState;
	if(!CurrentState) return;

	if(IMovementStateInterface* MovementStateInterface = Cast<IMovementStateInterface>(CurrentState))
	{
		MovementStateInterface->OnMoveInput(InputDirection);
	}
}

void UBoomMovementComponent::Jump() const
{
	UStateBase* CurrentState = StateManager->CurrentState;
	if(!CurrentState) return;

	if(IMovementStateInterface* MovementStateInterface = Cast<IMovementStateInterface>(CurrentState))
	{
		MovementStateInterface->OnJumpInput();
	}
}

void UBoomMovementComponent::Dash()
{
	UStateBase* CurrentState = StateManager->CurrentState;
	if(!CurrentState) return;

	if(IMovementStateInterface* MovementStateInterface = Cast<IMovementStateInterface>(CurrentState))
	{
		MovementStateInterface->OnDashInput();
	}
}

void UBoomMovementComponent::MoveRelease()
{
	DashDirection = Character->GetActorForwardVector();
}

void UBoomMovementComponent::DashRelease()
{
}

void UBoomMovementComponent::JumpRelease()
{
}

void UBoomMovementComponent::UseTriggered()
{
	UStateBase* CurrentState = StateManager->CurrentState;
	if(!CurrentState) return;

	if(IMovementStateInterface* MovementStateInterface = Cast<IMovementStateInterface>(CurrentState))
	{
		MovementStateInterface->UseTriggered();
	}
}

void UBoomMovementComponent::UseReleased()
{
	UStateBase* CurrentState = StateManager->CurrentState;
	if(!CurrentState) return;

	if(IMovementStateInterface* MovementStateInterface = Cast<IMovementStateInterface>(CurrentState))
	{
		MovementStateInterface->UseReleased();
	}
}




