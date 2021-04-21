#include <stdio.h>
#include <rapidcsv.h>
#include <vector>

int main()
{
	rapidcsv::Document doc("dataset/train.csv");
	std::vector<float>& x_col = doc.GetColumn<float>("x");
	std::vector<float>& y_col = doc.GetColumn<float>("y");

	for (int i = 0; i < x_col.size() && i < y_col.size(); ++i)
	{
		printf("%f\t%f\n", x_col[i], y_col[i]);
	}
	return 0;
}