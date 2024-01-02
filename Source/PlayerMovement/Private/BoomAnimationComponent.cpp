#include "BoomAnimationComponent.h"
#include "MovementHandler.h"
#include "GameFramework/Character.h"


UBoomAnimationComponent::UBoomAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UBoomAnimationComponent::SetMovementHandler(IMovementHandler* NewMovementHandler)
{
	MovementHandler = NewMovementHandler;
	MovementHandler->GetOnHangLedgeEvent()->AddUObject(this, &UBoomAnimationComponent::OnHangLedge);
}

void UBoomAnimationComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBoomAnimationComponent::OnHangLedge()
{
	const USkeletalMeshComponent* Mesh = Character->GetMesh();
	UAnimInstance* AnimInstance = Mesh->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->Montage_Play(HangLedgeMontage);
	}
}


void UBoomAnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

