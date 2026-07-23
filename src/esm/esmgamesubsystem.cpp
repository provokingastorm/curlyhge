#include "esmgamesubsystem.h"
#include "esmgameinstance.h"
#include "curlyengine.h"
#include "sharedrenderables.h"


// ----------------------------------------------------------------------------
// Global function for the Curly Engine
// ----------------------------------------------------------------------------

IMPLEMENT_GAME_SUBSYSTEM_CREATOR(ESMGameSubsystem);

// ----------------------------------------------------------------------------
// ESMGameSubsystem - Definition
// ----------------------------------------------------------------------------

void ESMGameSubsystem::InitializeGameEngine()
{
    CurlyEngine& CE = CurlyEngine::Instance();

    CE.Initialize("ESM", "ESM");

    // Add other subsystems here
    CE.AddEngineSubsystem(*this);
}

void ESMGameSubsystem::InitializeInternal()
{
    const int ScreenWidth = CurlyEngine::Instance().GetScreenWidth();
    const int ScreenHeight = CurlyEngine::Instance().GetScreenHeight();

    // Setup the playable area quad
    const float PlayableAreaWidth = 750.0f;
    const float PlayableAreaHeight = 375.0f;
    const float HalfPlayableWidth = PlayableAreaWidth * 0.5f;
    const float HalfPlayableHeight = PlayableAreaHeight * 0.5f;
    const float HalfScreenWidth = ScreenWidth * 0.5f;
    const float HalfScreenHeight = ScreenHeight * 0.5f;
    PlayableAreaQuad.v[0].x = HalfScreenWidth - HalfPlayableWidth;
    PlayableAreaQuad.v[0].y = HalfScreenHeight - HalfPlayableHeight;
    PlayableAreaQuad.v[1].x = HalfScreenWidth + HalfPlayableWidth;
    PlayableAreaQuad.v[1].y = PlayableAreaQuad.v[0].y;
    PlayableAreaQuad.v[2].x = PlayableAreaQuad.v[1].x;
    PlayableAreaQuad.v[2].y = HalfScreenHeight + HalfPlayableHeight;
    PlayableAreaQuad.v[3].x = PlayableAreaQuad.v[0].x;
    PlayableAreaQuad.v[3].y = PlayableAreaQuad.v[2].y;

    // Setup the engine to render the playable area in blue
    for (int i = 0; i < 4; i++)
    {
        PlayableAreaQuad.v[i].col = 0xFF0000FF;
    }

    PlayableAreaQuad.blend = (hgeBlendMode)(BLEND_DEFAULT);

    // Setup the rendering of the playable area
    PlayableAreaRenderable = new RenderedQuad();
    PlayableAreaRenderable->SetContent(PlayableAreaQuad);

    // Setup the game instance
    CleanupGameInstance();
    GameInstance = new ESMVolleyballGameInstance();
    GameInstance->Initialize(PlayableAreaQuad);

    // NOTE: This will need to move when implementing a UI that triggers the start of the game
    GameInstance->StartGame();
}

void ESMGameSubsystem::ShutdownInternal()
{
    CleanupGameInstance();

    if (PlayableAreaRenderable != NULL)
    {
        delete PlayableAreaRenderable;
        PlayableAreaRenderable = NULL;
    }
}

void ESMGameSubsystem::Tick(float DeltaTime)
{
    if (PlayableAreaRenderable != NULL)
    {
        CurlyEngine::Instance().AddToRenderQueue(*PlayableAreaRenderable);
    }

    if (GameInstance != NULL)
    {
        GameInstance->Tick(DeltaTime);
    }
}

void ESMGameSubsystem::Render()
{
}

void ESMGameSubsystem::CleanupGameInstance()
{
    if (GameInstance != NULL)
    {
        GameInstance->StopGame();
        delete GameInstance;
        GameInstance = NULL;
    }
}

// EOF
