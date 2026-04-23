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
UNREALMEASUREMENTTOOL_API UClass* Z_Construct_UClass_UMeasurementLabelComponent_NoRegister();
UNREALMEASUREMENTTOOL_API UClass* Z_Construct_UClass_UMeasurementSnapComponent_NoRegister();
UNREALMEASUREMENTTOOL_API UEnum* Z_Construct_UEnum_UnrealMeasurementTool_EMeasurementMode();
UNREALMEASUREMENTTOOL_API UEnum* Z_Construct_UEnum_UnrealMeasurementTool_EMeasurementUnit();
UPackage* Z_Construct_UPackage__Script_UnrealMeasurementTool();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AMeasurementActor Function ApplyManualSize *******************************
struct Z_Construct_UFunction_AMeasurementActor_ApplyManualSize_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "Measurement Control" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Rescales the spline so its total length matches ManualSize in the current unit. */" },
#endif
		{ "DisplayName", "Submit" },
		{ "ModuleRelativePath", "Public/MeasurementActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Rescales the spline so its total length matches ManualSize in the current unit." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ApplyManualSize constinit property declarations ***********************
// ********** End Function ApplyManualSize constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMeasurementActor_ApplyManualSize_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMeasurementActor, nullptr, "ApplyManualSize", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMeasurementActor_ApplyManualSize_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMeasurementActor_ApplyManualSize_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AMeasurementActor_ApplyManualSize()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMeasurementActor_ApplyManualSize_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMeasurementActor::execApplyManualSize)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ApplyManualSize();
	P_NATIVE_END;
}
// ********** End Class AMeasurementActor Function ApplyManualSize *********************************

// ********** Begin Class AMeasurementActor Function ResetSpline ***********************************
struct Z_Construct_UFunction_AMeasurementActor_ResetSpline_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "Measurement Control" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Resets the spline to its default state (2 points), clears rotation and scale. */" },
#endif
		{ "DisplayName", "Reset" },
		{ "ModuleRelativePath", "Public/MeasurementActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Resets the spline to its default state (2 points), clears rotation and scale." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ResetSpline constinit property declarations ***************************
// ********** End Function ResetSpline constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMeasurementActor_ResetSpline_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMeasurementActor, nullptr, "ResetSpline", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMeasurementActor_ResetSpline_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMeasurementActor_ResetSpline_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AMeasurementActor_ResetSpline()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMeasurementActor_ResetSpline_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMeasurementActor::execResetSpline)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ResetSpline();
	P_NATIVE_END;
}
// ********** End Class AMeasurementActor Function ResetSpline *************************************

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
		{ "Comment", "/**\n * Actor that uses a SplineComponent to measure distance and displays\n * the result through a WidgetComponent.\n *\n * Communication with the widget is fully decoupled via\n * IMeasurementTxtWgtCommunicationInterface \xe2\x80\x93 the actor never references\n * the concrete widget class.\n *\n * Snap logic is delegated to UMeasurementSnapComponent.\n * Label management is delegated to UMeasurementLabelComponent.\n * Calculations / formatting live in UMeasurementCalculator.\n *\n * The measurement updates in the editor when spline points are moved\n * (OnConstruction). Billboard (face-camera) rotation of labels and widget\n * runs on a low-frequency timer (10 Hz) instead of per-frame Tick.\n */" },
