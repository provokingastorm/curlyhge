#include "enginesubsystem.h"
#include "curlyengine.h"
#include "..\..\include\hge.h"

#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


extern EngineSubsystem& GetGameSubsystem();

// ----------------------------------------------------------------------------
// WinMain
// ----------------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	EngineSubsystem& Subsystem = GetGameSubsystem();
	Subsystem.InitializeGameEngine();

	// Now, run the game
    CurlyEngine::Instance().Startup();

	// At this point, the player exited the application in the game-specific way
	CurlyEngine::Instance().Shutdown();

	// Dump memory leaks
#if defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}
