// Building Escape - Copywrite Chris Matthewman 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
	void CloseDoor(float DeltaTime);
	void OpenDoor(float DeltaTime);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	

private:
	float InitialYaw;
	float CurrentYaw;

	float DoorLastOpened = 0.f;

	//expose to editor
	UPROPERTY(EditAnywhere)
	float OpenAngle = 90.f;

	UPROPERTY(EditAnywhere)
	float DoorOpenSpeed = 8.f;

	UPROPERTY(EditAnywhere)
	float DoorClosingSpeed = 3.5f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 0.f;

	//Set up a trigger volume
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;
	
	//What triggers the volume
	UPROPERTY(EditAnywhere)
	AActor* ActorThatOpens;



};