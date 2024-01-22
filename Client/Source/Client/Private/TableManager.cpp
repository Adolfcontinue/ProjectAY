// Fill out your copyright notice in the Description page of Project Settings.


#include "TableManager.h"

// Sets default values
UTableManager::UTableManager()
{

}


void UTableManager::TableLoad()
{
	FString tablePath = TEXT("/Game/Table/TableBase.TableBase");
	UDataTable* aa = LoadObject<UDataTable>(nullptr, *tablePath);
	Test = aa;
}

FTableTest* UTableManager::GetTableTest(int a)
{
	return Test->FindRow<FTableTest>(*FString::FromInt(a), TEXT(""));
}

