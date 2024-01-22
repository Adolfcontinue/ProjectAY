// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Client.h"
#include "GameFramework/Actor.h"
#include "AYActorBase.generated.h"

UCLASS()
class CLIENT_API AAYActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAYActorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void LoadMesh(const FString& path);
	void SetScale(FVector& scale);
	UStaticMeshComponent* GetStaticMeshComponent();
	

protected:
	UPROPERTY(Category = Mesh, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

};
