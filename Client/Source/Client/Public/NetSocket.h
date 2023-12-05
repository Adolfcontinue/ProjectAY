// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NetWork/NetService.h"
#include "NetWork/NetCore.h"
#include "NetSocket.generated.h"

UCLASS()
class CLIENT_API ANetSocket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANetSocket();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	std::shared_ptr<ClientService> _service;

public:
	void CreateService();

private:
	bool IsConnected = false;

};
