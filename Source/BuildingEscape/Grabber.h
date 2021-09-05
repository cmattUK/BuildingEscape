// Building Escape - Copywrite Chris Matthewman 2021

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game start
	virtual void BeginPlay() override;

private:
	float Reach = 100.f;
	// Declare member of UPhysicsHandle component then initialize to nullptr to avoid crashes
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputCom = nullptr;


	void Grab();
	void ReleaseObject();
	void FindPhysicsHandle();
	void SetupInputComponent();
	FHitResult GetFirstPhysicsBodyInReach() const;
};

