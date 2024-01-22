// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextBoxWidget.generated.h"

/**
 * 
 */
UCLASS()
class CLIENT_API UTextBoxWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetText(const FString& string);


protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTextBlock* TextBox;

private:
	UPROPERTY(Editanywhere, BlueprintReadOnly, Category = TEXT, Meta = (AllowPrivateAccess = true))
	FText TextString;
};
