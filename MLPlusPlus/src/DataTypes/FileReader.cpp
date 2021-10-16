#include "FileReader.h"

FileReader::FileReader(const char* filePath)
	:doc(rapidcsv::Document(filePath))
{

}

rapidcsv::Document* FileReader::operator->()
{
	return &doc;
}
