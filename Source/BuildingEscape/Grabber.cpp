// Building Escape - Copywrite Chris Matthewman 2021
#include "Grabber.h"
#include "CollisionQueryParams.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Controller.h"

//define something
#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	//GetFirstPhysicsBodyInReach();
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandle();
	SetupInputComponent();
}

// check for input component
void UGrabber::SetupInputComponent() 
{
	//Returns first component of the specified class
	InputCom = GetOwner()->FindComponentByClass<UInputComponent>();
	//protect from crash
	if (InputCom)
	{
		//input component is found
		UE_LOG(LogTemp, Warning, TEXT("Input component attached to: %s "), *GetOwner()->GetName());

		//bind action (set-up in preferences>input) to input component
		InputCom->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputCom->BindAction("Grab", IE_Released, this, &UGrabber::ReleaseObject);
		/*BindCation params =
			1) The name of the set up action
			2) The type of action that triggers it
			3) The object
			4) Address (&) to a function
		*/
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Input component attached to: %s"), *GetOwner()->GetName());
	}
}

// check for physics handle component
void UGrabber::FindPhysicsHandle() 
{
	//Returns first component of the specified class
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	//protect from crash
	if (PhysicsHandle)
	{
		//Physics handle is found
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Physics handle attached to: %s"), *GetOwner()->GetName());
	}
}

//Grab object
void UGrabber::Grab() 
{
	UE_LOG(LogTemp, Warning, TEXT("Grabbing"));
	//try and reach any AActors with a 'physics body' collision channel set

	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(
		OUT PlayerViewpointLocation,
		OUT PlayerViewpointRotation
	);

	FVector LineTraceDirection = PlayerViewpointRotation.Vector();
	FVector LineTraceEnd = PlayerViewpointLocation + LineTraceDirection * Reach;

	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

	//If we hit something, then attach physics handle
	if(HitResult.GetActor())
	{
		PhysicsHandle->GrabComponentAtLocation
		(
			ComponentToGrab,
			NAME_None,
			LineTraceEnd
		);
	}
}

//release object
void UGrabber::ReleaseObject() 
{
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->ReleaseComponent();
	}
	UE_LOG(LogTemp, Warning, TEXT("Released"));
	//TODO remove/release physics handle
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(
		OUT PlayerViewpointLocation,
		OUT PlayerViewpointRotation
	);

	FVector LineTraceDirection = PlayerViewpointRotation.Vector();
	FVector LineTraceEnd = PlayerViewpointLocation + LineTraceDirection * Reach;


// 	if physics handle is attached and has a grabbed component
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
// 		//move the object we are holding
// 	

		
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
// 		//Draw a line form the player
// 		//line endpoint
// 		FVector LineTraceDirection = PlayerViewpointRotation.Vector();
// 		FVector LineTraceEnd = PlayerViewpointLocation + LineTraceDirection * Reach;
// 	
// 		//draw debug line
// 		DrawDebugLine
// 		(
// 			GetWorld(),
// 			PlayerViewpointLocation, 
// 			LineTraceEnd, 
// 			FColor(0, 255, 0), 
// 			false, 
// 			0.f, 
// 			0, 
// 			3.f
// 		);

	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(
		OUT PlayerViewpointLocation,
		OUT PlayerViewpointRotation
	);

	FVector LineTraceDirection = PlayerViewpointRotation.Vector();
	FVector LineTraceEnd = PlayerViewpointLocation + LineTraceDirection * Reach;

	FHitResult hit;

	//TRACE PARAMS: Param 1: tag name (we aren't looking for tags here), Param 2: Are we using complex collision?, Param3: what do we need to ignore?
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	bool IsAHit = GetWorld()->LineTraceSingleByObjectType
	(
		OUT hit,
		PlayerViewpointLocation,
		LineTraceEnd,
		//set collision channel for object type
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	AActor* ActorHit = hit.GetActor();

	if (ActorHit) {
		UE_LOG(LogTemp, Error, TEXT("Actor hit: %s"), *ActorHit->GetName());
	}
	return hit;

}

