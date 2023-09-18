// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DashCharacterMovementComponent.generated.h"

class APlayerCharacter;

USTRUCT(BlueprintType)
struct FDashCharacterGroundInfo
{
	GENERATED_BODY()

	FDashCharacterGroundInfo()
		: LastUpdateFrame(0.0f)
		, GroundDistance(0.0f)
	{}
	
	uint64 LastUpdateFrame;

	UPROPERTY(BlueprintReadOnly)
	FHitResult GroundHitResult;

	UPROPERTY(BlueprintReadOnly)
	float GroundDistance;
};

UENUM()
enum ECustomMovementMode
{
	CMOVE_None	UMETA(Hidden),
	CMOVE_Slide UMETA(DisplayName = "Slide"),
	CMOVE_MAX	UMETA(Hidden),
};

UCLASS()
class DASH_API UDashCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

	class FSavedMove_Dash : public FSavedMove_Character
	{
	public:
		typedef FSavedMove_Character Super;

		uint8 Saved_bWantsToSprint:1;
		
	
		FSavedMove_Dash();
		
		virtual bool CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const override;
		virtual void Clear() override;
		virtual uint8 GetCompressedFlags() const override;
		virtual void SetMoveFor(ACharacter* C, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData) override;
		virtual void PrepMoveFor(ACharacter* C) override;
	};

	class FNetworkPredictionData_Client_Dash : public FNetworkPredictionData_Client_Character
	{
	public:
		FNetworkPredictionData_Client_Dash(const UCharacterMovementComponent& ClientMovement);

		typedef FNetworkPredictionData_Client_Character Super;

		virtual FSavedMovePtr AllocateNewMove() override;
	};
	
	bool Safe_bWantsToSprint;
	
public:
	virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;
	
protected:
	virtual void UpdateFromCompressedFlags(uint8 Flags) override;
	
public:
	UDashCharacterMovementComponent();
	
	void SprintPressed();
	void SprintReleased();
	
	virtual float GetMaxBrakingDeceleration() const override;
	virtual float GetMaxSpeed() const override;
	
	bool IsCustomMovementMode(ECustomMovementMode InCustomMovementMode) const
	{
		return MovementMode == MOVE_Custom && CustomMovementMode == InCustomMovementMode;
	};
	
	virtual bool IsMovingOnGround() const override;
	virtual bool CanCrouchInCurrentState() const override;
	
	UFUNCTION(BlueprintCallable)
	const FDashCharacterGroundInfo& GetGroundInfo();
	
	UFUNCTION(BlueprintPure)
	bool IsMovementMode(EMovementMode InMovementMode) const;

protected:
	virtual void InitializeComponent() override;
	
	virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;
	
	virtual void UpdateCharacterStateBeforeMovement(float DeltaSeconds) override;

	virtual void PhysCustom(float DeltaTime, int32 Iterations) override;
	
private:
	// Sprint
	UPROPERTY(EditDefaultsOnly)
	float MaxSprintSpeed=750.f;
	
	// Slide
	UPROPERTY(EditDefaultsOnly)
	float MinSlideSpeed=720.f;
	UPROPERTY(EditDefaultsOnly)
	float MaxSlideSpeed=400.f;
	UPROPERTY(EditDefaultsOnly)
	float SlideEnterImpulse=400.f;
	UPROPERTY(EditDefaultsOnly)
	float SlideGravityForce=4000.f;
	UPROPERTY(EditDefaultsOnly)
	float SlideFrictionFactor=.06f;
	UPROPERTY(EditDefaultsOnly)
	float BrakingDecelerationSliding=1000.f;
	
	UPROPERTY(Transient)
	APlayerCharacter* DashCharacterOwner;

	void EnterSlide();
	void ExitSlide();
	bool CanSlide();
	void PhysSlide(float DeltaTime, int32 Iterations);
	
	bool CanSprint() const;

	FDashCharacterGroundInfo CachedGroundInfo;
};
