#pragma once

#include <vector>

class LinearRegression
{
private:
	double learningRate;
	unsigned int epoch;
	double m, c;
public:
	LinearRegression(double learningRate, unsigned int epoch);
	void train(std::vector<double>& x, std::vector<double>& y);
	std::vector<double> predict(const std::vector<double>& x) const;
};