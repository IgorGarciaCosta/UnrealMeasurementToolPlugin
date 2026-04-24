// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MeasurementTextWidget.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeMeasurementTextWidget() {}

// ********** Begin Cross Module References ********************************************************
UMG_API UClass* Z_Construct_UClass_UTextBlock_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UNREALMEASUREMENTTOOL_API UClass* Z_Construct_UClass_UMeasurementTextWidget();
UNREALMEASUREMENTTOOL_API UClass* Z_Construct_UClass_UMeasurementTextWidget_NoRegister();
UNREALMEASUREMENTTOOL_API UClass* Z_Construct_UClass_UMeasurementTxtWgtCommunicationInterface_NoRegister();
UPackage* Z_Construct_UPackage__Script_UnrealMeasurementTool();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UMeasurementTextWidget Function SetText **********************************
struct Z_Construct_UFunction_UMeasurementTextWidget_SetText_Statics
{
	struct MeasurementTextWidget_eventSetText_Parms
	{
		FText InText;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Measurement" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Sets the measurement display text. */" },
#endif
		{ "ModuleRelativePath", "Public/MeasurementTextWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Sets the measurement display text." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InText_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetText constinit property declarations *******************************
	static const UECodeGen_Private::FTextPropertyParams NewProp_InText;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetText constinit property declarations *********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetText Property Definitions ******************************************
const UECodeGen_Private::FTextPropertyParams Z_Construct_UFunction_UMeasurementTextWidget_SetText_Statics::NewProp_InText = { "InText", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MeasurementTextWidget_eventSetText_Parms, InText), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InText_MetaData), NewProp_InText_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMeasurementTextWidget_SetText_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMeasurementTextWidget_SetText_Statics::NewProp_InText,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMeasurementTextWidget_SetText_Statics::PropPointers) < 2048);
// ********** End Function SetText Property Definitions ********************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMeasurementTextWidget_SetText_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UMeasurementTextWidget, nullptr, "SetText", 	Z_Construct_UFunction_UMeasurementTextWidget_SetText_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UMeasurementTextWidget_SetText_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UMeasurementTextWidget_SetText_Statics::MeasurementTextWidget_eventSetText_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMeasurementTextWidget_SetText_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMeasurementTextWidget_SetText_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UMeasurementTextWidget_SetText_Statics::MeasurementTextWidget_eventSetText_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UMeasurementTextWidget_SetText()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMeasurementTextWidget_SetText_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMeasurementTextWidget::execSetText)
{
	P_GET_PROPERTY_REF(FTextProperty,Z_Param_Out_InText);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetText(Z_Param_Out_InText);
	P_NATIVE_END;
}
// ********** End Class UMeasurementTextWidget Function SetText ************************************

