#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "InputHandler.h"
#include "Components/ActorComponent.h"
#include "CharacterInputComponent.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PLAYERINPUTCONTROLLER_API UCharacterInputComponent : public UActorComponent, public IInputHandler
{
	GENERATED_BODY()

public:
	UCharacterInputComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
	void SetInputComponent(UInputComponent* InputComponent, const APlayerController* PlayerController);

	virtual FInputActionEvent* GetFireHoldEvent() override { return &FireHoldDelegate; }
	virtual FInputActionEvent* GetFireReleaseEvent() override { return &FireReleaseDelegate; }

	virtual FInputActionEvent* GetAdditionalFireHoldEvent() override { return &AdditionalFireHoldDelegate; }
	virtual FInputActionEvent* GetAdditionalFireReleaseEvent() override { return &AdditionalFireReleaseDelegate; }

	virtual FInputActionEventVector2D* GetMoveActionEvent() override { return &MoveActionDelegate; }
	virtual FInputActionEvent* GetMoveReleaseEvent() override { return &MoveReleaseDelegate; }

	virtual FInputActionEventVector2D* GetLookActionEvent() override { return &LookActionDelegate; }

	virtual FInputActionEvent* GetJumpTriggerEvent() override { return &JumpTriggerDelegate; }
	virtual FInputActionEvent* GetJumpReleaseEvent() override { return &JumpReleaseDelegate; }

	virtual FInputActionEvent* GetDashTriggerEvent() override { return &DashTriggerDelegate; }
	virtual FInputActionEvent* GetDashReleaseEvent() override { return &DashReleaseDelegate; }

	virtual FInputActionEvent* GetUseTriggerEvent() override { return &UseTriggerDelegate; }
	virtual FInputActionEvent* GetUseReleaseEvent() override { return &UseReleaseDelegate; }

	virtual FInputActionEventInt* GetWeaponSwitchEvent() override { return &WeaponSwitchDelegate; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* MovementMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* CombatMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* WeaponSwitchMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* DashAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* UseAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* AdditionalFireAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Change")
	UInputAction* WeaponSwitchAction1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Change")
	UInputAction* WeaponSwitchAction2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Change")
	UInputAction* WeaponSwitchAction3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Change")
	UInputAction* WeaponSwitchAction4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Change")
	UInputAction* WeaponSwitchAction5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Change")
	UInputAction* WeaponSwitchAction6;

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent;

	FInputActionEvent FireHoldDelegate;
	FInputActionEvent FireReleaseDelegate;
	FInputActionEvent AdditionalFireHoldDelegate;
	FInputActionEvent AdditionalFireReleaseDelegate;

	FInputActionEventVector2D MoveActionDelegate;
	FInputActionEvent MoveReleaseDelegate;
	FInputActionEventVector2D LookActionDelegate;
	FInputActionEvent JumpTriggerDelegate;
	FInputActionEvent JumpReleaseDelegate;
	FInputActionEvent DashTriggerDelegate;
	FInputActionEvent DashReleaseDelegate;

	FInputActionEvent UseTriggerDelegate;
	FInputActionEvent UseReleaseDelegate;

	FInputActionEventInt WeaponSwitchDelegate;

	void OnFireAction();
	void OnFireReleaseAction();
	void OnAdditionalFireAction();
	void OnAdditionalFireReleaseAction();

	void OnJumpAction(const FInputActionValue& Value);
	void OnMoveAction(const FInputActionValue& Value);
	void OnLookAction(const FInputActionValue& Value);
	void OnDashAction(const FInputActionValue& Value);
	void OnMoveReleaseAction(const FInputActionValue& Value);
	void OnJumpReleaseAction(const FInputActionValue& Value);
	void OnDashReleaseAction(const FInputActionValue& Value);
	void OnUseAction();
	void OnUseReleaseAction();

	void OnWeaponSwitchAction1();
	void OnWeaponSwitchAction2();
	void OnWeaponSwitchAction3();
	void OnWeaponSwitchAction4();
	void OnWeaponSwitchAction5();
	void OnWeaponSwitchAction6();
};
