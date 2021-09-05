// Fill out your copyright notice in the Description page of Project Settings.

#pragma once // This means you only load the header files below once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WordPosition.generated.h" // generated file must be at the bottom of includes


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UWordPosition : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWordPosition(); //constructor

protected:
	// Called when the game starts
	virtual void BeginPlay() override; 

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
