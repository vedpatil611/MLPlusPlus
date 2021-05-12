#include "LinearRegression.h"

#include <Utils/vecops.h>

LinearRegression::LinearRegression()
{
}

LinearRegression::LinearRegression(double learningRate, unsigned int epoch)
	:learningRate(learningRate), epoch(epoch) {}

void LinearRegression::train(std::vector<double>& x, std::vector<double>& y)
{
	double m = 1.0f;
	double c = 1.0f;
	double n = static_cast<double>(x.size());

	for (unsigned int i = 0; i < epoch; ++i)
	{
		std::vector<double> predications;
		predications.resize(n);
		for (int i = 0; i < n; ++i)
			predications[i] = m * x[i] + c;

		std::vector<double> diff = Utils::Diff(predications, y);
		std::vector<double> err = Utils::Mult(diff, x);

		c = c - (learningRate * Utils::Sum(diff) / n);
		m = m - (learningRate * Utils::Sum(err) / n);
	}

	this->m = m;
	this->c = c;
}

void LinearRegression::train(double learningRate, unsigned int iters, std::vector<double>& x, std::vector<double>& y)
{
	this->learningRate = learningRate;
	this->epoch = iters;

	double m = 1.0f;
	double c = 1.0f;
	double n = static_cast<double>(x.size());

	for (unsigned int i = 0; i < epoch; ++i)
	{
		std::vector<double> predications;
		predications.resize(n);
		for (int i = 0; i < n; ++i)
			predications[i] = m * x[i] + c;

		std::vector<double> diff = Utils::Diff(predications, y);
		std::vector<double> err = Utils::Mult(diff, x);

		c = c - (learningRate * Utils::Sum(diff) / n);
		m = m - (learningRate * Utils::Sum(err) / n);
	}

	this->m = m;
	this->c = c;
}

std::vector<double> LinearRegression::predict(const std::vector<double>& x) const
{
	std::vector<double> result;
	result.resize(x.size());
	for (int i = 0; i < x.size(); ++i)
	{
		result[i] = m * x[i] + c;
	}
	return result;
}
