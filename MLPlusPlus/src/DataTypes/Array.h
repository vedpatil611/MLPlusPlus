#pragma once

#include <vector>

class Array {
public:
	std::vector<double> data;

	Array() = default;
	Array(const std::vector<double>& data);
	~Array() = default;
};