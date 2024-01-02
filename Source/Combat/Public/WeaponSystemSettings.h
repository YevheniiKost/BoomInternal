// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponData.h"
#include "UObject/Object.h"
#include "WeaponSystemSettings.generated.h"


UCLASS(Blueprintable)
class COMBAT_API UWeaponSystemSettings : public UObject
{
	GENERATED_BODY()

public:
	TArray<TSubclassOf<UWeaponData>> GetWeaponDataList() const { return WeaponDataList; }
	UAnimMontage* GetLowerRaiseMontage() const { return LowerRaiseMontage; }
	float GetWeaponSwitchTime() const { return WeaponSwitchTime; }
	FName GetLowerWeaponSectionName() const { return LowerWeaponSectionName; }
	FName GetRaiseWeaponSectionName() const { return RaiseWeaponSectionName; }

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "General")
	TArray<TSubclassOf<UWeaponData>> WeaponDataList;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
	UAnimMontage* LowerRaiseMontage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
	float WeaponSwitchTime = 0.5f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
	FName LowerWeaponSectionName = "Lower";

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
	FName RaiseWeaponSectionName = "Raise";
};
