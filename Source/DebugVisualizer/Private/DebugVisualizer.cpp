// Copyright Epic Games, Inc. All Rights Reserved.

#include "DebugVisualizer.h"
#include "DebugVisualizerComponent.h"

#define LOCTEXT_NAMESPACE "FDebugVisualizerModule"

void FDebugVisualizerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	TSharedPtr<FDebugVizComponentVisualizer> Visualizer = MakeShareable(new FDebugVizComponentVisualizer());

	GUnrealEd->RegisterComponentVisualizer(
			UDebugVisualizerComponent::StaticClass()->GetFName(), Visualizer);
}

void FDebugVisualizerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FDebugVisualizerModule, DebugVisualizer)