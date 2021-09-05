// Building Escape - Copywrite Chris Matthewman 2021
#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFrameWork/Actor.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	//Show an error if the pPressurePlate pinter is Null
	if (!PressurePlate) {
	FString NoPlateName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s has no PressurePlate set!"), *NoPlateName);
	}
	
	//get the player pawn
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;

	//Compound assignment means add itself plus another value
	OpenAngle += InitialYaw; 
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//protecting from null pointers
	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor(DeltaTime);
		//When the door was last opened
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else
	{
		/*door has been opened longer than indicated seconds then close the door*/
		if ((GetWorld()->GetTimeSeconds() - DoorLastOpened) > DoorCloseDelay)
		{
			CloseDoor(DeltaTime);
		}
	}
	
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	// Lerp the Yaw between CurrentYaw and OpenAngle
	//!!!interpolation with easing!!!
	CurrentYaw = FMath::FInterpTo(CurrentYaw, OpenAngle, DeltaTime, DoorOpenSpeed);
	// Create an FRotator called Open door with current rotation
	FRotator OpenDoor = GetOwner()->GetActorRotation();

	//!!!Constant interpolation!!!
	//OpenDoor.Yaw = FMath::FInterpConstantTo(CurrentYaw, -OpenAngle, DeltaTime, 90);
	
	OpenDoor.Yaw = CurrentYaw;
	//Fire the Lerp on the actor
	GetOwner()->SetActorRotation(OpenDoor);

}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	// Lerp the Yaw between CurrentYaw and OpenAngle
	//!!!interpolation with easing!!!
	CurrentYaw = FMath::FInterpTo(CurrentYaw, InitialYaw, DeltaTime, DoorClosingSpeed);
	// Create an FRotator called Close door with current rotation
	FRotator CloseDoor = GetOwner()->GetActorRotation();

	CloseDoor.Yaw = CurrentYaw;
	//Fire the Lerp on the actor
	GetOwner()->SetActorRotation(CloseDoor);

}

