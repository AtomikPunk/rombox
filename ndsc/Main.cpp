#include "CRC32.h"
#include "DatParser.h"

#include <iostream>

int main(int argc, char *argv[])
{
	int result;

	//CRC32 crc;
	//result = crc.Test(argc,argv);

	if (argc < 2)
	{
		std::cout << "  Usage: " << argv[0] << " <filename> [filename] [filename] ..." << std::endl;
		return 0;
	}

	unsigned long crc;
	unsigned long size;
	for (int i = 1; i < argc; ++i)
	{
		DatParser parser;
		RomList romList;
		parser.FromFile(argv[i], romList);
	}

	return 0;
}