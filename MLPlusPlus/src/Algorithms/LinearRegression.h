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
	inline double getY(double x) const { return m * x + c; }
	std::vector<double> predict(const std::vector<double>& x) const;
};