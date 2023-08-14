// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DashCharacterMovementComponent.h"

#include "GameFramework/Character.h"

#pragma region SavedMove

bool UDashCharacterMovementComponent::FSavedMove_Dash::CanCombineWith(const FSavedMovePtr& NewMove,
                                                                      ACharacter* InCharacter, float MaxDelta) const
{
	const FSavedMove_Dash* NewDashMove = static_cast<FSavedMove_Dash*>(NewMove.Get());
	
	if (Saved_bWantsToSprint != NewDashMove->Saved_bWantsToSprint) return false;

	return FSavedMove_Character::CanCombineWith(NewMove, InCharacter, MaxDelta);
}

void UDashCharacterMovementComponent::FSavedMove_Dash::Clear()
{
	FSavedMove_Character::Clear();

	Saved_bWantsToSprint = 0;
}

uint8 UDashCharacterMovementComponent::FSavedMove_Dash::GetCompressedFlags() const
{
	uint8 Result = Super::GetCompressedFlags();

	if(Saved_bWantsToSprint) Result = FLAG_Custom_0;

	return Result;
}

void UDashCharacterMovementComponent::FSavedMove_Dash::SetMoveFor(ACharacter* C, float InDeltaTime,
	FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData)
{
	FSavedMove_Character::SetMoveFor(C, InDeltaTime, NewAccel, ClientData);

	const auto CharacterMovement = Cast<UDashCharacterMovementComponent>(C->GetCharacterMovement());

	Saved_bWantsToSprint = CharacterMovement->Safe_bWantsToSprint;
}

void UDashCharacterMovementComponent::FSavedMove_Dash::PrepMoveFor(ACharacter* C)
{
	Super::PrepMoveFor(C);

	const auto CharacterMovement = Cast<UDashCharacterMovementComponent>(C->GetCharacterMovement());

	CharacterMovement->Safe_bWantsToSprint = Saved_bWantsToSprint;
}

#pragma endregion SavedMove

#pragma region NetworkPredictionData_Client
UDashCharacterMovementComponent::FNetworkPredictionData_Client_Dash::FNetworkPredictionData_Client_Dash(
	const UCharacterMovementComponent& ClientMovement) : Super(ClientMovement)
{
}

FSavedMovePtr UDashCharacterMovementComponent::FNetworkPredictionData_Client_Dash::AllocateNewMove()
{
	return FSavedMovePtr(new FSavedMove_Dash());
}

#pragma endregion NetworkPredictionData_Client

FNetworkPredictionData_Client* UDashCharacterMovementComponent::GetPredictionData_Client() const
{
	check(PawnOwner)
	
	if (!ClientPredictionData)
	{
		auto MutableThis = const_cast<UDashCharacterMovementComponent*>(this);

		MutableThis->ClientPredictionData = new FNetworkPredictionData_Client_Dash(*this);
		MutableThis->ClientPredictionData->MaxSmoothNetUpdateDist = 92.f;
		MutableThis->ClientPredictionData->NoSmoothNetUpdateDist = 140.f;
	}
	return ClientPredictionData;
}

void UDashCharacterMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);

	Safe_bWantsToSprint = (Flags & FSavedMove_Character::FLAG_Custom_0) != 0;
}

void UDashCharacterMovementComponent::OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation,
	const FVector& OldVelocity)
{
	Super::OnMovementUpdated(DeltaSeconds, OldLocation, OldVelocity);

	if (MovementMode == MOVE_Walking)
	{
		MaxWalkSpeed = Safe_bWantsToSprint ? Sprint_MaxWalkSpeed : Walk_MaxWalkSpeed;
	}
}

UDashCharacterMovementComponent::UDashCharacterMovementComponent()
{
	NavAgentProps.bCanCrouch = true;
}

void UDashCharacterMovementComponent::SprintPressed()
{
	Safe_bWantsToSprint = true;
}

void UDashCharacterMovementComponent::SprintReleased()
{
	Safe_bWantsToSprint = false;
}


