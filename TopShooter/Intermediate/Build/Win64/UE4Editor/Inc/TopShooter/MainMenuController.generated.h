// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef TOPSHOOTER_MainMenuController_generated_h
#error "MainMenuController.generated.h already included, missing '#pragma once' in MainMenuController.h"
#endif
#define TOPSHOOTER_MainMenuController_generated_h

#define TopShooter_Source_TopShooter_MainMenuController_h_15_RPC_WRAPPERS
#define TopShooter_Source_TopShooter_MainMenuController_h_15_RPC_WRAPPERS_NO_PURE_DECLS
#define TopShooter_Source_TopShooter_MainMenuController_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAMainMenuController(); \
	friend struct Z_Construct_UClass_AMainMenuController_Statics; \
public: \
	DECLARE_CLASS(AMainMenuController, APlayerController, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/TopShooter"), NO_API) \
	DECLARE_SERIALIZER(AMainMenuController)


#define TopShooter_Source_TopShooter_MainMenuController_h_15_INCLASS \
private: \
	static void StaticRegisterNativesAMainMenuController(); \
	friend struct Z_Construct_UClass_AMainMenuController_Statics; \
public: \
	DECLARE_CLASS(AMainMenuController, APlayerController, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/TopShooter"), NO_API) \
	DECLARE_SERIALIZER(AMainMenuController)


#define TopShooter_Source_TopShooter_MainMenuController_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AMainMenuController(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AMainMenuController) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AMainMenuController); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AMainMenuController); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AMainMenuController(AMainMenuController&&); \
	NO_API AMainMenuController(const AMainMenuController&); \
public:


#define TopShooter_Source_TopShooter_MainMenuController_h_15_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AMainMenuController(AMainMenuController&&); \
	NO_API AMainMenuController(const AMainMenuController&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AMainMenuController); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AMainMenuController); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AMainMenuController)


#define TopShooter_Source_TopShooter_MainMenuController_h_15_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__keyPressed() { return STRUCT_OFFSET(AMainMenuController, keyPressed); } \
	FORCEINLINE static uint32 __PPO__wMainMenu() { return STRUCT_OFFSET(AMainMenuController, wMainMenu); }


#define TopShooter_Source_TopShooter_MainMenuController_h_12_PROLOG
#define TopShooter_Source_TopShooter_MainMenuController_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	TopShooter_Source_TopShooter_MainMenuController_h_15_PRIVATE_PROPERTY_OFFSET \
	TopShooter_Source_TopShooter_MainMenuController_h_15_RPC_WRAPPERS \
	TopShooter_Source_TopShooter_MainMenuController_h_15_INCLASS \
	TopShooter_Source_TopShooter_MainMenuController_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define TopShooter_Source_TopShooter_MainMenuController_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	TopShooter_Source_TopShooter_MainMenuController_h_15_PRIVATE_PROPERTY_OFFSET \
	TopShooter_Source_TopShooter_MainMenuController_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	TopShooter_Source_TopShooter_MainMenuController_h_15_INCLASS_NO_PURE_DECLS \
	TopShooter_Source_TopShooter_MainMenuController_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> TOPSHOOTER_API UClass* StaticClass<class AMainMenuController>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID TopShooter_Source_TopShooter_MainMenuController_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
