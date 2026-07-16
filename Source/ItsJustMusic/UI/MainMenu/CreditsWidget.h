// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CreditsWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCreditsReturnClicked);

/**
 * 
 */
UCLASS()
class ITSJUSTMUSIC_API UCreditsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FOnCreditsReturnClicked OnCreditsReturnClicked;

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> ButtonReturn;

private:
	UFUNCTION()
	void OnButtonReturnClicked();
};
