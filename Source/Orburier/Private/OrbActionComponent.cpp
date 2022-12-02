// Fill out your copyright notice in the Description page of Project Settings.


#include "OrbActionComponent.h"
#include "NetworkPredictionModelDef.h"
#include "NetworkPredictionModelDefRegistry.h"
#include "NetworkPredictionProxyInit.h"
#include "Net/UnrealNetwork.h"
#include "Utils/OrburierLogging.h"


class FOrbActionComponentModelDef : public FNetworkPredictionModelDef
{
public:

	NP_MODEL_BODY();

	using Simulation = UOrbActionComponent;
	using StateTypes = TOrbActionNetTypes;
	using Driver = UOrbActionComponent;

	static const TCHAR* GetName() { return TEXT("OrbActionComponent"); }
	static constexpr int32 GetSortPriority() { return static_cast<int32>(ENetworkPredictionSortPriority::PreKinematicMovers) + 5; }
};

NP_MODEL_REGISTER(FOrbActionComponentModelDef);

// Sets default values for this component's properties
UOrbActionComponent::UOrbActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	bWantsInitializeComponent = true;
	SetIsReplicatedByDefault(true);

	bWantsInitializeComponent = true;
	// ...
}

void UOrbActionComponent::InitializeComponent()
{
	Super::InitializeComponent();

	UWorld* world = GetWorld();
	if(!world)
	{
		UE_LOG(OrburierLog, Error, TEXT("UOrbActionComponent could not get world"))
		return;
	}

	const UNetworkPredictionWorldManager* networkPredictionWorldManager = world->GetSubsystem<UNetworkPredictionWorldManager>();
	if(!networkPredictionWorldManager)
	{
		UE_LOG(OrburierLog, Error, TEXT("UOrbActionComponent could not get UNetworkPredictionWorldManager"))
		return;
	}

	// Init RepProxies
	ReplicationProxy_ServerRPC.Init(&NetworkPredictionProxy, EReplicationProxyTarget::ServerRPC);
	ReplicationProxy_Autonomous.Init(&NetworkPredictionProxy, EReplicationProxyTarget::AutonomousProxy);
	ReplicationProxy_Simulated.Init(&NetworkPredictionProxy, EReplicationProxyTarget::SimulatedProxy);
	ReplicationProxy_Replay.Init(&NetworkPredictionProxy, EReplicationProxyTarget::Replay);

	InitializeNetworkPredictionProxy();

	CheckOwnerRoleChange();
}

void UOrbActionComponent::PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker)
{
	Super::PreReplication(ChangedPropertyTracker);
	
	CheckOwnerRoleChange();

	// We have to update our replication proxies so they can be accurately compared against client shadowstate during property replication. ServerRPC proxy does not need to do this.
	ReplicationProxy_Autonomous.OnPreReplication();
	ReplicationProxy_Simulated.OnPreReplication();
	ReplicationProxy_Replay.OnPreReplication();
}

void UOrbActionComponent::PreNetReceive()
{
	Super::PreNetReceive();
	CheckOwnerRoleChange();
}

void UOrbActionComponent::EndPlay(const EEndPlayReason::Type Reason)
{
	Super::EndPlay(Reason);
	NetworkPredictionProxy.EndPlay();
}

void UOrbActionComponent::CallServerRPC()
{
	// Temp hack to make sure the ServerRPC doesn't get suppressed from bandwidth limiting
	// (system hasn't been optimized and not mature enough yet to handle gaps in input stream)
	FScopedBandwidthLimitBypass BandwidthBypass(GetOwner());

	FServerReplicationRPCParameter ProxyParameter(ReplicationProxy_ServerRPC);
	ServerReceiveClientInput(ProxyParameter);
}

void UOrbActionComponent::ProduceInput(const int32 DeltaTimeMS, FOrbActionNetInput* Cmd)
{
	UE_LOG(OrburierLog, Verbose, TEXT("UOrbActionComponent::ProduceInput"))
}

void UOrbActionComponent::RestoreFrame(const FOrbActionNetSync* SyncState, const FOrbActionNetAux* AuxState)
{
	UE_LOG(OrburierLog, Verbose, TEXT("UOrbActionComponent::RestoreFrame"))
}

void UOrbActionComponent::FinalizeFrame(const FOrbActionNetSync* SyncState, const FOrbActionNetAux* AuxState)
{
	UE_LOG(OrburierLog, Verbose, TEXT("UOrbActionComponent::FinalizeFrame"))
}

void UOrbActionComponent::InitializeSimulationState(FOrbActionNetSync* Sync, FOrbActionNetAux* Aux)
{
	UE_LOG(OrburierLog, Verbose, TEXT("UOrbActionComponent::InitializeSimulationState"))
}

void UOrbActionComponent::SimulationTick(const FNetSimTimeStep& TimeStep, const TNetSimInput<TOrbActionNetTypes>& Input, const TNetSimOutput<TOrbActionNetTypes>& Output)
{
	UE_LOG(OrburierLog, Verbose, TEXT("UOrbActionComponent::SimulationTick"))
}

// Called when the game starts
void UOrbActionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UOrbActionComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME( UOrbActionComponent, NetworkPredictionProxy);
	DOREPLIFETIME_CONDITION( UOrbActionComponent, ReplicationProxy_Autonomous, COND_AutonomousOnly);
	DOREPLIFETIME_CONDITION( UOrbActionComponent, ReplicationProxy_Simulated, COND_SimulatedOnly);
	DOREPLIFETIME_CONDITION( UOrbActionComponent, ReplicationProxy_Replay, COND_ReplayOnly);
}

void UOrbActionComponent::ServerReceiveClientInput_Implementation(const FServerReplicationRPCParameter& ProxyParameter)
{
	// The const_cast is unavoidable here because the replication system only allows by value (forces copy, bad) or by const reference. This use case is unique because we are using the RPC parameter as a temp buffer.
	const_cast<FServerReplicationRPCParameter&>(ProxyParameter).NetSerializeToProxy(ReplicationProxy_ServerRPC);
}

bool UOrbActionComponent::ServerReceiveClientInput_Validate(const FServerReplicationRPCParameter& ProxyParameter)
{
	return true;
}

void UOrbActionComponent::InitializeNetworkPredictionProxy()
{
	NetworkPredictionProxy.Init<FOrbActionComponentModelDef>(GetWorld(), GetReplicationProxies(), this, this);
}

void UOrbActionComponent::InitializeForNetworkRole(ENetRole Role, const bool bHasNetConnection)
{
	NetworkPredictionProxy.InitForNetworkRole(Role, bHasNetConnection);
}

bool UOrbActionComponent::CheckOwnerRoleChange()
{
	AActor* OwnerActor = GetOwner();
	const ENetRole CurrentRole = OwnerActor->GetLocalRole();
	const bool bHasNetConnection = OwnerActor->GetNetConnection() != nullptr;
	
	if (CurrentRole != NetworkPredictionProxy.GetCachedNetRole() || bHasNetConnection != NetworkPredictionProxy.GetCachedHasNetConnection())
	{
		InitializeForNetworkRole(CurrentRole, bHasNetConnection);
		return true;
	}

	return false;
}

