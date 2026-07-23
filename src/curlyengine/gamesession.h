#ifndef GameSession_H_
#define GameSession_H_

// ----------------------------------------------------------------------------
// GameSession - Macros
// ----------------------------------------------------------------------------

#define IMPLEMENT_SESSION_CREATOR(SessionClass) \
GameSession* CreateGameSession() \
{ \
	return new SessionClass(); \
}

// ----------------------------------------------------------------------------
// GameSession - Declaration
// ----------------------------------------------------------------------------

class GameSession
{
public:
    GameSession();
	virtual ~GameSession();

	// Override on derived classes to provide game-specific engine configuration
	virtual void PreInit() {}

	// Override on derived classes to provide game-specific startup operations
	virtual void LoadGame() {}

	// Override on derived classes to customize the engine output files and game title to your game name
	virtual char* GetGameName() const;
	virtual char* GetGameShortName() const;

	bool IsGamePaused() const   { return bPaused; }
	void Pause();

protected:
	class HGE* HGEEngine;

private:
	bool bPaused;
};


// ----------------------------------------------------------------------------
// GameSession - Inline Methods
// ----------------------------------------------------------------------------

inline char* GameSession::GetGameName() const
{
	return "Curly Engine";
}

inline char* GameSession::GetGameShortName() const
{
	return "Curly";
}


#endif
