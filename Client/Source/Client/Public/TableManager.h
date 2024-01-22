// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Client.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "TableManager.generated.h"



USTRUCT(BlueprintType)
struct FTableTest : public FTableRowBase
{
	GENERATED_BODY()

public:
	FTableTest() {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Level;

};




UCLASS()
class CLIENT_API UTableManager : public UObject
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	UTableManager();

public:
	void TableLoad();

public:
	FTableTest* GetTableTest(int a);

public:
	UPROPERTY()
	UDataTable* Test;

};