#endif
		{ "IncludePath", "MeasurementActor.h" },
		{ "ModuleRelativePath", "Public/MeasurementActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Actor that uses a SplineComponent to measure distance and displays\nthe result through a WidgetComponent.\n\nCommunication with the widget is fully decoupled via\nIMeasurementTxtWgtCommunicationInterface \xe2\x80\x93 the actor never references\nthe concrete widget class.\n\nSnap logic is delegated to UMeasurementSnapComponent.\nLabel management is delegated to UMeasurementLabelComponent.\nCalculations / formatting live in UMeasurementCalculator.\n\nThe measurement updates in the editor when spline points are moved\n(OnConstruction). Billboard (face-camera) rotation of labels and widget\nruns on a low-frequency timer (10 Hz) instead of per-frame Tick." },
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
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SnapComponent_MetaData[] = {
		{ "Category", "Measurement" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/MeasurementActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LabelComponent_MetaData[] = {
		{ "Category", "Measurement" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/MeasurementActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MeasurementMode_MetaData[] = {
		{ "Category", "Measurement Control" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Measurement mode: Distance (spline length) or Area (enclosed polygon). */" },
#endif
		{ "DisplayName", "Mode" },
		{ "ModuleRelativePath", "Public/MeasurementActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Measurement mode: Distance (spline length) or Area (enclosed polygon)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DisplayUnit_MetaData[] = {
		{ "Category", "Measurement Control" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Unit used for the measurement display. */" },
#endif
		{ "DisplayName", "Unit" },
		{ "ModuleRelativePath", "Public/MeasurementActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Unit used for the measurement display." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ManualSize_MetaData[] = {
		{ "Category", "Measurement Control" },
		{ "ClampMin", "0.01" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Size (in the currently selected unit) to apply when Submit is pressed. */" },
#endif
		{ "DisplayName", "Size" },
		{ "ModuleRelativePath", "Public/MeasurementActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Size (in the currently selected unit) to apply when Submit is pressed." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bLinearSpline_MetaData[] = {
		{ "Category", "Measurement Control" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** When enabled, spline segments are straight lines instead of smooth curves. */" },
#endif
		{ "DisplayName", "Linear" },
		{ "ModuleRelativePath", "Public/MeasurementActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "When enabled, spline segments are straight lines instead of smooth curves." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bShowClosingLine_MetaData[] = {
		{ "Category", "Measurement Control" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Show a debug closing line from the last spline point to the first (Area mode). */" },
#endif
		{ "DisplayName", "Show Closing Line" },
		{ "EditCondition", "MeasurementMode == EMeasurementMode::Area" },
		{ "ModuleRelativePath", "Public/MeasurementActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Show a debug closing line from the last spline point to the first (Area mode)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class AMeasurementActor constinit property declarations ************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SplineComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WidgetComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SnapComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LabelComponent;
	static const UECodeGen_Private::FBytePropertyParams NewProp_MeasurementMode_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_MeasurementMode;
	static const UECodeGen_Private::FBytePropertyParams NewProp_DisplayUnit_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_DisplayUnit;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ManualSize;
	static void NewProp_bLinearSpline_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bLinearSpline;
	static void NewProp_bShowClosingLine_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShowClosingLine;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class AMeasurementActor constinit property declarations **************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("ApplyManualSize"), .Pointer = &AMeasurementActor::execApplyManualSize },
		{ .NameUTF8 = UTF8TEXT("ResetSpline"), .Pointer = &AMeasurementActor::execResetSpline },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AMeasurementActor_ApplyManualSize, "ApplyManualSize" }, // 3132284702
		{ &Z_Construct_UFunction_AMeasurementActor_ResetSpline, "ResetSpline" }, // 3877373454
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMeasurementActor>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_AMeasurementActor_Statics

// ********** Begin Class AMeasurementActor Property Definitions ***********************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMeasurementActor_Statics::NewProp_SplineComponent = { "SplineComponent", nullptr, (EPropertyFlags)0x01240800000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMeasurementActor, SplineComponent), Z_Construct_UClass_USplineComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SplineComponent_MetaData), NewProp_SplineComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMeasurementActor_Statics::NewProp_WidgetComponent = { "WidgetComponent", nullptr, (EPropertyFlags)0x01240800000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMeasurementActor, WidgetComponent), Z_Construct_UClass_UWidgetComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WidgetComponent_MetaData), NewProp_WidgetComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMeasurementActor_Statics::NewProp_SnapComponent = { "SnapComponent", nullptr, (EPropertyFlags)0x01240800000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMeasurementActor, SnapComponent), Z_Construct_UClass_UMeasurementSnapComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SnapComponent_MetaData), NewProp_SnapComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMeasurementActor_Statics::NewProp_LabelComponent = { "LabelComponent", nullptr, (EPropertyFlags)0x01240800000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMeasurementActor, LabelComponent), Z_Construct_UClass_UMeasurementLabelComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LabelComponent_MetaData), NewProp_LabelComponent_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_AMeasurementActor_Statics::NewProp_MeasurementMode_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_AMeasurementActor_Statics::NewProp_MeasurementMode = { "MeasurementMode", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMeasurementActor, MeasurementMode), Z_Construct_UEnum_UnrealMeasurementTool_EMeasurementMode, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeasurementMode_MetaData), NewProp_MeasurementMode_MetaData) }; // 2049286744
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_AMeasurementActor_Statics::NewProp_DisplayUnit_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_AMeasurementActor_Statics::NewProp_DisplayUnit = { "DisplayUnit", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMeasurementActor, DisplayUnit), Z_Construct_UEnum_UnrealMeasurementTool_EMeasurementUnit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DisplayUnit_MetaData), NewProp_DisplayUnit_MetaData) }; // 4084313674
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMeasurementActor_Statics::NewProp_ManualSize = { "ManualSize", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMeasurementActor, ManualSize), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ManualSize_MetaData), NewProp_ManualSize_MetaData) };
void Z_Construct_UClass_AMeasurementActor_Statics::NewProp_bLinearSpline_SetBit(void* Obj)
{
	((AMeasurementActor*)Obj)->bLinearSpline = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AMeasurementActor_Statics::NewProp_bLinearSpline = { "bLinearSpline", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AMeasurementActor), &Z_Construct_UClass_AMeasurementActor_Statics::NewProp_bLinearSpline_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bLinearSpline_MetaData), NewProp_bLinearSpline_MetaData) };
void Z_Construct_UClass_AMeasurementActor_Statics::NewProp_bShowClosingLine_SetBit(void* Obj)
{
	((AMeasurementActor*)Obj)->bShowClosingLine = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AMeasurementActor_Statics::NewProp_bShowClosingLine = { "bShowClosingLine", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AMeasurementActor), &Z_Construct_UClass_AMeasurementActor_Statics::NewProp_bShowClosingLine_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bShowClosingLine_MetaData), NewProp_bShowClosingLine_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AMeasurementActor_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMeasurementActor_Statics::NewProp_SplineComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMeasurementActor_Statics::NewProp_WidgetComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMeasurementActor_Statics::NewProp_SnapComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMeasurementActor_Statics::NewProp_LabelComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMeasurementActor_Statics::NewProp_MeasurementMode_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMeasurementActor_Statics::NewProp_MeasurementMode,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMeasurementActor_Statics::NewProp_DisplayUnit_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMeasurementActor_Statics::NewProp_DisplayUnit,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMeasurementActor_Statics::NewProp_ManualSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMeasurementActor_Statics::NewProp_bLinearSpline,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMeasurementActor_Statics::NewProp_bShowClosingLine,
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
	FuncInfo,
	Z_Construct_UClass_AMeasurementActor_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_AMeasurementActor_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AMeasurementActor_Statics::Class_MetaDataParams), Z_Construct_UClass_AMeasurementActor_Statics::Class_MetaDataParams)
};
void AMeasurementActor::StaticRegisterNativesAMeasurementActor()
{
	UClass* Class = AMeasurementActor::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_AMeasurementActor_Statics::Funcs));
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
		{ Z_Construct_UClass_AMeasurementActor, AMeasurementActor::StaticClass, TEXT("AMeasurementActor"), &Z_Registration_Info_UClass_AMeasurementActor, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMeasurementActor), 4138313154U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_ISILV125_Documents_GitHub_UnrealMeasurementToolPlugin_Plugins_UnrealMeasurementTool_Source_UnrealMeasurementTool_Public_MeasurementActor_h__Script_UnrealMeasurementTool_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_ISILV125_Documents_GitHub_UnrealMeasurementToolPlugin_Plugins_UnrealMeasurementTool_Source_UnrealMeasurementTool_Public_MeasurementActor_h__Script_UnrealMeasurementTool_2052824446{
	TEXT("/Script/UnrealMeasurementTool"),
	Z_CompiledInDeferFile_FID_Users_ISILV125_Documents_GitHub_UnrealMeasurementToolPlugin_Plugins_UnrealMeasurementTool_Source_UnrealMeasurementTool_Public_MeasurementActor_h__Script_UnrealMeasurementTool_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_ISILV125_Documents_GitHub_UnrealMeasurementToolPlugin_Plugins_UnrealMeasurementTool_Source_UnrealMeasurementTool_Public_MeasurementActor_h__Script_UnrealMeasurementTool_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
