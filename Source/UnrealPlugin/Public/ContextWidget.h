// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SWidget.h"
#include "Components/ContentWidget.h"
#include "ContextWidget.generated.h"

class SBox;

/**
 * Allows you to expose an external slot for your user widget.  When others reuse your user control,
 * they can put whatever they want in this named slot.
 */
UCLASS()
class UNREALPLUGIN_API UContextWidget : public UContentWidget
{
	GENERATED_BODY()

public:
	UContextWidget();
	// UPanelWidget interface
	virtual void OnSlotAdded(UPanelSlot* Slot) override;
	virtual void OnSlotRemoved(UPanelSlot* Slot) override;
	// End of UPanelWidget interface

	// UVisual interface
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	// End of UVisual interface

#if WITH_EDITOR
	// UWidget interface
	virtual const FText GetPaletteCategory() override;
	// End of UWidget interface
#endif

	UFUNCTION(BlueprintPure, meta = (DefaultToSelf = Widget, HidePin = Widget, DeterminesOutputType = Type))
	static UContextWidget* GetContext(UWidget* Widget, TSubclassOf<UContextWidget> Type);

protected:
	// UWidget interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	// End of UWidget interface

	TSharedPtr<SBox> MyBox;
};
