// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ProjectAYGameInstance.generated.h"

//Delegate
DECLARE_DELEGATE(FDele_Single);

/**
 * To do List
 * delegated ����ص� ���̳� ����Ʈ �������Ѵ�??
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
