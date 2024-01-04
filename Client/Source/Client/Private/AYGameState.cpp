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
	return *iter;
}
