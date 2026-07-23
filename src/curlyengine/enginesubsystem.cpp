#include "enginesubsystem.h"

EngineSubsystem::EngineSubsystem()
	: bIsInitialized(false)
	, bTickedOnce(false)
{
}

EngineSubsystem::~EngineSubsystem()
{
}

void EngineSubsystem::Initialize()
{
	bTickedOnce = false;

	InitializeInternal();
	bIsInitialized = true;
}

void EngineSubsystem::Shutdown()
{
	ShutdownInternal();
	bIsInitialized = false;
}

void EngineSubsystem::OnFirstEngineTick()
{
	FirstEngineTickInternal();
	bTickedOnce = true;
}
