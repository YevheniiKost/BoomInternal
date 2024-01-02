#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "WeaponModel.generated.h"

class UWeaponData;

UCLASS()
class COMBAT_API UWeaponModel : public UObject
{
	GENERATED_BODY()

public:
	void Init(UWeaponData* Data);

	bool CanFire();
	void Fire();
	void OnFireTimerFinished();
	void AddAmmo(int Amount);

	int GetCurrentAmmo() const { return CurrentAmmo; }
	UWeaponData* GetWeaponData() const { return WeaponData; }

private:
	TObjectPtr<UWeaponData> WeaponData;

	bool bCanFire = true;
	int CurrentAmmo = 0;
};
