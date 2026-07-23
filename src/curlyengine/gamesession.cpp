#include "gamesession.h"
#include "hge.h"


GameSession::GameSession()
	: HGEEngine(NULL)
	, bPaused(false)
{
	if(HGEEngine == NULL)
	{
		HGEEngine = hgeCreate(HGE_VERSION);
	}
}

GameSession::~GameSession()
{
	if(HGEEngine != NULL)
	{
		HGEEngine->Release();
		HGEEngine = NULL;
	}
}

void GameSession::Pause()
{
	bPaused = true;
}
