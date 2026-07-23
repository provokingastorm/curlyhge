#ifndef SharedRenderables_H_
#define SharedRenderables_H_

#ifndef IRenderable_H_
#include "irenderable.h"
#endif

#ifndef Vector2D_H_
#include "vector2d.h"
#endif


// ----------------------------------------------------------------------------
// AnimatedCharacter - Declaration
// ----------------------------------------------------------------------------

class AnimatedCharacter : public IRenderable
{
public:
	AnimatedCharacter();
	~AnimatedCharacter();

	void AddAnimation(class hgeAnimation& InAnim);

	void Tick(float DeltaTime);
	void Render(class HGE& Engine);
	void SetHotSpot(float X, float Y);
	void OnStart();
	void OnStop();
	void OnPause();

private:
	class hgeAnimation* CurrentAnim;
	Vector2D HotSpot;
};


// ----------------------------------------------------------------------------
// StaticImage - Declaration
// ----------------------------------------------------------------------------

class StaticImage : public IRenderable
{
public:
	StaticImage();
	~StaticImage();

	void SetContent(class hgeSprite& InBackground);
	inline void SetRotation(float RotationInRadians);

	void Tick(float DeltaTime);
	void Render(class HGE& Engine);
	void SetHotSpot(float X, float Y);
	void OnStart();
	void OnStop();
	void OnPause();

private:

	class hgeSprite* Image;
	Vector2D HotSpot;
	float Rotation;
};


// ----------------------------------------------------------------------------
// RenderedQuad - Declaration
// ----------------------------------------------------------------------------

class RenderedQuad : public IRenderable
{
public:
    RenderedQuad();
    ~RenderedQuad();

    void SetContent(struct hgeQuad& InQuad);

    void Tick(float DeltaTime);
    void Render(class HGE& Engine);
    void SetHotSpot(float X, float Y);
    void OnStart();
    void OnStop();
    void OnPause();

private:

    struct hgeQuad* Quad;
    Vector2D HotSpot;
};

#endif

// EOF
