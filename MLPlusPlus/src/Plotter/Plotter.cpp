#include "Plotter.h"

#include <algorithm>
#include <Algorithms/LinearRegression.h>
#include <implot/implot.h>

double max(std::vector<double>& x)
{
	double max = x[0];
	for (auto e : x)
		if (max < e)
			max = e;
	return max;
}

double min(std::vector<double>& x)
{
	double min = x[0];
	for (auto e : x)
		if (min > e)
			min = e;
	return min;
}

Plotter::Plotter(LinearRegression* lr, std::vector<double> x, std::vector<double> y)
	:x(x), y(y)
{
	this->lr = new LinearRegression(*lr);

	x_p[0] = min(x) - 10.0;
	x_p[1] = max(x) + 10.0;
	y_p[0] = lr->getY(x_p[0]);
	y_p[1] = lr->getY(x_p[1]);

	isOpen = true;
}

Plotter::~Plotter()
{
	delete lr;
}

void Plotter::plot()
{
	ImGui::Begin("Graph", &Plotter::isOpen);
	
	if (ImPlot::BeginPlot("Graph"));
	{
		ImPlot::PlotScatter("Scatter Plot", x.data(), y.data(), static_cast<int>(x.size()));
		ImPlot::PlotLine("Line", x_p, y_p, 2);
		ImPlot::EndPlot();
	}
	ImGui::End();
}
