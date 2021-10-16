#pragma once

#include <string>

class String {
public:
	std::string data;

	String();
	String(const std::string& data);
	~String() = default;
};