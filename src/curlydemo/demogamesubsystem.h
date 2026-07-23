#pragma once

#ifndef DemoGameSubsystem_H_
#define DemoGameSubsystem_H_

#ifndef EngineSubsystem_H_
#include "enginesubsystem.h"
#endif

#include "hge.h"
#include "hgevector.h"

// ----------------------------------------------------------------------------
// DemoGameSubsystem - Declaration
// ----------------------------------------------------------------------------

class DemoGameSubsystem : public EngineSubsystem
{
public:
    DECLARE_SUBSYSTEM(DemoGameSubsystem);

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
};

#endif

// EOF
