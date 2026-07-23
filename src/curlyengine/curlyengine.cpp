#include "curlyengine.h"
#include "enginesubsystem.h"
#include "debugutilities.h"
#include "curlycore.h"
#include "hgeresource.h"
#include "hge.h"

// ----------------------------------------------------------------------------
// HGE - Defines
// ----------------------------------------------------------------------------

#define GAME_NAME_LENGTH		48
#define GAME_NAME_SHORT_LENGTH	8


// ----------------------------------------------------------------------------
// HGE - Callbacks
// ----------------------------------------------------------------------------

bool FrameFunc()
{
    return CurlyEngine::Instance().Tick();
}

bool RenderFunc()
{
    CurlyEngine::Instance().Render();
    return false;
}

bool FocusLostFunc()
{
    CurlyEngine::Instance().OnFocusLost();
    return false;
}

bool FocusGainedFunc()
{
    CurlyEngine::Instance().OnFocusGained();
    return false;
}

bool ExitFunc()
{
    return true;
}

// ----------------------------------------------------------------------------
// CurlyEngine - Definition
// ----------------------------------------------------------------------------

CurlyEngine::CurlyEngine()
    : HGEEngine(NULL)
    , ResourceManager(NULL)
    , bIsHGEInitialized(false)
    , bExitApplication(false)
    , bTickedOnce(false)
    , GameName(NULL)
    , GameShortName(NULL)
    , ScreenWidth(640)
    , ScreenHeight(480)
{
}

CurlyEngine::~CurlyEngine()
{
}

void CurlyEngine::Initialize(char* InGameName, char* InGameShortName)
{
    CurlyAssert(bIsHGEInitialized == false, "Trying to initialize an already initialized engine");

    GameName = InGameName;
    GameShortName = ChzStrLower(InGameShortName);

    if (!bIsHGEInitialized)
    {
        if (HGEEngine == NULL)
        {
            HGEEngine = hgeCreate(HGE_VERSION);
        }

        // Setup the log file
        char LogFilename[128];
        sprintf(LogFilename, "logs/%s.log", GameShortName);
        HGEEngine->System_SetState(HGE_LOGFILE, LogFilename);

        HGEEngine->System_SetState(HGE_SHOWSPLASH, true);
        HGEEngine->System_SetState(HGE_FPS, 60);
        HGEEngine->System_SetState(HGE_TITLE, GameName);

        // Disable Sound otherwise game crashes without bass.dll
        HGEEngine->System_SetState(HGE_USESOUND, false);

        ImportEngineConfig();

        // Set the resource manager
        char ResourceFilename[128];
        sprintf(ResourceFilename, "%s/res/%sgame.res", GameShortName, GameShortName);
        ResourceManager = new hgeResourceManager(ResourceFilename);
        ResourceManager->Precache(RG_AlwaysLoaded);

        HGEEngine->System_SetState(HGE_FRAMEFUNC, FrameFunc);
        HGEEngine->System_SetState(HGE_RENDERFUNC, RenderFunc);
        HGEEngine->System_SetState(HGE_FOCUSLOSTFUNC, FocusLostFunc);
        HGEEngine->System_SetState(HGE_FOCUSGAINFUNC, FocusGainedFunc);
        HGEEngine->System_SetState(HGE_EXITFUNC, ExitFunc);

        bIsHGEInitialized = HGEEngine->System_Initiate();
    }
}

void CurlyEngine::Shutdown()
{
    SAFE_DELETE_ARRAY(GameShortName);

    const unsigned int NumSubsystems = Subsystems.size();
    for (unsigned int j = 0; j < NumSubsystems; ++j)
    {
        SAFE_SHUTDOWN(Subsystems[j]);
    }
    Subsystems.~vector();

    // Delete all loaded resourcesn
    if (ResourceManager != NULL)
    {
        ResourceManager->Purge();
        SAFE_DELETE(ResourceManager);
    }

    if (HGEEngine != NULL)
    {
        // Restore video mode and free all allocated resources.
        GetHGE().System_Shutdown();

        // If there are no more references, the HGE object will be deleted.
        HGEEngine->Release();
        HGEEngine = NULL;
    }
}

