#pragma once

#include <string>
#include <map>

#include "File.h"

class Folder
{
public:
	Folder(void);
	virtual ~Folder(void);

	int Populate();

	std::wstring m_path;
	std::map<std::wstring, File*> mFileList;
	std::map<std::wstring, Folder*> mFolderList;
};
