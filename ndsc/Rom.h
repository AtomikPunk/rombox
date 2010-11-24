#pragma once

#include <string>

class Game;

class Rom
{
public:
	Rom(void);
	virtual ~Rom(void);

	std::wstring mName;
	unsigned long mCRC;
	std::wstring mStatus;
	Game *mGame;
};
