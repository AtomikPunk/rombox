#include "Folder.h"

Folder::Folder(void)
{
}

Folder::~Folder(void)
{
	while (!mFileList.empty())
	{
		delete mFileList.begin()->second;
		mFileList.erase(mFileList.begin());
	}
}

int Folder::Populate()
{
	return 0;
}
