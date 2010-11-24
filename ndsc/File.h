#pragma once

#include <string>

class File
{
public:
	File(void);
	virtual ~File(void);

	std::wstring m_path;
	unsigned long m_crc;
};
