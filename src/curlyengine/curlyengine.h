#ifndef CurlyEngine_H_
#define CurlyEngine_H_

#ifndef _VECTOR_
#include <vector>
#endif


enum EResourceGroup
{
    RG_None = 0,
    RG_AlwaysLoaded = 1,
};


class CurlyEngine
{
public:
    static inline CurlyEngine& Instance()
    {
        static CurlyEngine Instance;
        return Instance;
    }
    ~CurlyEngine();

    void Initialize(char* InGameName, char* InGameShortName);
    void Startup();
    void Shutdown();

    bool Tick();


    // --------------------------------------------------------
    //	Rendering Methods

    void Render();
    // Returns true if the object was added to the render queue; false, otherwise.
    bool AddToRenderQueue(class IRenderable& RenderableObject);

    void OnFocusGained();
    void OnFocusLost();

    bool IsInitialized() const;

    bool IsExiting() const;
    void ExitApplication();

    const char* GetGameName() const { return GameName; }
    const char* GetGameShortName() const { return GameShortName; }
    int GetScreenWidth() const { return ScreenWidth; }
    int GetScreenHeight() const { return ScreenHeight; }

    bool AddEngineSubsystem(class EngineSubsystem& Subsystem);

    class HGE& GetHGE() const;
    class hgeResourceManager* GetResourceManager() const;

private:

    void ImportEngineConfig();

    void OnFirstTick(float DeltaTime);

    // Prevent the functions from getting called since this is a singleton
    CurlyEngine();
    CurlyEngine(const CurlyEngine&);
    CurlyEngine& operator=(const CurlyEngine&);

    class HGE* HGEEngine;
    class hgeResourceManager* ResourceManager;

    std::vector<class IRenderable*> RenderQueue;
    std::vector<class EngineSubsystem*> Subsystems;

    // Tick
    bool bTickedOnce;

    // Engine states
    bool bIsHGEInitialized;
    bool bExitApplication;

    // Engine configuration
    char* GameName;
    char* GameShortName;
    int ScreenWidth;
    int ScreenHeight;
};


#endif
