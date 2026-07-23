#ifndef EngineSubsystem_H_
#define EngineSubsystem_H_


// ----------------------------------------------------------------------------
// EngineSubsystem - Defines
// ----------------------------------------------------------------------------

#define DECLARE_SUBSYSTEM(ClassName) \
private: \
	ClassName() {} \
	~ClassName() {} \
	ClassName(const ClassName&); \
	ClassName& operator=(const ClassName&); \
public: \
	static ClassName& Instance() { static ClassName SubInstance; return SubInstance; }

#define IMPLEMENT_GAME_SUBSYSTEM_CREATOR(SubsystemClass) \
EngineSubsystem& GetGameSubsystem() \
{ \
	return SubsystemClass::Instance(); \
}

// ----------------------------------------------------------------------------
// EngineSubsystem - Declaration
// ----------------------------------------------------------------------------

class EngineSubsystem
{
public:
	EngineSubsystem();
	virtual ~EngineSubsystem();

	virtual void InitializeGameEngine() {}
	void Initialize();
	void Shutdown();

	bool IsInitialized() const;

	bool HasTicked() const;
	virtual void OnFirstEngineTick();
	virtual void Tick(float DeltaTime) {}
    virtual void Render() {}

	virtual void OnAppFocusGained() {}
	virtual void OnAppFocusLost() {}

	virtual void AddObjectsToRenderQueue() {}

protected:
	virtual void InitializeInternal() {}
	virtual void ShutdownInternal() {}
	virtual void FirstEngineTickInternal() {}

private:
	bool bIsInitialized;
	bool bTickedOnce;
};


// ----------------------------------------------------------------------------
// EngineSubsystem - Inline methods
// ----------------------------------------------------------------------------

inline bool EngineSubsystem::HasTicked() const
{
	return bTickedOnce;
}

inline bool EngineSubsystem::IsInitialized() const
{
	return bIsInitialized;
}

#endif

// EOF
