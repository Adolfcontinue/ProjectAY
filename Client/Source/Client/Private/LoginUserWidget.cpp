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

    // ���⿡ �α��� ó�� ������ �ۼ��ϸ� �˴ϴ�.
    //1. UserName�� �Է��Ͻÿ�
    if (Username.Len() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Username: %s is Empty"), *Username);
        return;
    }
    //2. Password�� �Է��Ͻÿ�
    if (Password.Len() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Password: %s is Empty"), *Password);
        return;
    }

    //�켱���� ���̵� ������� ���̵� ����ٴ� �˾� �������Ѵ�.

    //���̵� Ȯ�ο��δ� ���߿� ���ú�� �޾Ƽ� Ȯ���Ѵ�.

    // ���÷� �ֿܼ� ����� �̸��� ��й�ȣ�� ����մϴ�.
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
    // �� �Լ��� ������ Blueprint���� ȣ��� �� �ִ� �Լ��Դϴ�.
    HandleLoginButtonClicked();
}