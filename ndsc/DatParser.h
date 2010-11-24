#pragma once

#include "GameList.h"

#include <Markup.h>

#include <string>
#include <map>

class DatParser
{
public:
	DatParser(void);
	virtual ~DatParser(void);

	int FromFile(const std::wstring &filename);

	int ParseGame(Game *outGame);
	int ParseRelease(Release *outRelease);
	int ParseRom(Rom *outRom);

	const Rom *FindCRC(unsigned long inCRC);

protected:
	CMarkup markup;
	GameList mGameList;
	std::map<unsigned long, Rom*> mCRCList;
};
