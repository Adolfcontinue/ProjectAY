// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginUserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/CanvasPanelSlot.h"
//Gameinstance
#include "Kismet/GameplayStatics.h"
#include "Client/AYGameInstance.h"
#include <string>

void ULoginUserWidget::NativeConstruct()
{
    Super::NativeConstruct();

    //if (UCanvasPanelSlot* Slot = Cast<UCanvasPanelSlot>(GetRootWidget()->Slot))
    //{
    //    //Slot->SetAlignment(FVector2D(0.5f, 0.5f));
    //    //Slot->SetAnchors(FAnchors(0.5f, 0.5f, 0.5f, 0.5f));
    //}

    if (LoginButton)
    {
        LoginButton->OnClicked.AddDynamic(this, &ULoginUserWidget::HandleLoginButtonClicked);
    }

    UAYGameInstance* GI = Cast<UAYGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
    GI->GetRecvProsessor()->Delegate_P2C_Result.AddUObject(this, &ULoginUserWidget::ChangeLevel);
}

void ULoginUserWidget::ChangeLevel()
{
    UGameplayStatics::OpenLevel(this, "Field1");
}

//void ULoginUserWidget::ChangeLevel()
//{
//    UGameplayStatics::OpenLevel(this, "ThirdPersonmMap");
//}

void ULoginUserWidget::HandleLoginButtonClicked()
{
    FString Username = UsernameTextBox->GetText().ToString();
    FString Password = PasswordTextBox->GetText().ToString();

    // 여기에 로그인 처리 로직을 작성하면 됩니다.
    //1. UserName을 입력하시오
    if (Username.Len() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Username: %s is Empty"), *Username);
        return;
    }
    //2. Password를 입력하시오
    if (Password.Len() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Password: %s is Empty"), *Password);
        return;
    }

    //우선조건 아이디가 비었으면 아이디 비었다는 팝업 띄어줘야한다.

    //아이디 확인여부는 나중에 리시브로 받아서 확인한다.

    // 예시로 콘솔에 사용자 이름과 비밀번호를 출력합니다.
    UE_LOG(LogTemp, Warning, TEXT("Username: %s, Password: %s"), *Username, *Password);
    UAYGameInstance* GI = Cast<UAYGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
    if (IsValid(GI))
    {
        Protocol::C2P_RequestLogin packet;
        packet.set_id(std::string(TCHAR_TO_UTF8(*Username)));
        packet.set_pw(std::string(TCHAR_TO_UTF8(*Password)));
        GI->Send(packet,(uint16)EPacket_C2P_Protocol::C2P_RequestLogin);
    }
}

void ULoginUserWidget::OnLoginButtonClicked()
{
    // 이 함수는 위젯의 Blueprint에서 호출될 수 있는 함수입니다.
    HandleLoginButtonClicked();
}