// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(CLIENT, Log, All);

//#define LOG_CALL_INFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
//#define LOG_S(Verbosity) UE_LOG(CLIENT, Verbosity, TEXT("%s"), *LOG_CALL_INFO)
//#define LOG(Verbosity, Format, ...) UE_LOG(CLIENT, Verbosity, TEXT("%s %s"), *LOG_CALL_INFO, *FString::Printf(Format, ##__VA_ARGS__))
//#define CHECK(Expr,...) {if(!(Expr)) {LOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__;}}