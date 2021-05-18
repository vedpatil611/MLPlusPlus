#include "File.h"

#ifdef OS_LINUX
#include <string.h>
#include <stdio.h>
#endif

#include <memory>

const char* Utils::readFile(const char* filepath)
{
    FILE* file = fopen(filepath, "r");
    fseek(file, 0, SEEK_END);
    unsigned long length = ftell(file);
    char* data = new char[length + 1];
    memset(data, 0, length + 1);
    fseek(file, 0, SEEK_SET);
    fread(data, 1, length, file);
    fclose(file);
    return data;
}
