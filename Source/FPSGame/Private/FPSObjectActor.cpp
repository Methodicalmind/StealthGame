// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSObjectActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FPSCharacter.h"


// Sets default values
AFPSObjectActor::AFPSObjectActor()
{
	//holds the mesh of the object and is the root component
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;
	
	//Is the collision radius and is attached to the mesh
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	
	//no physics we just want queries (overlapping, etc..)
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//turn off a response for all channels
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	//turn on for this specific channel
	//pawn is the player
	//So it is off for everything except the player in which it can overlap
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetupAttachment(MeshComp);
}

// Called when the game starts or when spawned
void AFPSObjectActor::BeginPlay()
{
	Super::BeginPlay();
	PlayEffects();
}

void AFPSObjectActor::NotifyActorBeginOverlap(AActor * OtherActor)
{
	//call the base implementation from the actor class
	Super::NotifyActorBeginOverlap(OtherActor);
	PlayEffects();

	AFPSCharacter* MyCharacter = Cast<AFPSCharacter>(OtherActor);
	if (MyCharacter)
	{
		MyCharacter->bIsCarryingObject = true;
		Destroy();
	}
}

void AFPSObjectActor::PlayEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, PickupFX, GetActorLocation());
}

