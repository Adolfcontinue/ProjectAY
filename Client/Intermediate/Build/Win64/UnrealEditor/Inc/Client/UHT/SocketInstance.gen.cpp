// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Client/SocketInstance.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSocketInstance() {}
// Cross Module References
	CLIENT_API UClass* Z_Construct_UClass_USocketInstance();
	CLIENT_API UClass* Z_Construct_UClass_USocketInstance_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UGameInstance();
	UPackage* Z_Construct_UPackage__Script_Client();
// End Cross Module References
	DEFINE_FUNCTION(USocketInstance::execTest)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Test();
		P_NATIVE_END;
	}
	void USocketInstance::StaticRegisterNativesUSocketInstance()
	{
		UClass* Class = USocketInstance::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "Test", &USocketInstance::execTest },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_USocketInstance_Test_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USocketInstance_Test_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "SocketInstance.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USocketInstance_Test_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USocketInstance, nullptr, "Test", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USocketInstance_Test_Statics::Function_MetaDataParams), Z_Construct_UFunction_USocketInstance_Test_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_USocketInstance_Test()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USocketInstance_Test_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(USocketInstance);
	UClass* Z_Construct_UClass_USocketInstance_NoRegister()
	{
		return USocketInstance::StaticClass();
	}
	struct Z_Construct_UClass_USocketInstance_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USocketInstance_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UGameInstance,
		(UObject* (*)())Z_Construct_UPackage__Script_Client,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USocketInstance_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_USocketInstance_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_USocketInstance_Test, "Test" }, // 4240380428
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USocketInstance_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USocketInstance_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "SocketInstance.h" },
		{ "ModuleRelativePath", "SocketInstance.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_USocketInstance_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USocketInstance>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_USocketInstance_Statics::ClassParams = {
		&USocketInstance::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x009000A8u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USocketInstance_Statics::Class_MetaDataParams), Z_Construct_UClass_USocketInstance_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_USocketInstance()
	{
		if (!Z_Registration_Info_UClass_USocketInstance.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_USocketInstance.OuterSingleton, Z_Construct_UClass_USocketInstance_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_USocketInstance.OuterSingleton;
	}
	template<> CLIENT_API UClass* StaticClass<USocketInstance>()
	{
		return USocketInstance::StaticClass();
	}
	USocketInstance::USocketInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(USocketInstance);
	USocketInstance::~USocketInstance() {}
	struct Z_CompiledInDeferFile_FID_Users_godye_Desktop_Project_ProjectAY_Client_Source_Client_SocketInstance_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_godye_Desktop_Project_ProjectAY_Client_Source_Client_SocketInstance_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_USocketInstance, USocketInstance::StaticClass, TEXT("USocketInstance"), &Z_Registration_Info_UClass_USocketInstance, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USocketInstance), 1433592999U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_godye_Desktop_Project_ProjectAY_Client_Source_Client_SocketInstance_h_702946910(TEXT("/Script/Client"),
		Z_CompiledInDeferFile_FID_Users_godye_Desktop_Project_ProjectAY_Client_Source_Client_SocketInstance_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_godye_Desktop_Project_ProjectAY_Client_Source_Client_SocketInstance_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
