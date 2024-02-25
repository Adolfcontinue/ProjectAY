// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Client.h"
#include "GameFramework/Character.h"
#include "Define.h"
#include "Protobuf/Enum.pb.h"
#include "Protobuf/Protocol.pb.h"
#include "Protobuf/Struct.pb.h"
#include "AYMonsterBase.generated.h"

UCLASS()
class CLIENT_API AAYMonsterBase : public ACharacter
{
	GENERATED_BODY()


public:
    // Sets default values for this actor's properties
    AAYMonsterBase();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaTime) override;
    virtual void PostInitializeComponents() override;
    void SetActorKey(uint64 key);
    uint64 GetActorKey();
    void SetMonseterAsset();


public:
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

public:
    void RepMonsterState(FVector pos, FVector targetPos, Protocol::ActorState state);

private:
    void Move(float DeltaTime);
    void Rotation(float DeltaTime);
    void AttackCheck();
    EAnimState ConvertAnimState(Protocol::ActorState state);



protected:
    uint64 ActorKey;
    MonsterType MonsterKey;

    UPROPERTY()
    class UMonsterAnimInstance* Anim;

    FVector MyLocation;
    FVector CurLocation;
    FVector MoveDir;
    FVector TargetLocation;
    float LerpAlpha;
    FQuat CurrentRotation;
    FQuat TargetRotation;
    float SlerpAlpha;

    UPROPERTY()
    class UPlayerStatComponent* Stat;

    UPROPERTY()
    class UWidgetComponent* HPBar;
};
