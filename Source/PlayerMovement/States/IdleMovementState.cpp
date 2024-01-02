#include "IdleMovementState.h"

#include "StateManagerComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PlayerMovement/BoomMovementComponent.h"
#include "PlayerMovement/MovementConfig.h"

void UIdleMovementState::OnEnterState(AActor* Owner)
{
	Super::OnEnterState(Owner);
	bUseHold = false;
}

void UIdleMovementState::OnMoveInput(const FVector2D InputDirection)
{
	if (Controller)
	{
		const FVector ActorForward = Character->GetActorForwardVector();
		const FVector ActorRight = Character->GetActorRightVector();
		const FVector DashDirection = FVector(ActorForward.X * InputDirection.Y + ActorRight.X * InputDirection.X,
		                                      ActorForward.Y * InputDirection.Y + ActorRight.Y * InputDirection.X, 0.f);
		MovementComponent->SetDashDirection(DashDirection);
		Character->AddMovementInput(ActorForward, InputDirection.Y);
		Character->AddMovementInput(ActorRight, InputDirection.X);
	}
}

void UIdleMovementState::OnJumpInput()
{
	Character->Jump();
}

void UIdleMovementState::OnDashInput()
{
	StateManagerComponent->SwitchStateByKey(MovementConfig::DashStateName);
}

void UIdleMovementState::OnLookInput(const FVector2D InputDirection)
{
	ProcessLook(InputDirection);
}

void UIdleMovementState::UseTriggered()
{
	Super::UseTriggered();
	bUseHold = true;
}

void UIdleMovementState::UseReleased()
{
	Super::UseReleased();
	bUseHold = false;
}

void UIdleMovementState::TickState(float DeltaTime)
{
	Super::TickState(DeltaTime);

	if (Character->GetMovementComponent()->IsFalling())
	{
		ProcessLedgeDetection();
		ProcessClimbDetection();
	}
}

void UIdleMovementState::ProcessLedgeDetection()
{
	FHitResult HeightHitResult;
	if (HeightTrace(HeightHitResult))
	{
		const FVector CharacterLocation = Character->GetActorLocation();
		const FVector HeightLocation = HeightHitResult.ImpactPoint;
		const float HeightDifference = CharacterLocation.Z - HeightLocation.Z;

		if (HeightDifference > -MaxHeightForClimb && HeightDifference < 0)
		{
			//	OnHangLedgeEvent.Broadcast();

			UCapsuleComponent* Capsule = Character->GetCapsuleComponent();
			FVector ClimbLocation = HeightLocation + Character->GetActorForwardVector() *
				ClimbFinalPositionForwardOffset +
				FVector::UpVector * Capsule->GetScaledCapsuleHalfHeight();
			MovementComponent->SetClimbLocation(ClimbLocation);

			StateManagerComponent->SwitchStateByKey(MovementConfig::PullUpStateName);
		}
	}
}

void UIdleMovementState::ProcessClimbDetection()
{
	FHitResult ForwardHitResult;
	if (ForwardTrace(ForwardHitResult) && ForwardHitResult.GetActor()->Tags.Contains(
		MovementConfig::ClimbableSurfaceTag) && bUseHold)
	{
		StateManagerComponent->SwitchStateByKey(MovementConfig::ClimbStateName);
	}
}

bool UIdleMovementState::HeightTrace(FHitResult& HitResult) const
{
	FVector StartLocation = Character->GetActorLocation();
	const FVector ForwardVector = Character->GetActorForwardVector() * HeightTraceForwardOffset;
	StartLocation += FVector(0.f, 0.f, HeightTraceVerticalOffset);
	StartLocation += ForwardVector;

	const FVector EndLocation = StartLocation - FVector(0.f, 0.f, HeightTraceVerticalOffset);

	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(Character);

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(Character);

	return UKismetSystemLibrary::SphereTraceSingle(
		GetWorld(),
		StartLocation,
		EndLocation,
		TraceSphereRadius,
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::Type::ForOneFrame,
		HitResult,
		true,
		FColor::Green,
		FColor::Red,
		1.f
	);
}

bool UIdleMovementState::ForwardTrace(FHitResult& HitResult) const
{
	const FVector StartLocation = Character->GetActorLocation();
	const FVector EndLocation = StartLocation + Character->GetActorForwardVector() * ForwardTraceDistance;

	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(Character);

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(Character);


	return UKismetSystemLibrary::SphereTraceSingle(
		GetWorld(),
		StartLocation,
		EndLocation,
		15.f,
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::Type::ForOneFrame,
		HitResult,
		true,
		FColor::Green,
		FColor::Red,
		1.f
	);
}
