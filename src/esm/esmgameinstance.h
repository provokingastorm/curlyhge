#ifndef ESMGameInstance_H_
#define ESMGameInstance_H_

#include "hge.h"
#include "hgevector.h"

// ----------------------------------------------------------------------------
// ESMGameInstance - Declaration
// ----------------------------------------------------------------------------

class ESMGameInstance
{
public:
    ESMGameInstance() {};
    virtual ~ESMGameInstance() {};

    virtual void Initialize(const struct hgeQuad& PlayableArea) = 0;
    virtual void StartGame() = 0;
    virtual void StopGame() = 0;
    virtual void Tick(float DeltaTime) = 0;
    virtual bool IsRunning() = 0;

private:
};


// ----------------------------------------------------------------------------
// ESMVolleyballGameInstance - Declaration
// ----------------------------------------------------------------------------

class ESMVolleyballGameInstance : public ESMGameInstance
{
public:

    ESMVolleyballGameInstance();
    ~ESMVolleyballGameInstance();

    void Initialize(const struct hgeQuad& PlayableAreaQuad);
    void StartGame();
    void StopGame();
    void Tick(float DeltaTime);
    bool IsRunning();

private:

    hgeQuad FloorQuad;
    hgeQuad NetQuad;

    class RenderedQuad* FloorRenderable;
    class RenderedQuad* NetRenderable;

    class StaticImage* PlayerSlimeStaticImage;
    class hgeSprite* PlayerSlime;

    hgeVector PlayerSlimeLocation;
    hgeVector PlayerSlimeVelocity;

    HTEXTURE PlayerSlimeHandle;

    bool bIsRunning;
};

#endif

// EOF
