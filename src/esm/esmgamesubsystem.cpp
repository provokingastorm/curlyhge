#include "esmgamesubsystem.h"
#include "curlyengine.h"
#include "hgesprite.h"


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
    FloorQuad = {};
    NetQuad = {};

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

    // Setup the floor quad
    const float FloorTopY = PlayableAreaQuad.v[3].y - (PlayableAreaHeight * 0.2f);
    FloorQuad.v[0].x = PlayableAreaQuad.v[0].x;
    FloorQuad.v[0].y = FloorTopY;
    FloorQuad.v[1].x = PlayableAreaQuad.v[1].x;
    FloorQuad.v[1].y = FloorTopY;
    FloorQuad.v[2].x = PlayableAreaQuad.v[2].x;
    FloorQuad.v[2].y = PlayableAreaQuad.v[2].y;
    FloorQuad.v[3].x = PlayableAreaQuad.v[3].x;
    FloorQuad.v[3].y = PlayableAreaQuad.v[3].y;

    // Setup the engine to render the floor in gray
    for (int i = 0; i < 4; i++)
    {
        FloorQuad.v[i].col = 0xFF808080;
    }

    FloorQuad.blend = (hgeBlendMode)(BLEND_DEFAULT);

    // Setup the net
    const float NetWidth = 4.0f;
    const float NetHeight = 40.0f;
    float NetBottomLeftX = std::abs(ScreenWidth * 0.5);
    float NetBottomLeftY = FloorTopY + 10.0f; // Add pixels to push the net down visually from the floor to mimic the original
    float NetTopLeftY = NetBottomLeftY - NetHeight;

    NetQuad.v[0].x = NetBottomLeftX;
    NetQuad.v[0].y = NetTopLeftY;
    NetQuad.v[1].x = NetBottomLeftX + NetWidth;
    NetQuad.v[1].y = NetTopLeftY;
    NetQuad.v[2].x = NetBottomLeftX + NetWidth;
    NetQuad.v[2].y = NetBottomLeftY;
    NetQuad.v[3].x = NetBottomLeftX;
    NetQuad.v[3].y = NetBottomLeftY;

    for (int i = 0; i < 4; i++)
    {
        NetQuad.v[i].col = 0xFFFFFFFF;
    }

    NetQuad.blend = (hgeBlendMode)(BLEND_DEFAULT);

    PlayerSlimeHandle = CurlyEngine::Instance().GetHGE().Texture_Load("esm/art/SlimeTest.png");

    if (PlayerSlimeHandle)
    {
        const float PlayerSlimeWidth = 32.0f;
        const float PlayerSlimeHeight = 32.0f;
        PlayerSlime = new hgeSprite(PlayerSlimeHandle, 0.0f, 0.0f, PlayerSlimeWidth, PlayerSlimeHeight);

        if (PlayerSlime != NULL)
        {
            // Calculate the player's starting position by placing him in the center of the left side of the net.
            const float LeftCourtDistance = (NetQuad.v[0].x - FloorQuad.v[0].x) * 0.5f;
            PlayerSlimeLocation.x = LeftCourtDistance + FloorQuad.v[0].x - (PlayerSlimeWidth * 0.5f);
            PlayerSlimeLocation.y = NetQuad.v[3].y - PlayerSlimeHeight;
        }
    }
}

void ESMGameSubsystem::ShutdownInternal()
{
    if (PlayerSlime != NULL)
    {
        delete PlayerSlime;
        PlayerSlime = NULL;
    }
}

void ESMGameSubsystem::Tick(float DeltaTime)
{
}

void ESMGameSubsystem::Render()
{
    HGE& HGERef = CurlyEngine::Instance().GetHGE();
    HGERef.Gfx_BeginScene();
    HGERef.Gfx_Clear(0);

    HGERef.Gfx_RenderQuad(&PlayableAreaQuad);
    HGERef.Gfx_RenderQuad(&FloorQuad);
    HGERef.Gfx_RenderQuad(&NetQuad);

    if (PlayerSlime != NULL)
    {
        PlayerSlime->RenderEx(PlayerSlimeLocation.x, PlayerSlimeLocation.y, 0.0f);
    }

    HGERef.Gfx_EndScene();
}

// EOF
