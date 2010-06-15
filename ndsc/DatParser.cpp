#include "DatParser.h"

#include <iostream>

void DatParser::ParserData::ResetCurrent()
{
	mCurrentName = "";
	mCurrentString = "";
	mCurrentAttributes.clear();
}

DatParser::DatParser(void)
{
	memset(&mSAXHandler, 0, sizeof(xmlSAXHandler));

	mSAXHandler.startDocument = (startDocumentSAXFunc)&DatParser::OnStartDocument;
	mSAXHandler.startElement = (startElementSAXFunc)&DatParser::OnStartElement;
	mSAXHandler.endElement = (endElementSAXFunc)&DatParser::OnEndElement;

	mParserData.mState = ParserData::UNKNOWN;
}

DatParser::~DatParser(void)
{
}

int DatParser::FromFile(const std::string &filename, RomList &outRomList)
{
	//xmlDocPtr doc;
	//xmlNodePtr node;
	//doc = xmlReadFile(filename.c_str(), NULL, XML_PARSE_DTDVALID);

	//if (!doc)
	//	return -1;

	//node = xmlDocGetRootElement(doc);
	//if (!node)
	//{
	//	xmlFreeDoc(doc);
	//	return -2;
	//}

	//std::cout << "Loaded " << filename << std::endl;
	//std::cout << "  Root: " << node->name << std::endl;

	//xmlFreeDoc(doc);

	xmlSAXUserParseFile(&mSAXHandler, &mParserData, filename.c_str());

	return 0;
}

void DatParser::OnStartDocument(void *inoutData)
{
	ParserData *data((ParserData*)inoutData);
	if (!data)
		return;

	data->mState = ParserData::START;
}

void DatParser::OnStartElement(void *inoutData, const xmlChar *name, const xmlChar **attr)
{
	ParserData *data((ParserData*)inoutData);
	if (!data)
		return;

	switch (data->mState)
	{
		case ParserData::START:
			if (xmlStrcmp(name, BAD_CAST"game") == 0)
			{
				data->mState = ParserData::INSIDE_GAME;
			}
			else if (xmlStrcmp(name, BAD_CAST"header") == 0)
			{
				data->mState = ParserData::INSIDE_HEADER;
			}

			break;

		case ParserData::UNKNOWN:
			data->mUnknownDepth++;
			break;

		default:
			break;
	}
}

void DatParser::OnCharacters(void *inoutData, const xmlChar *ch, int len)
{
}

void DatParser::OnEndElement(void *inoutData, const xmlChar *ch)
{
	ParserData *data((ParserData*)inoutData);
	if (!data)
		return;

	switch (data->mState)
	{
		case ParserData::UNKNOWN:
			if (--data->mUnknownDepth <= 0)
				data->mState = data->mPreviousState;
			break;

		default:
			break;
	}
}

void DatParser::OnEndDocument(void *inoutData)
{
}