// ********** Begin Class UMeasurementTextWidget ***************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UMeasurementTextWidget;
UClass* UMeasurementTextWidget::GetPrivateStaticClass()
{
	using TClass = UMeasurementTextWidget;
	if (!Z_Registration_Info_UClass_UMeasurementTextWidget.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("MeasurementTextWidget"),
			Z_Registration_Info_UClass_UMeasurementTextWidget.InnerSingleton,
			StaticRegisterNativesUMeasurementTextWidget,
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
	return Z_Registration_Info_UClass_UMeasurementTextWidget.InnerSingleton;
}
UClass* Z_Construct_UClass_UMeasurementTextWidget_NoRegister()
{
	return UMeasurementTextWidget::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UMeasurementTextWidget_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Widget that displays a measurement text value.\n * Implements IMeasurementTxtWgtCommunicationInterface so that any actor can send\n * measurement data without knowing the concrete widget type.\n *\n * Usage: Create a Widget Blueprint based on this class and add a TextBlock named \"MeasurementText\".\n */" },
#endif
		{ "IncludePath", "MeasurementTextWidget.h" },
		{ "ModuleRelativePath", "Public/MeasurementTextWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Widget that displays a measurement text value.\nImplements IMeasurementTxtWgtCommunicationInterface so that any actor can send\nmeasurement data without knowing the concrete widget type.\n\nUsage: Create a Widget Blueprint based on this class and add a TextBlock named \"MeasurementText\"." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MeasurementText_MetaData[] = {
		{ "BindWidget", "" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Bound text block \xe2\x80\x93 must exist in the Widget Blueprint with this exact name. */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/MeasurementTextWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Bound text block \xe2\x80\x93 must exist in the Widget Blueprint with this exact name." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UMeasurementTextWidget constinit property declarations *******************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MeasurementText;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UMeasurementTextWidget constinit property declarations *********************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("SetText"), .Pointer = &UMeasurementTextWidget::execSetText },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UMeasurementTextWidget_SetText, "SetText" }, // 356826968
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static const UECodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMeasurementTextWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UMeasurementTextWidget_Statics

// ********** Begin Class UMeasurementTextWidget Property Definitions ******************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UMeasurementTextWidget_Statics::NewProp_MeasurementText = { "MeasurementText", nullptr, (EPropertyFlags)0x0124080000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMeasurementTextWidget, MeasurementText), Z_Construct_UClass_UTextBlock_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeasurementText_MetaData), NewProp_MeasurementText_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UMeasurementTextWidget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMeasurementTextWidget_Statics::NewProp_MeasurementText,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMeasurementTextWidget_Statics::PropPointers) < 2048);
// ********** End Class UMeasurementTextWidget Property Definitions ********************************
UObject* (*const Z_Construct_UClass_UMeasurementTextWidget_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_UnrealMeasurementTool,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMeasurementTextWidget_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FImplementedInterfaceParams Z_Construct_UClass_UMeasurementTextWidget_Statics::InterfaceParams[] = {
	{ Z_Construct_UClass_UMeasurementTxtWgtCommunicationInterface_NoRegister, (int32)VTABLE_OFFSET(UMeasurementTextWidget, IMeasurementTxtWgtCommunicationInterface), false },  // 3852926708
};
const UECodeGen_Private::FClassParams Z_Construct_UClass_UMeasurementTextWidget_Statics::ClassParams = {
	&UMeasurementTextWidget::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UMeasurementTextWidget_Statics::PropPointers,
	InterfaceParams,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UMeasurementTextWidget_Statics::PropPointers),
	UE_ARRAY_COUNT(InterfaceParams),
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMeasurementTextWidget_Statics::Class_MetaDataParams), Z_Construct_UClass_UMeasurementTextWidget_Statics::Class_MetaDataParams)
};
void UMeasurementTextWidget::StaticRegisterNativesUMeasurementTextWidget()
{
	UClass* Class = UMeasurementTextWidget::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UMeasurementTextWidget_Statics::Funcs));
}
UClass* Z_Construct_UClass_UMeasurementTextWidget()
{
	if (!Z_Registration_Info_UClass_UMeasurementTextWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UMeasurementTextWidget.OuterSingleton, Z_Construct_UClass_UMeasurementTextWidget_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UMeasurementTextWidget.OuterSingleton;
}
UMeasurementTextWidget::UMeasurementTextWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UMeasurementTextWidget);
UMeasurementTextWidget::~UMeasurementTextWidget() {}
// ********** End Class UMeasurementTextWidget *****************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_ISILV125_Documents_GitHub_UnrealMeasurementToolPlugin_Plugins_UnrealMeasurementTool_Source_UnrealMeasurementTool_Public_MeasurementTextWidget_h__Script_UnrealMeasurementTool_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UMeasurementTextWidget, UMeasurementTextWidget::StaticClass, TEXT("UMeasurementTextWidget"), &Z_Registration_Info_UClass_UMeasurementTextWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UMeasurementTextWidget), 4236823480U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_ISILV125_Documents_GitHub_UnrealMeasurementToolPlugin_Plugins_UnrealMeasurementTool_Source_UnrealMeasurementTool_Public_MeasurementTextWidget_h__Script_UnrealMeasurementTool_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_ISILV125_Documents_GitHub_UnrealMeasurementToolPlugin_Plugins_UnrealMeasurementTool_Source_UnrealMeasurementTool_Public_MeasurementTextWidget_h__Script_UnrealMeasurementTool_2629657653{
	TEXT("/Script/UnrealMeasurementTool"),
	Z_CompiledInDeferFile_FID_Users_ISILV125_Documents_GitHub_UnrealMeasurementToolPlugin_Plugins_UnrealMeasurementTool_Source_UnrealMeasurementTool_Public_MeasurementTextWidget_h__Script_UnrealMeasurementTool_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_ISILV125_Documents_GitHub_UnrealMeasurementToolPlugin_Plugins_UnrealMeasurementTool_Source_UnrealMeasurementTool_Public_MeasurementTextWidget_h__Script_UnrealMeasurementTool_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
