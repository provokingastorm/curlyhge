#ifndef ESMGameSubsystem_H_
#define ESMGameSubsystem_H_

#ifndef EngineSubsystem_H_
#include "enginesubsystem.h"
#endif

#include "hge.h"

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

    void CleanupGameInstance();

    hgeQuad PlayableAreaQuad;
    class RenderedQuad* PlayableAreaRenderable;
    class ESMGameInstance* GameInstance;
};

#endif

// EOF
