// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "kismet/GameplayStatics.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn, bool bMissionSuccess)
{
	if (InstigatorPawn)
	{
		InstigatorPawn->DisableInput(nullptr);

		if (SpectatorViewpointClass)
		{
			TArray<AActor*> ReturnedActors;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatorViewpointClass, ReturnedActors);

			//change view target if any actor found
			if (ReturnedActors.Num() > 0)
			{
				AActor* NewViewtarget = ReturnedActors[0];
				APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());
				if (PC)
				{
					PC->SetViewTargetWithBlend(NewViewtarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SpectatorViewpointClass is null. Please update gamemode class with valis subclass. Cannot change spectating view targets"))
		}
	}


	OnMissionCompleted(InstigatorPawn, bMissionSuccess);
}