void CurlyEngine::Startup()
{
    if (HGEEngine != NULL)
    {
        if (bIsHGEInitialized)
        {
            GetHGE().System_Start();

            // NOTE: Do not add any code after System_Start(). All other code must be handled by the HGE callbacks (Tick, Render, etc)
        }
        else
        {
            // If HGE initialization failed show error message
            MessageBox(NULL, GetHGE().System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
        }
    }
}

bool CurlyEngine::Tick()
{
    if (!IsExiting())
    {
        float DeltaTime = GetHGE().Timer_GetDelta();

        if (!bTickedOnce)
        {
            bTickedOnce = true;
            OnFirstTick(DeltaTime);
        }

        for (unsigned int i = 0; i < Subsystems.size(); ++i)
        {
            Subsystems[i]->Tick(DeltaTime);
        }
    }

    return IsExiting();
}

void CurlyEngine::Render()
{
    const int NumSubsystem = Subsystems.size();
    for (int i = 0; i < NumSubsystem; ++i)
    {
        Subsystems[i]->Render();
    }
}

void CurlyEngine::OnFocusGained()
{
    const int NumSubsystem = Subsystems.size();
    for (int i = 0; i < NumSubsystem; ++i)
    {
        Subsystems[i]->OnAppFocusGained();
    }
}

void CurlyEngine::OnFocusLost()
{
    const int NumSubsystem = Subsystems.size();
    for (int i = 0; i < NumSubsystem; ++i)
    {
        Subsystems[i]->OnAppFocusLost();
    }
}

void CurlyEngine::ImportEngineConfig()
{
    HGE& HGERef = GetHGE();
    HGERef.System_SetState(HGE_INIFILE, "config/CurlyEngine.ini");

    ScreenWidth = HGERef.Ini_GetInt("DisplayOptions", "ScreenWidth", ScreenWidth);
    ScreenHeight = HGERef.Ini_GetInt("DisplayOptions", "ScreenHeight", ScreenHeight);
    int ColorDepth = HGERef.Ini_GetInt("DisplayOptions", "ColorDepth", 32);
    int FullscreenMode = HGERef.Ini_GetInt("DisplayOptions", "FullscreenMode", 0);

    HGERef.System_SetState(HGE_SCREENWIDTH, ScreenWidth);
    HGERef.System_SetState(HGE_SCREENHEIGHT, ScreenHeight);
    HGERef.System_SetState(HGE_SCREENBPP, ColorDepth);

    if (!FullscreenMode)
    {
        HGERef.System_SetState(HGE_WINDOWED, true);
    }
}

void CurlyEngine::OnFirstTick(float DeltaTime)
{
    const int NumSubsystem = Subsystems.size();
    for (int i = 0; i < NumSubsystem; ++i)
    {
        Subsystems[i]->OnFirstEngineTick();
    }
}

HGE& CurlyEngine::GetHGE() const
{
    CurlyAssert(HGEEngine != NULL, "Trying to access HGE before it's been initialized");
    return *HGEEngine;
}

hgeResourceManager* CurlyEngine::GetResourceManager() const
{
    return ResourceManager;
}

bool CurlyEngine::IsInitialized() const
{
    return (HGEEngine != NULL && bIsHGEInitialized && ResourceManager != NULL);
}

bool CurlyEngine::IsExiting() const
{
    return bExitApplication;
}

void CurlyEngine::ExitApplication()
{
    bExitApplication = true;
}

bool CurlyEngine::AddEngineSubsystem(EngineSubsystem& Subsystem)
{
    bool bAlreadyTracked = false;
    bool bAdded = false;

    const int NumSubsystems = Subsystems.size();
    for (int i = 0; i < NumSubsystems; ++i)
    {
        if (Subsystems[i] == &Subsystem)
        {
            bAlreadyTracked = true;
            break;
        }
    }

    if (!bAlreadyTracked)
    {
        if (!Subsystem.IsInitialized())
        {
            Subsystem.Initialize();
        }

        Subsystems.push_back(&Subsystem);
        bAdded = true;
    }

    return bAdded;
}

// EOF
