#include <iostream>
#include "QuickFind.h"
#include "PercolationStats.h"

using namespace DSM;

int main()
{
	PercolationStats<double, 10> ps(100, 10, std::make_unique<QuickFind>(100));
	std::cout << "Mean: " << ps.Mean();
	std::cout << "Stddev: " << ps.Stddev();
	std::cout << "95% confidence interval: " + '[' << ps.ConfidenceLo() +
		',' << ps.ConfidenceHi() + ']';
	//decltype(auto) uf = std::make_unique<QuickFind>(100);
	//std::cout << typeid(*uf).name();
}