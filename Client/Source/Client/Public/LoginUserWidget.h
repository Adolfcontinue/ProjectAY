// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginUserWidget.generated.h"

UCLASS()
class CLIENT_API ULoginUserWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Login")
    void OnLoginButtonClicked();

protected:
    UPROPERTY(meta = (BindWidget))
    class UButton* LoginButton;

    UPROPERTY(meta = (BindWidget))
    class UEditableTextBox* UsernameTextBox;

    UPROPERTY(meta = (BindWidget))
    class UEditableTextBox* PasswordTextBox;

    UFUNCTION()
    void HandleLoginButtonClicked();

    virtual void NativeConstruct() override;
};
