#include "PullUpState.h"

#include "StateManagerComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "PlayerMovement/BoomMovementComponent.h"
#include "PlayerMovement/MovementConfig.h"

class UCapsuleComponent;

void UPullUpState::TickState(float DeltaTime)
{
	Super::TickState(DeltaTime);

	const FVector ClimbLocation = MovementComponent->GetClimbLocation();
	
	DrawDebugSphere(GetWorld(), ClimbLocation, 10.f, 10, FColor::Red, false, 0.1f, 0, 1.f);

	FVector ClimbDirection = ClimbLocation - Character->GetActorLocation();
	ClimbDirection.Normalize();
	Character->AddActorWorldOffset(ClimbDirection * ClimbSpeed * DeltaTime, true);

	const FVector ForwardVector = Character->GetActorForwardVector();
	Character->SetActorRotation(ForwardVector.Rotation());

	if (FVector::Distance(Character->GetActorLocation(), ClimbLocation) < ClimbPositionThreshold)
	{
		StateManagerComponent->SwitchStateByKey(MovementConfig::IdleMovementStateName);
	}
}

void UPullUpState::OnEnterState(AActor* Owner)
{
	Super::OnEnterState(Owner);

	Character->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	Character->GetCharacterMovement()->StopMovementImmediately();

	UCapsuleComponent* Capsule = Character->GetCapsuleComponent();
	Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UPullUpState::OnExitState()
{
	Super::OnExitState();

	UCapsuleComponent* Capsule = Character->GetCapsuleComponent();
	Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Character->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}
