// Copyright Epic Games, Inc. All Rights Reserved.

#include "ClientGameMode.h"
#include "ClientCharacter.h"
#include "GamePlayer.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AClientGameMode::AClientGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AClientGameMode::CreatePlayer(uint64 playerKey)
{
	// 스폰할 블루프린트 클래스의 경로를 문자열로 지정합니다.
	FString BlueprintPath = TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter");

	// 블루프린트 클래스 로드
	UClass* bp_class = LoadObject<UClass>(nullptr, *BlueprintPath);

	if (!bp_class)
		return;

	AGamePlayer* player = GetWorld()->SpawnActor<AGamePlayer>(bp_class, FVector::ZeroVector, FRotator::ZeroRotator);

	if (player)
		return;

	player->SetPlayerKey(playerKey);

	AddPlayer(player);
}

void AClientGameMode::AddPlayer(AGamePlayer* player)
{
	_players.Add(player->GetPlayerKey(), player);
}

void AClientGameMode::ErasePlaye(uint64 playerKey)
{
	_players.Remove(playerKey);
}

AGamePlayer* AClientGameMode::FindPlayer(uint64 playerKey)
{
	AGamePlayer* ret = _players.FindAndRemoveChecked(playerKey);
	return ret;
}
