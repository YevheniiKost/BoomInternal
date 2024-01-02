#include "ClimbingState.h"

#include "StateManagerComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PlayerMovement/MovementConfig.h"

void UClimbingState::OnEnterState(AActor* Owner)
{
	Super::OnEnterState(Owner);

	Character->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	Character->GetCharacterMovement()->StopMovementImmediately();
	Character->GetCharacterMovement()->MaxFlySpeed = ClimbingSpeed;
	Character->bUseControllerRotationYaw = false;
}


void UClimbingState::TickState(float DeltaTime)
{
	Super::TickState(DeltaTime);
	
	FHitResult HitResult;

	RotateToWall(DeltaTime, HitResult);
	KeepDistanceToWall(DeltaTime, HitResult);
}

void UClimbingState::OnExitState()
{
	Super::OnExitState();

	Character->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	Character->bUseControllerRotationYaw = true;
}

void UClimbingState::OnLookInput(const FVector2D Input)
{
	Super::OnLookInput(Input);
	ProcessLook(Input);
}

void UClimbingState::OnMoveInput(const FVector2D Input)
{
	Super::OnMoveInput(Input);
	this->InputDirection = Input;

	const FVector ActorUp = Character->GetActorUpVector();
	const FVector ActorRight = Character->GetActorRightVector();

	float VerticalInput = Input.Y;
	float HorizontalInput = Input.X;

	const FVector UpCheckLocation = Character->GetActorLocation() + ActorUp * UpCheckDistance;
	const FVector DownCheckLocation = Character->GetActorLocation() - ActorUp * DownCheckDistance;
	const FVector LeftCheckLocation = Character->GetActorLocation() - ActorRight * SideCheckDistance;
	const FVector RightCheckLocation = Character->GetActorLocation() + ActorRight * SideCheckDistance;

	FHitResult HitResult;
	if(!CheckClimbSurface(UpCheckLocation, HitResult))
	{
		VerticalInput = FMath::Clamp(VerticalInput, -1.f, 0.f);
	}

	if(!CheckClimbSurface(DownCheckLocation, HitResult))
	{
		VerticalInput = FMath::Clamp(VerticalInput, 0.f, 1.f);
	}

	if(!CheckClimbSurface(LeftCheckLocation, HitResult))
	{
		HorizontalInput = FMath::Clamp(HorizontalInput, 0.f, 1.f);
	}

	if(!CheckClimbSurface(RightCheckLocation, HitResult))
	{
		HorizontalInput = FMath::Clamp(HorizontalInput, -1.f, 0.f);
	}

	Character->AddMovementInput(ActorUp, VerticalInput);
	Character->AddMovementInput(ActorRight, HorizontalInput);
}

void UClimbingState::OnJumpInput()
{
	Super::OnJumpInput();
	APlayerCameraManager* CameraManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	const FVector LaunchDirection = CameraManager->GetCameraRotation().Vector();
	Character->LaunchCharacter(LaunchDirection * LaunchForce, false, true);
	StateManagerComponent->SwitchStateByKey(MovementConfig::IdleMovementStateName);
}


bool UClimbingState::CheckClimbSurface(const FVector& StartLocation, FHitResult& HitResult) const
{
	const FVector EndLocation = StartLocation + Character->GetActorForwardVector() * ForwardTraceDistance;

	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(Character);

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(Character);

	const bool CheckTrace = UKismetSystemLibrary::SphereTraceSingle(
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

	return CheckTrace && HitResult.GetActor()->Tags.Contains(MovementConfig::ClimbableSurfaceTag);
}

void UClimbingState::RotateToWall(float DeltaTime, FHitResult HitResult)
{
	if(CheckClimbSurface(Character->GetActorLocation(), HitResult))
	{
		FVector SurfaceNormal = HitResult.Normal * -1.f;
		SurfaceNormal.Normalize();
		FRotator CurrentRotation = Character->GetActorRotation();
		FRotator DesiredRotation = SurfaceNormal.Rotation();
		FRotator SmoothRotation = FMath::RInterpTo(CurrentRotation, DesiredRotation, DeltaTime, 2.0f);
		Character->SetActorRotation(SmoothRotation);
	}
}

void UClimbingState::KeepDistanceToWall(float DeltaTime, FHitResult HitResult)
{
	const float CurrentDistance = FVector::Dist(HitResult.ImpactPoint, Character->GetActorLocation());
	const FVector DirectionToWall = (HitResult.ImpactPoint - Character->GetActorLocation()).GetSafeNormal();

	constexpr float DistanceThreshold = 5.f;
	if(CurrentDistance - DistanceToWall > DistanceThreshold)
	{
		Character->AddActorWorldOffset(DirectionToWall * DeltaTime * ClimbingSpeed, true);
	}else if(CurrentDistance - DistanceToWall < -DistanceThreshold)
	{
		Character->AddActorWorldOffset(DirectionToWall * DeltaTime * -ClimbingSpeed, true);
	}
}
