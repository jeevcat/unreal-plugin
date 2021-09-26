// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ContextWidget.h"
#include "CoreMinimal.h"

#include "ThemeContextWidget.generated.h"

/**
 *
 */
UCLASS()
class UNREALPLUGIN_API UThemeContextWidget final : public UContextWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FLinearColor Theme;
};
