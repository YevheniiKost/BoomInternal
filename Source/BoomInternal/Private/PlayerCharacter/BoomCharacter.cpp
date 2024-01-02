#include "PlayerCharacter/BoomCharacter.h"

#include "BoomAnimationComponent.h"
#include "CharacterInputComponent.h"
#include "StateManagerComponent.h"
#include "Camera/CameraComponent.h"
#include "Combat/Public/BoomWeaponComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "PlayerMovement/BoomMovementComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ABoomCharacter::ABoomCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetupAttachment(Mesh1P, FName("weaponSocket_r"));

	CharacterInputComponent = CreateDefaultSubobject<UCharacterInputComponent>(TEXT("Character Input Component"));
	MovementComponent = CreateDefaultSubobject<UBoomMovementComponent>(TEXT("Character Movement Component"));
	AnimationComponent = CreateDefaultSubobject<UBoomAnimationComponent>(TEXT("Character Animation Component"));
	MovementStateManagerComponent = CreateDefaultSubobject<UStateManagerComponent>(TEXT("Movement State Manager Component"));
	WeaponComponent = CreateDefaultSubobject<UBoomWeaponComponent>(TEXT("Weapon Component"));
}

void ABoomCharacter::BeginPlay()
{
	Super::BeginPlay();
	WeaponMesh->AttachToComponent(Mesh1P, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("weaponSocket_r"));
	
	MovementComponent->SetCharacter(this);
	MovementComponent->SetMovementStateManager(MovementStateManagerComponent);
	
	WeaponComponent->SetAnimationHandler(this);
	WeaponComponent->SetWeaponMeshComponent(WeaponMesh);
	WeaponComponent->SetInputHandler(CharacterInputComponent);
}

void ABoomCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(CharacterInputComponent, TEXT("Character does not have an CharacterInputComponent"));

	CharacterInputComponent->SetInputComponent(PlayerInputComponent, Cast<APlayerController>(GetController()));
	MovementComponent->SetInputComponent(CharacterInputComponent);
	
	AnimationComponent->SetCharacter(this);
	AnimationComponent->SetMovementHandler(MovementComponent);
}

void ABoomCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool ABoomCharacter::GetHasRifle()
{
	return bHasRifle;
}

UBoomWeaponComponent* ABoomCharacter::GetWeaponComponent()
{
	return WeaponComponent;
}

void ABoomCharacter::PlayMontageSection(UAnimMontage* MontageToPlay, float PlayDuration, FName StartSectionName)
{
	if(Mesh1P)
	{
		if(UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance())
		{
			const int SectionIndex = MontageToPlay->GetSectionIndex(StartSectionName);
			const float SectionLength = MontageToPlay->GetSectionLength(SectionIndex);
			const float PlayRate = SectionLength / PlayDuration;
			AnimInstance->Montage_Play(MontageToPlay, PlayRate);
			AnimInstance->Montage_JumpToSection(StartSectionName, MontageToPlay);
		}
	}
}
