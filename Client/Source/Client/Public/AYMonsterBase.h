// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AYMonsterBase.generated.h"

UCLASS()
class CLIENT_API AAYMonsterBase : public APawn
{
	GENERATED_BODY()

protected:

public:
    // Sets default values for this actor's properties
    AAYMonsterBase();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster")
    float MaxHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster")
    float Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster")
    float AttackPower;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster")
    bool bIsStunned;

    UFUNCTION(BlueprintCallable, Category = "Monster")
    void TakeDamage(float DamageAmount);

    UFUNCTION(BlueprintCallable, Category = "Monster")
    void ApplyStun(float StunDuration);

};
