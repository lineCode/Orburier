// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetworkPredictionProxy.h"
#include "NetworkPredictionReplicationProxy.h"
#include "NetworkPredictionSimulation.h"
#include "NetworkPredictionStateTypes.h"
#include "Components/ActorComponent.h"
#include "Net/OrbActionNetAux.h"
#include "Net/OrbActionNetInput.h"
#include "Net/OrbActionNetSync.h"
#include "Utils/OrburierLogging.h"
#include "OrbActionComponent.generated.h"


struct FNetSimTimeStep;
using TOrbActionNetTypes = TNetworkPredictionStateTypes<FOrbActionNetInput, FOrbActionNetSync, FOrbActionNetAux>;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ORBURIER_API UOrbActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOrbActionComponent();

	virtual void InitializeComponent() override;
	
	virtual void PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker) override;
	virtual void PreNetReceive() override;
	virtual void EndPlay(const EEndPlayReason::Type Reason);

public:
	// Invoke the ServerRPC, called from UNetworkPredictionWorldManager via the TServerRPCService.
	void CallServerRPC();
	
	// Get latest local input prior to simulation step
	void ProduceInput(const int32 DeltaTimeMS, struct FOrbActionNetInput* Cmd);

	// Restore a previous frame prior to resimulating
	void RestoreFrame(const FOrbActionNetSync* SyncState, const FOrbActionNetAux* AuxState);

	// Take output for simulation
	void FinalizeFrame(const FOrbActionNetSync* SyncState, const FOrbActionNetAux* AuxState);

	// Seed initial values based on component's state
	void InitializeSimulationState(FOrbActionNetSync* Sync, FOrbActionNetAux* Aux);
	
	// Called every frame
	void SimulationTick(const FNetSimTimeStep& TimeStep, const TNetSimInput<TOrbActionNetTypes>& Input, const TNetSimOutput<TOrbActionNetTypes>& Output);

protected:
	// Classes must initialize the NetworkPredictionProxy (register with the NetworkPredictionSystem) here. EndPlay will unregister.
	virtual void InitializeNetworkPredictionProxy();

	// Finalizes initialization when NetworkRole changes. Does not need to be overridden.
	virtual void InitializeForNetworkRole(ENetRole Role, const bool bHasNetConnection);

	// Helper: Checks if the owner's role has changed and calls InitializeForNetworkRole if necessary.
	bool CheckOwnerRoleChange();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UFUNCTION(Server, unreliable, WithValidation)
	void ServerReceiveClientInput(const FServerReplicationRPCParameter& ProxyParameter);

	// Proxy to interface with the NetworkPrediction system
	UPROPERTY(Replicated, transient)
	FNetworkPredictionProxy NetworkPredictionProxy;

	// ReplicationProxies are just pointers to the data/NetSerialize functions within the NetworkSim
	UPROPERTY()
	FReplicationProxy ReplicationProxy_ServerRPC;

	FReplicationProxySet GetReplicationProxies()
	{
		return FReplicationProxySet{ &ReplicationProxy_ServerRPC, &ReplicationProxy_Autonomous, &ReplicationProxy_Simulated, &ReplicationProxy_Replay };
	}
	
private:
	UPROPERTY(Replicated, transient)
	FReplicationProxy ReplicationProxy_Autonomous;

	UPROPERTY(Replicated, transient)
	FReplicationProxy ReplicationProxy_Simulated;

	UPROPERTY(Replicated, transient)
	FReplicationProxy ReplicationProxy_Replay;
};
