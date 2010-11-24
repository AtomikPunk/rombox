#include "Game.h"

Game::Game(void)
{
}

Game::~Game(void)
{
	for (std::list<Release*>::iterator i = mReleases.begin(); i != mReleases.end(); ++i)
		delete *i;
	mReleases.clear();

	for (std::list<Rom*>::iterator i = mRoms.begin(); i != mRoms.end(); ++i)
		delete *i;
	mRoms.clear();
}
