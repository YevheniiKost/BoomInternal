#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BoomPlayerController.generated.h"

class UInputAction;
class ABoomCharacter;
struct FInputActionValue;
class UInputMappingContext;

UCLASS()
class BOOMINTERNAL_API ABoomInternalPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void OnPossess(APawn* InPawn) override;
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TSubclassOf<ABoomCharacter> CharacterClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	ABoomCharacter* BoomCharacter;

	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent;
	
	void OnJumpAction(const FInputActionValue& Value);
	void OnMoveAction(const FInputActionValue& Value);
	void OnLookAction(const FInputActionValue& Value);
};
