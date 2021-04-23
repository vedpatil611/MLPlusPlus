#pragma once

#include <vector>

namespace Utils
{
	template<typename T>
	double Sum(std::vector<T>& v)
	{
		double sum = 0.0f;
		for (auto i : v)
			sum += i;
		return sum;
	}

	template<typename T>
	std::vector<T> Diff(std::vector<T>& f, std::vector<T>& s)
	{
		std::vector<T> diff;
		diff.resize(f.size());
		for (int i = 0; i < f.size(); ++i)
			diff[i] = f[i] - s[i];
		return diff;
	}

	template<typename T>
	std::vector<T> Mult(std::vector<T>& f, std::vector<T>& s)
	{
		std::vector<T> mult;
		mult.resize(f.size());
		for (int i = 0; i < f.size(); ++i)
			mult[i] = f[i] * s[i];
		return mult;
	}
}