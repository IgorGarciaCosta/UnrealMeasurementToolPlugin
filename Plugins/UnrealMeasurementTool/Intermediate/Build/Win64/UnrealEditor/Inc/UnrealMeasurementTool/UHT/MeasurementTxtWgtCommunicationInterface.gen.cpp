// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MeasurementTxtWgtCommunicationInterface.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeMeasurementTxtWgtCommunicationInterface() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UInterface();
UNREALMEASUREMENTTOOL_API UClass* Z_Construct_UClass_UMeasurementTxtWgtCommunicationInterface();
UNREALMEASUREMENTTOOL_API UClass* Z_Construct_UClass_UMeasurementTxtWgtCommunicationInterface_NoRegister();
UPackage* Z_Construct_UPackage__Script_UnrealMeasurementTool();
// ********** End Cross Module References **********************************************************

// ********** Begin Interface UMeasurementTxtWgtCommunicationInterface Function SendMeasurementText 
struct MeasurementTxtWgtCommunicationInterface_eventSendMeasurementText_Parms
{
	FText InText;
};
void IMeasurementTxtWgtCommunicationInterface::SendMeasurementText(FText const& InText)
{
	check(0 && "Do not directly call Event functions in Interfaces. Call Execute_SendMeasurementText instead.");
}
static FName NAME_UMeasurementTxtWgtCommunicationInterface_SendMeasurementText = FName(TEXT("SendMeasurementText"));
void IMeasurementTxtWgtCommunicationInterface::Execute_SendMeasurementText(UObject* O, FText const& InText)
{
	check(O != NULL);
	check(O->GetClass()->ImplementsInterface(UMeasurementTxtWgtCommunicationInterface::StaticClass()));
	MeasurementTxtWgtCommunicationInterface_eventSendMeasurementText_Parms Parms;
	UFunction* const Func = O->FindFunction(NAME_UMeasurementTxtWgtCommunicationInterface_SendMeasurementText);
	if (Func)
	{
		Parms.InText=std::move(InText);
		O->ProcessEvent(Func, &Parms);
	}
	else if (auto I = (IMeasurementTxtWgtCommunicationInterface*)(O->GetNativeInterfaceAddress(UMeasurementTxtWgtCommunicationInterface::StaticClass())))
	{
		I->SendMeasurementText_Implementation(InText);
	}
}
struct Z_Construct_UFunction_UMeasurementTxtWgtCommunicationInterface_SendMeasurementText_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Measurement" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Sends a formatted measurement text to the implementing widget. */" },
#endif
		{ "ModuleRelativePath", "Public/MeasurementTxtWgtCommunicationInterface.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Sends a formatted measurement text to the implementing widget." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InText_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function SendMeasurementText constinit property declarations *******************
	static const UECodeGen_Private::FTextPropertyParams NewProp_InText;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SendMeasurementText constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SendMeasurementText Property Definitions ******************************
const UECodeGen_Private::FTextPropertyParams Z_Construct_UFunction_UMeasurementTxtWgtCommunicationInterface_SendMeasurementText_Statics::NewProp_InText = { "InText", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MeasurementTxtWgtCommunicationInterface_eventSendMeasurementText_Parms, InText), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InText_MetaData), NewProp_InText_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMeasurementTxtWgtCommunicationInterface_SendMeasurementText_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMeasurementTxtWgtCommunicationInterface_SendMeasurementText_Statics::NewProp_InText,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMeasurementTxtWgtCommunicationInterface_SendMeasurementText_Statics::PropPointers) < 2048);
// ********** End Function SendMeasurementText Property Definitions ********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMeasurementTxtWgtCommunicationInterface_SendMeasurementText_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UMeasurementTxtWgtCommunicationInterface, nullptr, "SendMeasurementText", 	Z_Construct_UFunction_UMeasurementTxtWgtCommunicationInterface_SendMeasurementText_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UMeasurementTxtWgtCommunicationInterface_SendMeasurementText_Statics::PropPointers), 
sizeof(MeasurementTxtWgtCommunicationInterface_eventSendMeasurementText_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x0C420C00, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMeasurementTxtWgtCommunicationInterface_SendMeasurementText_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMeasurementTxtWgtCommunicationInterface_SendMeasurementText_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(MeasurementTxtWgtCommunicationInterface_eventSendMeasurementText_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UMeasurementTxtWgtCommunicationInterface_SendMeasurementText()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMeasurementTxtWgtCommunicationInterface_SendMeasurementText_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(IMeasurementTxtWgtCommunicationInterface::execSendMeasurementText)
{
	P_GET_PROPERTY_REF(FTextProperty,Z_Param_Out_InText);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SendMeasurementText_Implementation(Z_Param_Out_InText);
	P_NATIVE_END;
}
// ********** End Interface UMeasurementTxtWgtCommunicationInterface Function SendMeasurementText **

// ********** Begin Interface UMeasurementTxtWgtCommunicationInterface *****************************
FClassRegistrationInfo Z_Registration_Info_UClass_UMeasurementTxtWgtCommunicationInterface;
UClass* UMeasurementTxtWgtCommunicationInterface::GetPrivateStaticClass()
{
	using TClass = UMeasurementTxtWgtCommunicationInterface;
	if (!Z_Registration_Info_UClass_UMeasurementTxtWgtCommunicationInterface.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("MeasurementTxtWgtCommunicationInterface"),
			Z_Registration_Info_UClass_UMeasurementTxtWgtCommunicationInterface.InnerSingleton,
			StaticRegisterNativesUMeasurementTxtWgtCommunicationInterface,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UMeasurementTxtWgtCommunicationInterface.InnerSingleton;
}
UClass* Z_Construct_UClass_UMeasurementTxtWgtCommunicationInterface_NoRegister()
{
	return UMeasurementTxtWgtCommunicationInterface::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UMeasurementTxtWgtCommunicationInterface_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/MeasurementTxtWgtCommunicationInterface.h" },
	};
#endif // WITH_METADATA

// ********** Begin Interface UMeasurementTxtWgtCommunicationInterface constinit property declarations 
// ********** End Interface UMeasurementTxtWgtCommunicationInterface constinit property declarations 
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("SendMeasurementText"), .Pointer = &IMeasurementTxtWgtCommunicationInterface::execSendMeasurementText },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UMeasurementTxtWgtCommunicationInterface_SendMeasurementText, "SendMeasurementText" }, // 1366457051
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<IMeasurementTxtWgtCommunicationInterface>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UMeasurementTxtWgtCommunicationInterface_Statics
UObject* (*const Z_Construct_UClass_UMeasurementTxtWgtCommunicationInterface_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UInterface,
	(UObject* (*)())Z_Construct_UPackage__Script_UnrealMeasurementTool,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMeasurementTxtWgtCommunicationInterface_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UMeasurementTxtWgtCommunicationInterface_Statics::ClassParams = {
	&UMeasurementTxtWgtCommunicationInterface::StaticClass,
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
	0x000840A1u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMeasurementTxtWgtCommunicationInterface_Statics::Class_MetaDataParams), Z_Construct_UClass_UMeasurementTxtWgtCommunicationInterface_Statics::Class_MetaDataParams)
};
void UMeasurementTxtWgtCommunicationInterface::StaticRegisterNativesUMeasurementTxtWgtCommunicationInterface()
{
	UClass* Class = UMeasurementTxtWgtCommunicationInterface::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UMeasurementTxtWgtCommunicationInterface_Statics::Funcs));
}
UClass* Z_Construct_UClass_UMeasurementTxtWgtCommunicationInterface()
{
	if (!Z_Registration_Info_UClass_UMeasurementTxtWgtCommunicationInterface.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UMeasurementTxtWgtCommunicationInterface.OuterSingleton, Z_Construct_UClass_UMeasurementTxtWgtCommunicationInterface_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UMeasurementTxtWgtCommunicationInterface.OuterSingleton;
}
UMeasurementTxtWgtCommunicationInterface::UMeasurementTxtWgtCommunicationInterface(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UMeasurementTxtWgtCommunicationInterface);
// ********** End Interface UMeasurementTxtWgtCommunicationInterface *******************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_ISILV125_Documents_GitHub_UnrealMeasurementToolPlugin_Plugins_UnrealMeasurementTool_Source_UnrealMeasurementTool_Public_MeasurementTxtWgtCommunicationInterface_h__Script_UnrealMeasurementTool_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UMeasurementTxtWgtCommunicationInterface, UMeasurementTxtWgtCommunicationInterface::StaticClass, TEXT("UMeasurementTxtWgtCommunicationInterface"), &Z_Registration_Info_UClass_UMeasurementTxtWgtCommunicationInterface, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UMeasurementTxtWgtCommunicationInterface), 1644670533U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_ISILV125_Documents_GitHub_UnrealMeasurementToolPlugin_Plugins_UnrealMeasurementTool_Source_UnrealMeasurementTool_Public_MeasurementTxtWgtCommunicationInterface_h__Script_UnrealMeasurementTool_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_ISILV125_Documents_GitHub_UnrealMeasurementToolPlugin_Plugins_UnrealMeasurementTool_Source_UnrealMeasurementTool_Public_MeasurementTxtWgtCommunicationInterface_h__Script_UnrealMeasurementTool_2102648024{
	TEXT("/Script/UnrealMeasurementTool"),
	Z_CompiledInDeferFile_FID_Users_ISILV125_Documents_GitHub_UnrealMeasurementToolPlugin_Plugins_UnrealMeasurementTool_Source_UnrealMeasurementTool_Public_MeasurementTxtWgtCommunicationInterface_h__Script_UnrealMeasurementTool_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_ISILV125_Documents_GitHub_UnrealMeasurementToolPlugin_Plugins_UnrealMeasurementTool_Source_UnrealMeasurementTool_Public_MeasurementTxtWgtCommunicationInterface_h__Script_UnrealMeasurementTool_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
