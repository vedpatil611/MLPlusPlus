#include "FileReader.h"

FileReader::FileReader(const char* filePath)
	:data(rapidcsv::Document(filePath))
{

}

rapidcsv::Document* FileReader::operator->()
{
	return &data;
}
