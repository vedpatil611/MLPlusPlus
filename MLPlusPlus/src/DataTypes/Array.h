#pragma once

#include <vector>

class Array {
public:
	std::vector<float> data;

	Array() = default;
	Array(const std::vector<float>& data);
	~Array() = default;
};