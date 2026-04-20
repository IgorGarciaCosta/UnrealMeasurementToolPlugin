// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MeasurementActor.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeMeasurementActor() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_USplineComponent_NoRegister();
UMG_API UClass* Z_Construct_UClass_UWidgetComponent_NoRegister();
UNREALMEASUREMENTTOOL_API UClass* Z_Construct_UClass_AMeasurementActor();
UNREALMEASUREMENTTOOL_API UClass* Z_Construct_UClass_AMeasurementActor_NoRegister();
UPackage* Z_Construct_UPackage__Script_UnrealMeasurementTool();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AMeasurementActor ********************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_AMeasurementActor;
UClass* AMeasurementActor::GetPrivateStaticClass()
{
	using TClass = AMeasurementActor;
	if (!Z_Registration_Info_UClass_AMeasurementActor.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("MeasurementActor"),
			Z_Registration_Info_UClass_AMeasurementActor.InnerSingleton,
			StaticRegisterNativesAMeasurementActor,
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
	return Z_Registration_Info_UClass_AMeasurementActor.InnerSingleton;
}
UClass* Z_Construct_UClass_AMeasurementActor_NoRegister()
{
	return AMeasurementActor::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AMeasurementActor_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Actor that uses a SplineComponent to measure distance and displays\n * the result through a WidgetComponent.\n *\n * Communication with the widget is fully decoupled via\n * IMeasurementTxtWgtCommunicationInterface \xe2\x80\x93 the actor never references\n * the concrete widget class.\n *\n * The measurement updates in the editor when spline points are moved\n * (OnConstruction). No Tick overhead at runtime.\n */" },
#endif
		{ "IncludePath", "MeasurementActor.h" },
		{ "ModuleRelativePath", "Public/MeasurementActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Actor that uses a SplineComponent to measure distance and displays\nthe result through a WidgetComponent.\n\nCommunication with the widget is fully decoupled via\nIMeasurementTxtWgtCommunicationInterface \xe2\x80\x93 the actor never references\nthe concrete widget class.\n\nThe measurement updates in the editor when spline points are moved\n(OnConstruction). No Tick overhead at runtime." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SplineComponent_MetaData[] = {
		{ "Category", "Measurement" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/MeasurementActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WidgetComponent_MetaData[] = {
		{ "Category", "Measurement" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/MeasurementActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class AMeasurementActor constinit property declarations ************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SplineComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WidgetComponent;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class AMeasurementActor constinit property declarations **************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMeasurementActor>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_AMeasurementActor_Statics

// ********** Begin Class AMeasurementActor Property Definitions ***********************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMeasurementActor_Statics::NewProp_SplineComponent = { "SplineComponent", nullptr, (EPropertyFlags)0x01240800000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMeasurementActor, SplineComponent), Z_Construct_UClass_USplineComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SplineComponent_MetaData), NewProp_SplineComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMeasurementActor_Statics::NewProp_WidgetComponent = { "WidgetComponent", nullptr, (EPropertyFlags)0x01240800000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMeasurementActor, WidgetComponent), Z_Construct_UClass_UWidgetComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WidgetComponent_MetaData), NewProp_WidgetComponent_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AMeasurementActor_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMeasurementActor_Statics::NewProp_SplineComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMeasurementActor_Statics::NewProp_WidgetComponent,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMeasurementActor_Statics::PropPointers) < 2048);
// ********** End Class AMeasurementActor Property Definitions *************************************
UObject* (*const Z_Construct_UClass_AMeasurementActor_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_UnrealMeasurementTool,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMeasurementActor_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AMeasurementActor_Statics::ClassParams = {
	&AMeasurementActor::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_AMeasurementActor_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_AMeasurementActor_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AMeasurementActor_Statics::Class_MetaDataParams), Z_Construct_UClass_AMeasurementActor_Statics::Class_MetaDataParams)
};
void AMeasurementActor::StaticRegisterNativesAMeasurementActor()
{
}
UClass* Z_Construct_UClass_AMeasurementActor()
{
	if (!Z_Registration_Info_UClass_AMeasurementActor.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMeasurementActor.OuterSingleton, Z_Construct_UClass_AMeasurementActor_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AMeasurementActor.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, AMeasurementActor);
AMeasurementActor::~AMeasurementActor() {}
// ********** End Class AMeasurementActor **********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_ISILV125_Documents_GitHub_UnrealMeasurementToolPlugin_Plugins_UnrealMeasurementTool_Source_UnrealMeasurementTool_Public_MeasurementActor_h__Script_UnrealMeasurementTool_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AMeasurementActor, AMeasurementActor::StaticClass, TEXT("AMeasurementActor"), &Z_Registration_Info_UClass_AMeasurementActor, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMeasurementActor), 3907677105U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_ISILV125_Documents_GitHub_UnrealMeasurementToolPlugin_Plugins_UnrealMeasurementTool_Source_UnrealMeasurementTool_Public_MeasurementActor_h__Script_UnrealMeasurementTool_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_ISILV125_Documents_GitHub_UnrealMeasurementToolPlugin_Plugins_UnrealMeasurementTool_Source_UnrealMeasurementTool_Public_MeasurementActor_h__Script_UnrealMeasurementTool_3173801599{
	TEXT("/Script/UnrealMeasurementTool"),
	Z_CompiledInDeferFile_FID_Users_ISILV125_Documents_GitHub_UnrealMeasurementToolPlugin_Plugins_UnrealMeasurementTool_Source_UnrealMeasurementTool_Public_MeasurementActor_h__Script_UnrealMeasurementTool_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_ISILV125_Documents_GitHub_UnrealMeasurementToolPlugin_Plugins_UnrealMeasurementTool_Source_UnrealMeasurementTool_Public_MeasurementActor_h__Script_UnrealMeasurementTool_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
