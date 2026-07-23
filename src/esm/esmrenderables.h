#ifndef ESMRenderables_H_
#define ESMRenderables_H_

#ifndef IRenderable_H_
#include "irenderable.h"
#endif

#ifndef Vector2D_H_
#include "vector2d.h"
#endif

class ESMNet : public IRenderable
{
public:
    ESMNet();
    ~ESMNet();

    void Tick(float DeltaTime);
    void Render(class HGE& Engine);
    void SetHotSpot(float X, float Y);
    void OnStart();
    void OnStop();
    void OnPause();

private:

    Vector2D HotSpot;
};

class ESMFloor : public IRenderable
{
public:
    ESMFloor();
    ~ESMFloor();

    void Tick(float DeltaTime);
    void Render(class HGE& Engine);
    void SetHotSpot(float X, float Y);
    void OnStart();
    void OnStop();
    void OnPause();

private:

    Vector2D HotSpot;
};

#endif

// EOF
