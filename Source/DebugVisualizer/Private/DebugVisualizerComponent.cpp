// Fill out your copyright notice in the Description page of Project Settings.

#include "DebugVisualizerComponent.h"

// Sets default values for this component's properties
UDebugVisualizerComponent::UDebugVisualizerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UDebugVisualizerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

// Called every frame
void UDebugVisualizerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FVector UDebugVisualizerComponent::DebugPosition(FDebugVizStyle style, FVector PossiblyRelative) const
{
	if (style.Relative)
	{
		const AActor *Owner = this->GetOwner();
		const FVector Location = Owner->GetActorLocation();
		return PossiblyRelative + Location;
	}
	else
	{
		return PossiblyRelative;
	}
}

void FDebugVizComponentVisualizer::DrawVisualization(
		const UActorComponent *Component,
		const FSceneView *View,
		FPrimitiveDrawInterface *PDI)
{
	const UDebugVisualizerComponent *DrawComponent = Cast<UDebugVisualizerComponent>(Component);

	for (int i = 0; i < DrawComponent->Points.Num(); i++)
	{
		const FDebugVizPoint Point = DrawComponent->Points[i];
		PDI->DrawPoint(
				DrawComponent->DebugPosition(Point.Style, Point.Position),
				Point.Style.Color,
				Point.Style.Thickness,
				SDPG_Foreground);
	}

	for (int i = 0; i < DrawComponent->Lines.Num(); i++)
	{
		const FDebugVizLine Line = DrawComponent->Lines[i];
		PDI->DrawLine(
				DrawComponent->DebugPosition(Line.Style, Line.Start),
				DrawComponent->DebugPosition(Line.Style, Line.End),
				Line.Style.Color,
				SDPG_Foreground,
				Line.Style.Thickness);
	}
}