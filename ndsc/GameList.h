#pragma once

#include "Game.h"

#include <set>

class GameList
{
public:
	GameList(void);
	virtual ~GameList(void);

	void Clear();

	std::set<Game*> mGames;
};
