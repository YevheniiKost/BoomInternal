#include "CharacterInputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


UCharacterInputComponent::UCharacterInputComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterInputComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCharacterInputComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCharacterInputComponent::SetInputComponent(UInputComponent* InputComponent, const APlayerController* PlayerController)
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(MovementMappingContext, 0);
		Subsystem->AddMappingContext(CombatMappingContext, 1);
		Subsystem->AddMappingContext(WeaponSwitchMappingContext, 2);

		UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	}
	
	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(EnhancedInputComponent, TEXT("Character does not have an EnhancedInputComponent"));
	checkf(JumpAction, TEXT("Character does not have a JumpAction"));
	checkf(MoveAction, TEXT("Character does not have a MoveAction"));
	checkf(LookAction, TEXT("Character does not have a LookAction"));
	checkf(DashAction, TEXT("Character does not have a DashAction"));
	checkf(UseAction, TEXT("Character does not have a UseAction"));
	checkf(FireAction, TEXT("Character does not have a FireAction"));
	checkf(AdditionalFireAction, TEXT("Character does not have a AdditionalFireAction"));

	EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UCharacterInputComponent::OnFireAction);
	EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &UCharacterInputComponent::OnFireReleaseAction);
	EnhancedInputComponent->BindAction(AdditionalFireAction, ETriggerEvent::Triggered, this, &UCharacterInputComponent::OnAdditionalFireAction);
	EnhancedInputComponent->BindAction(AdditionalFireAction, ETriggerEvent::Completed, this, &UCharacterInputComponent::OnAdditionalFireReleaseAction);
	
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &UCharacterInputComponent::OnLookAction);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &UCharacterInputComponent::OnMoveAction);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &UCharacterInputComponent::OnJumpAction);
	EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &UCharacterInputComponent::OnDashAction);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &UCharacterInputComponent::OnMoveReleaseAction);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &UCharacterInputComponent::OnJumpReleaseAction);
	EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Completed, this, &UCharacterInputComponent::OnDashReleaseAction);
	EnhancedInputComponent->BindAction(UseAction, ETriggerEvent::Triggered, this, &UCharacterInputComponent::OnUseAction);
	EnhancedInputComponent->BindAction(UseAction, ETriggerEvent::Completed, this, &UCharacterInputComponent::OnUseReleaseAction);

	EnhancedInputComponent->BindAction(WeaponSwitchAction1, ETriggerEvent::Started, this, &UCharacterInputComponent::OnWeaponSwitchAction1);
	EnhancedInputComponent->BindAction(WeaponSwitchAction2, ETriggerEvent::Started, this, &UCharacterInputComponent::OnWeaponSwitchAction2);
	EnhancedInputComponent->BindAction(WeaponSwitchAction3, ETriggerEvent::Started, this, &UCharacterInputComponent::OnWeaponSwitchAction3);
	EnhancedInputComponent->BindAction(WeaponSwitchAction4, ETriggerEvent::Started, this, &UCharacterInputComponent::OnWeaponSwitchAction4);
	EnhancedInputComponent->BindAction(WeaponSwitchAction5, ETriggerEvent::Started, this, &UCharacterInputComponent::OnWeaponSwitchAction5);
	EnhancedInputComponent->BindAction(WeaponSwitchAction6, ETriggerEvent::Started, this, &UCharacterInputComponent::OnWeaponSwitchAction6);
}

void UCharacterInputComponent::OnMoveAction(const FInputActionValue& Value)
{
	const FVector2D MoveValue = Value.Get<FVector2D>();
	MoveActionDelegate.Broadcast(MoveValue);
}

void UCharacterInputComponent::OnLookAction(const FInputActionValue& Value)
{
	const FVector2D LookValue = Value.Get<FVector2D>();
	LookActionDelegate.Broadcast(LookValue);
}

void UCharacterInputComponent::OnFireAction()
{
	FireHoldDelegate.Broadcast();
}

void UCharacterInputComponent::OnFireReleaseAction()
{
	FireReleaseDelegate.Broadcast();
}

void UCharacterInputComponent::OnAdditionalFireAction()
{
	AdditionalFireHoldDelegate.Broadcast();
}

void UCharacterInputComponent::OnAdditionalFireReleaseAction()
{
	AdditionalFireReleaseDelegate.Broadcast();
}

void UCharacterInputComponent::OnJumpAction(const FInputActionValue& Value)
{
	JumpTriggerDelegate.Broadcast();
}

void UCharacterInputComponent::OnDashAction(const FInputActionValue& Value)
{
	DashTriggerDelegate.Broadcast();
}

void UCharacterInputComponent::OnMoveReleaseAction(const FInputActionValue& Value)
{
	MoveReleaseDelegate.Broadcast();
}

void UCharacterInputComponent::OnJumpReleaseAction(const FInputActionValue& Value)
{
	JumpReleaseDelegate.Broadcast();
}

void UCharacterInputComponent::OnDashReleaseAction(const FInputActionValue& Value)
{
	DashReleaseDelegate.Broadcast();
}

void UCharacterInputComponent::OnUseAction()
{
	UseTriggerDelegate.Broadcast();
}

void UCharacterInputComponent::OnUseReleaseAction()
{
	UseReleaseDelegate.Broadcast();
}

void UCharacterInputComponent::OnWeaponSwitchAction1()
{
	WeaponSwitchDelegate.Broadcast(1);
}

void UCharacterInputComponent::OnWeaponSwitchAction2()
{
	WeaponSwitchDelegate.Broadcast(2);
}

void UCharacterInputComponent::OnWeaponSwitchAction3()
{
	WeaponSwitchDelegate.Broadcast(3);
}

void UCharacterInputComponent::OnWeaponSwitchAction4()
{
	WeaponSwitchDelegate.Broadcast(4);
}

void UCharacterInputComponent::OnWeaponSwitchAction5()
{
	WeaponSwitchDelegate.Broadcast(5);
}

void UCharacterInputComponent::OnWeaponSwitchAction6()
{
	WeaponSwitchDelegate.Broadcast(6);
}



