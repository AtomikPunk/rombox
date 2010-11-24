#include "DatParser.h"

#include <sstream>
#include <iostream>

DatParser::DatParser(void)
{
}

DatParser::~DatParser(void)
{
}

int DatParser::FromFile(const std::wstring &filename)
{
	if (!markup.Load(filename))
		return -1;

	if (!markup.FindElem(L"datafile"))
		return -2;

	mGameList.Clear();

	markup.IntoElem();
	while (markup.FindElem(L"game"))
	{
		Game *game = new Game();

		ParseGame(game);

		mGameList.mGames.insert(game);
	}

	std::cout << "Loaded " << mGameList.mGames.size() << " games." << std::endl;

	return 0;
}

int DatParser::ParseGame(Game *outGame)
{
	outGame->mName = markup.GetAttrib(L"name");

	markup.IntoElem();

	while (markup.FindElem(L"release"))
	{
		Release *release = new Release();

		ParseRelease(release);

		release->mGame = outGame;
		outGame->mReleases.push_back(release);
	}

	while (markup.FindElem(L"rom"))
	{
		Rom *rom = new Rom();

		ParseRom(rom);

		rom->mGame = outGame;
		outGame->mRoms.push_back(rom);
	}

	markup.OutOfElem();

	return 0;
}

int DatParser::ParseRelease(Release *outRelease)
{
	outRelease->mName = markup.GetAttrib(L"name");
	outRelease->mRegion = markup.GetAttrib(L"region");

	return 0;
}

int DatParser::ParseRom(Rom *outRom)
{
	outRom->mName = markup.GetAttrib(L"name");
	std::wstringstream crc;
	crc.str(markup.GetAttrib(L"crc"));
	crc >> std::hex >> outRom->mCRC;
	outRom->mStatus = markup.GetAttrib(L"status");

	mCRCList[outRom->mCRC] = outRom;

	return 0;
}

const Rom *DatParser::FindCRC(unsigned long inCRC)
{
	std::map<unsigned long, Rom*>::const_iterator i;
	i = mCRCList.find(inCRC);
	if (i != mCRCList.end())
		return i->second;

	return NULL;
}
