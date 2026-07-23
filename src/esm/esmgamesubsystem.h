#pragma once

#ifndef ESMGameSubsystem_H_
#define ESMGameSubsystem_H_

#ifndef EngineSubsystem_H_
#include "enginesubsystem.h"
#endif

#include "hge.h"
#include "hgevector.h"

// ----------------------------------------------------------------------------
// ESMGameSubsystem - Declaration
// ----------------------------------------------------------------------------

class ESMGameSubsystem : public EngineSubsystem
{
public:
    DECLARE_SUBSYSTEM(ESMGameSubsystem);

    // --------------------------------------------------------
    //	EngineSubsystem inherited methods

    void InitializeGameEngine();

private:

    // --------------------------------------------------------
    //	EngineSubsystem inherited methods

    void InitializeInternal();
    void ShutdownInternal();
    void Tick(float DeltaTime);
    void Render();

    hgeQuad PlayableAreaQuad;
    class RenderedQuad* PlayableAreaRenderable;
    class ESMGameInstance* GameInstance;



    hgeQuad FloorQuad;
    hgeQuad NetQuad;

    class RenderedQuad* FloorRenderable;
    class RenderedQuad* NetRenderable;

    class StaticImage* PlayerSlimeStaticImage;
    class hgeSprite* PlayerSlime;

    hgeVector PlayerSlimeLocation;
    hgeVector PlayerSlimeVelocity;

    HTEXTURE PlayerSlimeHandle;
};

#endif

// EOF
