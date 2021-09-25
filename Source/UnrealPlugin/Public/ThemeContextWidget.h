// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ContextWidget.h"
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
