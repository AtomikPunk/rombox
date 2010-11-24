#include "FolderZip.h"
#include "DatParser.h"

#include <direct.h>	//For _wgetcwd()

#include <iostream>
#include <iomanip>

int wmain(int argc, wchar_t *argv[])
{
	if (argc < 2)
	{
		std::cout << "  Usage: " << argv[0] << " <datfile> [filename] [filename] ..." << std::endl;
		return 0;
	}

	DatParser parser;
	parser.FromFile(argv[1]);

	for (int i = 2; i < argc; ++i)
	{
		std::wcout << L"Loading " << argv[i] << std::endl;
		FolderZip zipFile;
		zipFile.m_path = std::wstring(argv[i], argv[i]+wcslen(argv[i]));
		zipFile.Populate();

		std::map<std::wstring,File*>::const_iterator it;
		for (it = zipFile.mFileList.begin(); it != zipFile.mFileList.end(); ++it)
		{
			const Rom *rom = parser.FindCRC(it->second->m_crc);
			if (rom)
				if (rom->mStatus.empty())
					std::cout << "[good]";
				else
					std::wcout << L"[" << rom->mStatus << L"]";
			else
				std::cout << "[unknown]";
			std::cout << " " << std::hex << std::uppercase << it->second->m_crc << " : ";
			std::wcout << it->second->m_path;
			if (rom && rom->mGame)
				std::wcout << L" -> " << rom->mGame->mName;
			std::cout << std::endl;
		}
	}

	return 0;
}