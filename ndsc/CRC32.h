#pragma once

#include <string>

class CRC32
{
public:
	CRC32(void);
	~CRC32(void);

	int Test(int argc, char *argv[]);
	int FromFile(const std::string &filename, unsigned long &crc, unsigned long &size);

	static unsigned long CRC32::POLY[];
};
