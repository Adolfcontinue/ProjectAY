// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#define LOG(Message, ...)\
	{\
		UE_LOG(LogTemp, Log, TEXT(Message), ##__VA_ARGS__); \
	}

#define LOG_WARNING(Message, ...)\
	{\
		UE_LOG(LogTemp, Warning, TEXT(Message), ##__VA_ARGS__); \
	}

#define LOG_SCREEN(Color, Message, ...) \
    { \
        if (GEngine) \
        { \
            FColor LogColor = Color; \
            FString LogMessage = FString::Printf(TEXT(Message), ##__VA_ARGS__); \
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, LogColor, LogMessage); \
        } \
    }

/**
 * 
 */
class CLIENT_API PreLoder
{
public:
	PreLoder();
	~PreLoder();
};
