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

UENUM(BlueprintType)
enum ECustomMovementMode
{
	CMOVE_None		UMETA(Hidden),
	CMOVE_Slide		UMETA(DisplayName = "Slide"),
	CMOVE_WallRun	UMETA(DisplayName = "Wall Run"),
	CMOVE_MAX		UMETA(Hidden),
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
		uint8 Saved_bWallRunIsRight:1;
		
	
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
	bool Safe_bWallRunIsRight;
	
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

	UFUNCTION(BlueprintPure)
	bool IsSliding();
	
	UFUNCTION(BlueprintPure)
	bool IsWallRunning() const { return IsCustomMovementMode(CMOVE_WallRun); }
	UFUNCTION(BlueprintPure)
	bool WallRunningIsRight() const { return Safe_bWallRunIsRight; }
	
	virtual bool CanAttemptJump() const override;
	virtual bool DoJump(bool bReplayingMoves) override;
	
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

	// Wall Run
	UPROPERTY(EditDefaultsOnly)
	float MinWallRunSpeed=200.f;
	UPROPERTY(EditDefaultsOnly)
	float MaxWallRunSpeed=800.f;
	UPROPERTY(EditDefaultsOnly)
	float MaxVerticalWallRunSpeed=200.f;
	UPROPERTY(EditDefaultsOnly)
	float WallRunPullAwayAngle=75;
	UPROPERTY(EditDefaultsOnly)
	float WallAttractionForce = 200.f;
	UPROPERTY(EditDefaultsOnly)
	float MinWallRunHeight=50.f;
	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* WallRunGravityScaleCurve;
	UPROPERTY(EditDefaultsOnly)
	float WallJumpOffForce = 300.f;
	
	UPROPERTY(Transient)
	APlayerCharacter* DashCharacterOwner;

	// Slide
	void EnterSlide();
	void ExitSlide();
	bool CanSlide();
	void PhysSlide(float DeltaTime, int32 Iterations);

	// Sprint
	bool CanSprint() const;


	// Wall Run
	bool TryWallRun();
	void PhysWallRun(float deltaTime, int32 Iterations);

	FDashCharacterGroundInfo CachedGroundInfo;

	float CapR() const;
	float CapHH() const;
};
