#pragma once

#include "Release.h"
#include "Rom.h"

#include <string>
#include <list>

class Game
{
public:
	Game(void);
	virtual ~Game(void);

	std::wstring mName;
	std::list<Release*> mReleases;
	std::list<Rom*> mRoms;
};
