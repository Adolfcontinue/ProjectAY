// Fill out your copyright notice in the Description page of Project Settings.


#include "TextBoxWidget.h"
#include "Components/TextBlock.h"


void UTextBoxWidget::SetText(const FString& string)
{
	TextString = FText::FromString(string);

	// �ؽ�Ʈ ����� �ؽ�Ʈ�� ����
	TextBox->SetText(TextString);
}

void UTextBoxWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	TextBox = Cast<UTextBlock>(GetWidgetFromName(TEXT("TEXTBOX")));
}

void UTextBoxWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
