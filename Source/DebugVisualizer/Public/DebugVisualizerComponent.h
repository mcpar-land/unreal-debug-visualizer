// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ComponentVisualizer.h"
#include "UnrealEd.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "DebugVisualizerComponent.generated.h"

USTRUCT(BlueprintType)
struct FDebugVizStyle
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Relative = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor Color = FColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "10.0"))
	float Thickness = 1.0;
};

USTRUCT(BlueprintType)
struct FDebugVizPoint
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDebugVizStyle Style;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Position = FVector(0, 0, 0);
};

USTRUCT(BlueprintType)
struct FDebugVizLine
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDebugVizStyle Style;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Start = FVector(0, 0, 0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector End = FVector(0, 0, 100);
};

USTRUCT(BlueprintType)
struct FDebugVizCube
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDebugVizStyle Style;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Center = FVector(0, 0, 0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Bounds = FVector(100, 100, 100);
};

USTRUCT(BlueprintType)
struct FDebugVizCylinder
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDebugVizStyle Style;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Center = FVector(0, 0, 0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Radius = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Height = 100;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DEBUGVISUALIZER_API UDebugVisualizerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDebugVisualizerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug Shapes")
	TArray<FDebugVizPoint> Points;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug Shapes", meta = (AllowPrivateAccess = true))
	TArray<FDebugVizLine> Lines;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug Shapes", meta = (AllowPrivateAccess = true))
	TArray<FDebugVizCube> Cubes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug Shapes", meta = (AllowPrivateAccess = true))
	TArray<FDebugVizCylinder> Cylinders;

	FVector DebugPosition(FDebugVizStyle style, FVector PossiblyRelative) const;
};

class FDebugVizComponentVisualizer : public FComponentVisualizer
{
public:
	void DrawVisualization(const UActorComponent *Component, const FSceneView *View,
												 FPrimitiveDrawInterface *PDI) override;
};