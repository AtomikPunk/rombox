#include "GameList.h"

GameList::GameList(void)
{
}

GameList::~GameList(void)
{
	Clear();
}

void GameList::Clear()
{
	for (std::set<Game*>::iterator i = mGames.begin(); i != mGames.end(); ++i)
		delete *i;
	mGames.clear();
}
