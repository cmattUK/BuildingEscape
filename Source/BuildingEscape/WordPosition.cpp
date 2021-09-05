// Fill out your copyright notice in the Description page of Project Settings.

#include "WordPosition.h"
#include "GameFramework/Actor.h"
#include "Math/Vector.h"
#include "Math/TransformNonVectorized.h"
// Sets default values for this component's properties
UWordPosition::UWordPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; // 'true' means that it WILL run every frame

	// ...
}


// Called when the game starts
void UWordPosition::BeginPlay()
{
	Super::BeginPlay(); // everything further up the hierarchy has to be run first and then we can run the code under

//  !!!!------------------------Pointers ------------------------!!!!
// 
// 	FString Log = TEXT("Hello!");
// 
// 	//* pointer is a memory address
// 	FString* PtrLog = &Log;
// 
// 	//dereferencing and accessing members
// 	PtrLog->Len();
// 
// 	//console logging for error reporting !!!
// 	UE_LOG(LogTemp, Warning, TEXT("%s"), **PtrLog); //dereferencing and overloading operator - logging a pointer
// 
//	!!!!------------------------END Pointers------------------------!!!!

	
	//Get this actor and the attached object name with the pointer GetOwner()->
	FString ObjName = GetOwner()->GetName();
	//get FVector as String
	FString ObjPosition = GetOwner()->GetActorLocation().ToString();
	//UE_LOG(LogTemp, Warning, TEXT("%s is at position: %s"), *ObjName, *ObjPosition);
	
}


// Called every frame
void UWordPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Run every frame
}

