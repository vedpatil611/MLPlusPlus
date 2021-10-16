#pragma once

#include <rapidcsv.h>

class FileReader {
public:
	rapidcsv::Document data;

	FileReader(const char* filePath);
	rapidcsv::Document* operator->();

	template<typename T>
	std::vector<T> getColumn(const char* columnName) const;
};

template<typename T>
inline std::vector<T> FileReader::getColumn(const char* columnName) const
{
	return data.GetColumn<T>(columnName);
}
