#include "BoomWeaponComponent.h"

#include "AnimationHandler.h"
#include "WeaponData.h"
#include "WeaponModel.h"
#include "InputHandler.h"
#include "WeaponSystemSettings.h"


UBoomWeaponComponent::UBoomWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UBoomWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBoomWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType,
										 FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UBoomWeaponComponent::SetWeaponMeshComponent(USkeletalMeshComponent* MeshComponent)
{
	WeaponMeshComponent = MeshComponent;
	SetWeapon(GetDefaultWeaponData());
}

void UBoomWeaponComponent::SetInputHandler(IInputHandler* Handler)
{
	Handler->GetFireHoldEvent()->AddUObject(this, &UBoomWeaponComponent::OnFireHold);
	Handler->GetFireReleaseEvent()->AddUObject(this, &UBoomWeaponComponent::OnFireRelease);
	Handler->GetAdditionalFireHoldEvent()->AddUObject(this, &UBoomWeaponComponent::OnAdditionalFireHold);
	Handler->GetAdditionalFireReleaseEvent()->AddUObject(this, &UBoomWeaponComponent::OnAdditionalFireRelease);
	Handler->GetWeaponSwitchEvent()->AddUObject(this, &UBoomWeaponComponent::OnWeaponSwitch);
}

UWeaponData* UBoomWeaponComponent::GetDefaultWeaponData()
{
	return GetWeaponDataByType(EWeaponType::WT_Shotgun);
}

UWeaponSystemSettings* UBoomWeaponComponent::GetWeaponSystemSettings() const
{
	return WeaponSystemSettings->GetDefaultObject<UWeaponSystemSettings>();
}

void UBoomWeaponComponent::StartFireTimer()
{
	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &UBoomWeaponComponent::OnFireTimerFinished,
	                                       CurrentWeaponModel->GetWeaponData()->GetFireRate(), false);
}

void UBoomWeaponComponent::OnFireTimerFinished()
{
	if(CurrentWeaponModel)
	{
		CurrentWeaponModel->OnFireTimerFinished();
	}
}

void UBoomWeaponComponent::OnFireHold()
{
	UE_LOG(LogTemp, Warning, TEXT("OnFireHold"));
	if(CurrentWeaponModel && CurrentWeaponModel->CanFire())
	{
		CurrentWeaponModel->Fire();
		StartFireTimer();
	}
}

void UBoomWeaponComponent::OnFireRelease()
{
}

void UBoomWeaponComponent::OnAdditionalFireHold()
{
}

void UBoomWeaponComponent::OnAdditionalFireRelease()
{
}

bool UBoomWeaponComponent::CanSwitch(int WeaponIndex)
{
	
	//is alive etc
	return true;
}

void UBoomWeaponComponent::SwitchWeapon(int WeaponIndex)
{
	UWeaponData* Data = GetWeaponDataByIndex(WeaponIndex);
	if(CurrentWeaponModel)
	{
		if(CurrentWeaponModel->GetWeaponData() == Data)
		{
			//already have this weapon
			return;
		}
	}
	
	if(Data)
	{
		SetWeapon(Data);
	}
}

void UBoomWeaponComponent::OnWeaponSwitch(int WeaponIndex)
{
	if(CanSwitch(WeaponIndex))
	{
		SwitchWeapon(WeaponIndex);
	}
}

void UBoomWeaponComponent::SetWeapon(UWeaponData* Data)
{
	if(!WeaponSystemSettings)
	{
		UE_LOG(LogTemp, Error, TEXT("WeaponSystemSettings is null"));
		return;
	}
	
	if(WeaponModels.Contains(Data->GetWeaponIndex()))
	{
		CurrentWeaponModel = WeaponModels[Data->GetWeaponIndex()];
	}else
	{
		CurrentWeaponModel = NewObject<UWeaponModel>();
		CurrentWeaponModel->Init(Data);
	}

	CurrentWeaponIndex = Data->GetWeaponIndex();

	const float AnimationDuration = GetWeaponSystemSettings()->GetWeaponSwitchTime() / 2;
	AnimationHandler->PlayMontageSection(GetWeaponSystemSettings()->GetLowerRaiseMontage(),
		AnimationDuration,
		GetWeaponSystemSettings()->GetLowerWeaponSectionName());
	
	GetWorld()->GetTimerManager().SetTimer(AnimationLowerRaiseTimerHandle,
		this,
		&UBoomWeaponComponent::OnLowerAnimationFinished,
		AnimationDuration, false);
}

void UBoomWeaponComponent::OnLowerAnimationFinished()
{
	
	WeaponMeshComponent->SetSkeletalMesh(CurrentWeaponModel->GetWeaponData()->GetSkeletalMesh());
	AnimationHandler->PlayMontageSection(GetWeaponSystemSettings()->GetLowerRaiseMontage(),
		GetWeaponSystemSettings()->GetWeaponSwitchTime() / 2,
		GetWeaponSystemSettings()->GetRaiseWeaponSectionName());
}

UWeaponData* UBoomWeaponComponent::GetWeaponDataByType(const EWeaponType Type)
{
	if(!WeaponSystemSettings)
	{
		UE_LOG(LogTemp, Error, TEXT("WeaponSystemSettings is null"));
		return nullptr;
	}
	
	for (const auto DataElement : GetWeaponSystemSettings()->GetWeaponDataList())
	{
		if(DataElement)
		{
			if (DataElement->GetDefaultObject<UWeaponData>()->GetWeaponType() == Type)
			{
				return DataElement->GetDefaultObject<UWeaponData>();
			}
		}
	}
	return nullptr;
}

UWeaponData* UBoomWeaponComponent::GetWeaponDataByIndex(int WeaponIndex)
{
	if(!WeaponSystemSettings)
	{
		UE_LOG(LogTemp, Error, TEXT("WeaponSystemSettings is null"));
		return nullptr;
	}
	
	for (const auto DataElement : GetWeaponSystemSettings()->GetWeaponDataList())
	{
		if(DataElement)
		{
			if (DataElement->GetDefaultObject<UWeaponData>()->GetWeaponIndex() == WeaponIndex)
			{
				return DataElement->GetDefaultObject<UWeaponData>();
			}
		}
	}
	return nullptr;
}



