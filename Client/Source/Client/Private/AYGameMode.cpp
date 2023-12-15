// Fill out your copyright notice in the Description page of Project Settings.


#include "AYGameMode.h"
#include "ClientPlayerPawn.h"
#include "AYCharacter.h"
#include "ClientPlayerController.h"

AAYGameMode::AAYGameMode()
{
	//default pawn class setting 
	DefaultPawnClass = AAYCharacter::StaticClass();

	//default controller class setting
	PlayerControllerClass = AClientPlayerController::StaticClass();
}

void AAYGameMode::PostLogin(APlayerController* newPlayer)
{
	LOG(Warning, TEXT("PostLogin Bagin"));
	Super::PostLogin(newPlayer);
	LOG(Warning, TEXT("PostLogin End"));
}

