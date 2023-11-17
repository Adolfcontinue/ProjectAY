// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ProjectAYGameInstance.generated.h"

//Delegate
DECLARE_DELEGATE(FDele_Single);

/**
 * To do List
 * delegated 등록해둘 맵이나 리스트 만들어야한다??
 * 
 * 
 * 
 * 
 */
UCLASS()
class CLIENT_API UProjectAYGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	FDele_Single Fuc_DeleSingle;




};
