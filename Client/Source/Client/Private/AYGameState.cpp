// Fill out your copyright notice in the Description page of Project Settings.


#include "AYGameState.h"

void AAYGameState::AddPlayer(int64 key, AOtherCharacter* player)
{
	Players.Add(key, player);
}

void AAYGameState::RemovePlayer(int64 key)
{
	Players.Remove(key);
}

AOtherCharacter* AAYGameState::FindPlayer(int64 key)
{
	auto iter = Players.Find(key);
	if (iter == nullptr)
		return nullptr;

	return *iter;
}

void AAYGameState::RepPlayerMove(int64 userKey, FVector pos, FQuat quat)
{
	AOtherCharacter* player = FindPlayer(userKey);
	if (player == nullptr)
		return;

	player->RepPlayerMove(pos, quat);
}
