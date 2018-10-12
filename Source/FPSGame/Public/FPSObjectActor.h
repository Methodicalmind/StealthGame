// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSObjectActor.generated.h"

class USphereComponent;

UCLASS()
class FPSGAME_API AFPSObjectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSObjectActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//the object
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;
	//used for collision
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp;
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* PickupFX;
	//in protected because we don't want anyone else to call this function since it specific to this class.
	void PlayEffects();

public:	

	virtual void NotifyActorBeginOverlap(AActor* OtherActor);
	
};
