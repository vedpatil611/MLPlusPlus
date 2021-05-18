#pragma once

#include <vector>

class Plotter
{
private:
	class LinearRegression* lr;
	std::vector<double> x;
	std::vector<double> y;
	
	inline static bool isOpen = false;
	double x_p[2];
	double y_p[2];
public:
	Plotter(LinearRegression* lr, std::vector<double> x, std::vector<double> y);
	~Plotter();

	void plot();
};
