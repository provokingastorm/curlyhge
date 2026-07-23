#ifndef IRenderable_H_
#define IRenderable_H_

class IRenderable
{
public:
	virtual ~IRenderable() {}

	virtual void Render(class HGE& Engine) = 0;
	virtual void Tick(float DeltaTime) = 0;
	virtual void OnStart() = 0;
	virtual void OnStop() = 0;
	virtual void OnPause() = 0;
	virtual void SetHotSpot(float X, float Y) = 0;
};

#endif