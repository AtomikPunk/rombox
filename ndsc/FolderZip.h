#pragma once
#include "folder.h"

class FolderZip :
	public Folder
{
public:
	FolderZip(void);
	virtual ~FolderZip(void);

	int FolderZip::Populate();
};
