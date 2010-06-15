#pragma once

#include "RomList.h"

#include <libxml/parser.h>
#pragma comment(lib,"iconv.lib")
#pragma comment(lib,"libxml2.lib")

#include <string>
#include <map>

class DatParser
{
public:
	class ParserData
	{
	public:
		enum State {UNKNOWN = 0, START, FINISH, INSIDE_HEADER, INSIDE_GAME};

		State mState;
		State mPreviousState;
		int mUnknownDepth;
		std::string mCurrentName;
		std::multimap<std::string,std::string> mCurrentAttributes;
		std::string mCurrentString;

		void ResetCurrent();
	};

	DatParser(void);
	virtual ~DatParser(void);

	int FromFile(const std::string &filename, RomList &outRomList);

private:
	static void OnStartDocument(void *inoutData);
	static void OnStartElement(void *inoutData, const xmlChar *name, const xmlChar **attr);
	static void OnCharacters(void *inoutData, const xmlChar *ch, int len);
	static void OnEndElement(void *inoutData, const xmlChar *ch);
	static void OnEndDocument(void *inoutData);

protected:
	xmlSAXHandler mSAXHandler;
	ParserData mParserData;
};
