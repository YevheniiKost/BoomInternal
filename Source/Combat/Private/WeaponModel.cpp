#include "WeaponModel.h"
#include "WeaponData.h"
#include "Kismet/KismetMathLibrary.h"


void UWeaponModel::Init(UWeaponData* Data)
{
	if(Data)
	{
		WeaponData = Data;
		CurrentAmmo = WeaponData->GetStartAmmo();
	}
}

bool UWeaponModel::CanFire()
{
	return bCanFire && CurrentAmmo > WeaponData->GetAmmoPerShot();
}

void UWeaponModel::Fire()
{
	if(!CanFire())
	{
		return;
	}
	
	bCanFire = false;
	CurrentAmmo -= WeaponData->GetAmmoPerShot();
}

void UWeaponModel::OnFireTimerFinished()
{
	bCanFire = true;
}

void UWeaponModel::AddAmmo(int Amount)
{
	CurrentAmmo = FMath::Clamp(CurrentAmmo + Amount, 0, WeaponData->GetMaxAmmo());
}
