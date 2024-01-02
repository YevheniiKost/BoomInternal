// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "WeaponData.generated.h"

UENUM()
enum class EAmmoType : uint8
{
	None UMETA(DisplayName = "None"),
	AT_Shotgun UMETA(DisplayName = "Shotgun Ammo"),
	AT_Rifle UMETA(DisplayName = "Rifle Ammo"),
	AT_Energy UMETA(DisplayName = "Energy Blast"),
	AT_Rocket UMETA(DisplayName = "Rocket"),
	AT_Bfg UMETA(DisplayName = "BFG")
};

UENUM()
enum class EWeaponType : uint8
{
	None UMETA(DisplayName = "None"),
	WT_Shotgun UMETA(DisplayName = "Shotgun"),
	WT_Handgun UMETA(DisplayName = "Handgun"),
	WT_EnergyBlaster UMETA(DisplayName = "Energy Blaster"),
	WT_RocketLauncher UMETA(DisplayName = "Rocket Launcher"),
	WT_SuperShotgun UMETA(DisplayName = "Super Shotgun"),
	WT_MachineGun UMETA(DisplayName = "Machine Gun"),
	WT_Ballista UMETA(DisplayName = "Ballista"),
	WT_BFG UMETA(DisplayName = "BFG")
};

class USkeletalMesh;

UCLASS(Blueprintable)
class COMBAT_API UWeaponData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
    int GetWeaponIndex() const { return WeaponIndex; }
	FName GetWeaponName() const { return WeaponName; }
	
	int GetStartAmmo() const { return StartAmmo; }
	int GetMaxAmmo() const { return MaxAmmo; }
	int GetAmmoPerShot() const { return AmmoPerShot; }
	float GetFireRate() const { return FireRate; }
	int GetBaseDamagePerAmmo() const { return BaseDamagePerAmmo; }
	EAmmoType GetAmmoType() const { return AmmoType; }
	EWeaponType GetWeaponType() const { return WeaponType; }
	TObjectPtr<USkeletalMesh> GetSkeletalMesh() const { return SkeletalMesh; }

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "General")
	int WeaponIndex = 0;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "General")
	FName WeaponName = "";
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon")
	int StartAmmo = 0;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon")
	int MaxAmmo = 0;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon")
	int AmmoPerShot = 0;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon")
	float FireRate = 0.f;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon")
	int BaseDamagePerAmmo = 1;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon")
	EAmmoType AmmoType = EAmmoType::None;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon")
	EWeaponType WeaponType = EWeaponType::None;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon")
	TObjectPtr<USkeletalMesh> SkeletalMesh;

	//Something with special abilities
	
};
