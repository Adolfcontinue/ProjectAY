// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterWidget.h"
#include "PlayerStatComponent.h"
#include "Components/ProgressBar.h"

void UCharacterWidget::BindCharacterStat(UPlayerStatComponent* statCom)
{
	CurrentStat = statCom;

	statCom->OnHPchanged.AddUObject(this, &UCharacterWidget::UpdateHPWidget);

	/*statCom->OnHPchanged.AddLambda([this]()-> void {
		if (CurrentStat.IsValid())
		{
			CurrentStat->GetHPRatio();
		}
		});*/
}

void UCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();
	progressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	UpdateHPWidget();
}

void UCharacterWidget::UpdateHPWidget()
{
	if (!CurrentStat.IsValid())
		return;

	if (progressBar == nullptr)
		return;

	progressBar->SetPercent(CurrentStat->GetHPRatio());
}
