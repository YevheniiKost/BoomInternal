#pragma once

#include "PlayerMovement/Interfaces/MovementComponentHolder.h"

#include "CoreMinimal.h"
#include "AnimationHandler.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "BoomCharacter.generated.h"

struct FInputActionValue;

class UBoomWeaponComponent;
class UStateManagerComponent;
class UBoomAnimationComponent;
class UBoomMovementComponent;
class ABoomInternalPlayerController;
class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class UCharacterInputComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ABoomCharacter : public ACharacter, public IMovementComponentHolder, public IAnimationHandler
{
	GENERATED_BODY()
public:
	ABoomCharacter();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	UBoomWeaponComponent* GetWeaponComponent();

	virtual UBoomMovementComponent* GetBoomMovementComponent() override { return MovementComponent; }
	virtual void PlayMontageSection(UAnimMontage* MontageToPlay, float PlayDuration, FName StartSectionName) override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UCharacterInputComponent> CharacterInputComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
    TObjectPtr<UBoomMovementComponent> MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	TObjectPtr<UBoomAnimationComponent> AnimationComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	TObjectPtr<UStateManagerComponent> MovementStateManagerComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	TObjectPtr<UBoomWeaponComponent> WeaponComponent;
	
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	TObjectPtr<USkeletalMeshComponent> Mesh1P;

	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DashVelocity = 1000.f;
	
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	virtual void BeginPlay() override;
};

