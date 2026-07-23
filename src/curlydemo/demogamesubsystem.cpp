#include "demogamesubsystem.h"
#include "curlyengine.h"

// ----------------------------------------------------------------------------
// Global function for the Curly Engine
// ----------------------------------------------------------------------------

IMPLEMENT_GAME_SUBSYSTEM_CREATOR(DemoGameSubsystem);

// ----------------------------------------------------------------------------
// DemoGameSubsystem - Definition
// ----------------------------------------------------------------------------

void DemoGameSubsystem::InitializeGameEngine()
{
    CurlyEngine& CE = CurlyEngine::Instance();

    CE.Initialize("Demo", "Demo");

    // Add other subsystems here
    CE.AddEngineSubsystem(*this);
}

void DemoGameSubsystem::InitializeInternal()
{
}

void DemoGameSubsystem::ShutdownInternal()
{
}

void DemoGameSubsystem::Tick(float DeltaTime)
{
}

void DemoGameSubsystem::Render()
{
    HGE& HGERef = CurlyEngine::Instance().GetHGE();
    HGERef.Gfx_BeginScene();
    HGERef.Gfx_Clear(0);

    // Your render code goes here!

    HGERef.Gfx_EndScene();
}

// EOF
