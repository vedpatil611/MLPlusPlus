#pragma once

#include <rapidcsv.h>

class FileReader {
public:
	rapidcsv::Document doc;

	FileReader(const char* filePath);
	rapidcsv::Document* operator->();
};