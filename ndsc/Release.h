#pragma once

#include <string>

class Release
{
public:
	Release(void);
	virtual ~Release(void);

	std::wstring mName;
	std::wstring mRegion;
};
