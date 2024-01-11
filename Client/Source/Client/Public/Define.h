// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EAnimState : uint8 
{ 
	Idle UMETA(DisplayName = "Idle"), 
	Attack1 UMETA(DisplayName = "Attack1"),
	Attack2 UMETA(DisplayName = "Attack2"),
	Move UMETA(DisplayName = "Move"),
	Dead UMETA(DisplayName = "Dead")
};

enum AnimState
{
	Idle = 0,
	Attack1 = 2,
	Attack2 = 3,
	Run = 4,
	Dead = 5
};


class CLIENT_API Define
{
public:
	Define();
	~Define();
};
