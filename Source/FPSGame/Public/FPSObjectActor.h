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
	UStaticMeshComponent* MeshComp;
	//used for collision
	USphereComponent* SphereComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
