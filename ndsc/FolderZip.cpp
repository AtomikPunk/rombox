#include "FolderZip.h"

#define ZLIB_WINAPI
#include "unzip.h"
#pragma comment(lib,"zlibwapi.lib")

FolderZip::FolderZip(void)
{
}

FolderZip::~FolderZip(void)
{
}

int FolderZip::Populate()
{
	std::string filename(m_path.begin(), m_path.end());
	unzFile f = unzOpen64(filename.c_str());
	// Support for unicode filename is not yet implemented in unzip(?)
	//unzFile f = unzOpen64(m_path.c_str());
	if (!f)
		return -1;

	unz_global_info64 globalInfo;
	int getGlobalInfoResult = unzGetGlobalInfo64(f, &globalInfo);
	if (getGlobalInfoResult != UNZ_OK)
	{
		unzClose(f);
		return -2;
	}

	int firstFileResult = unzGoToFirstFile(f);
	if (firstFileResult != UNZ_OK)
	{
		unzClose(f);
		return -3;
	}

	int nextFileResult = firstFileResult;
	do
	{
		unz_file_info64 fileInfo;
		int getInfoResult = unzGetCurrentFileInfo64(f, &fileInfo, NULL, 0, NULL, 0, NULL, 0);
		if (getInfoResult != UNZ_OK)
		{
			unzClose(f);
			continue;
		}

		char *filename = new char[fileInfo.size_filename+1];
		unzGetCurrentFileInfo64(f, &fileInfo, filename, fileInfo.size_filename, NULL, 0, NULL, 0);
		filename[fileInfo.size_filename] = '\0';

		File *newFile = new File();
		newFile->m_path = std::wstring(filename, filename+fileInfo.size_filename);
		newFile->m_crc = fileInfo.crc;
		mFileList.insert(std::pair<std::wstring,File*>(newFile->m_path, newFile));

		nextFileResult = unzGoToNextFile(f);
	} while (nextFileResult == UNZ_OK);

	unzClose(f);

	return 0;
}