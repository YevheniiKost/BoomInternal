#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BoomAnimationComponent.generated.h"

class IMovementHandler;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PLAYERMOVEMENT_API UBoomAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBoomAnimationComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE void SetCharacter(ACharacter* NewCharacter) { Character = NewCharacter; }
	void SetMovementHandler(IMovementHandler* NewMovementHandler);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animation")
	UAnimMontage* HangLedgeMontage;

private:
	TObjectPtr<ACharacter> Character;
	IMovementHandler* MovementHandler;

	void OnHangLedge();
};
