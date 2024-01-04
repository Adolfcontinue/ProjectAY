// Fill out your copyright notice in the Description page of Project Settings.


#include "AYGameMode.h"
#include "ClientPlayerPawn.h"
#include "AYCharacter.h"
#include "ClientPlayerController.h"
#include "../AYGameInstance.h"
#include "AYGameState.h"

AAYGameMode::AAYGameMode()
{
	DefaultPawnClass = AAYCharacter::StaticClass();
	PlayerControllerClass = AClientPlayerController::StaticClass();
	GameStateClass = AAYGameState::StaticClass();
}

void AAYGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AYGameState = Cast<AAYGameState>(GameState);
}

void AAYGameMode::PostLogin(APlayerController* newPlayer)
{
	//LOG(Warning, TEXT("PostLogin Bagin"));
	Super::PostLogin(newPlayer);

	UAYGameInstance* inst = Cast<UAYGameInstance>(GetGameInstance());
	Protocol::C2P_RequestWorldData packet;
	inst->Send(packet, (uint16)EPacket_C2P_Protocol::C2P_RequestWorldData);
}

