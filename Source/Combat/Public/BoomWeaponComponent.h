#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BoomWeaponComponent.generated.h"

class UWeaponSystemSettings;
class IAnimationHandler;
class IInputHandler;
enum class EWeaponType : uint8;
class UWeaponModel;
class UWeaponData;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class COMBAT_API UBoomWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBoomWeaponComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

	void SetAnimationHandler(IAnimationHandler* Handler) { AnimationHandler = Handler; }
	void SetWeaponMeshComponent(USkeletalMeshComponent* MeshComponent);
	
	void SetInputHandler(IInputHandler* Handler);

	int GetCurrentWeaponIndex() const { return CurrentWeaponIndex; }
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	int CurrentWeaponIndex = 0;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UWeaponSystemSettings> WeaponSystemSettings;

private:
	IAnimationHandler* AnimationHandler;
	
	IInputHandler* InputHandler;
	TObjectPtr<USkeletalMeshComponent> WeaponMeshComponent;
	TMap<int, UWeaponModel*> WeaponModels = TMap<int, UWeaponModel*>();
	
	UWeaponModel* CurrentWeaponModel;
	FTimerHandle FireTimerHandle;
	FTimerHandle AnimationLowerRaiseTimerHandle;

	UWeaponData* GetWeaponDataByType(EWeaponType Type);
	UWeaponData* GetWeaponDataByIndex(int WeaponIndex);

	UWeaponData* GetDefaultWeaponData();

	UWeaponSystemSettings* GetWeaponSystemSettings() const;

	void StartFireTimer();
	void OnFireTimerFinished();
	
	void OnFireHold();
	void OnFireRelease();
	void OnAdditionalFireHold();
	void OnAdditionalFireRelease();

	bool CanSwitch(int WeaponIndex);
	void SwitchWeapon(int WeaponIndex);
	void OnWeaponSwitch(int WeaponIndex);

	void OnLowerAnimationFinished();
	void SetWeapon(UWeaponData* Data);
};
