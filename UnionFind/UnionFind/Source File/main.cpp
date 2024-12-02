#include <iostream>
#include "PercolationStats.h"
#include "Timer.h"
#include "QuickFind.h"
#include "QuickUnion.h"
#include "WeightedQuickUnion.h"

using namespace DSM;

template<std::size_t N>
void TestPercolationStats(const std::size_t& size, std::unique_ptr<IUnionFind> uf)
{
	Timer timer;
	PercolationStats<double, N> ps(size, std::move(uf));
	timer.Stop();
	std::cout << "Mean: " << ps.Mean() << std::endl;
	std::cout << "Stddev: " << ps.Stddev() << std::endl;
	std::cout << "95% confidence interval: [" << ps.ConfidenceLo() <<
		',' << ps.ConfidenceHi() << ']' << std::endl;
}


int main()
{
	//TestPercolationStats<100>(100, std::make_unique<QuickFind>());
	//TestPercolationStats<100>(100, std::make_unique<QuickUnion>());
	TestPercolationStats<10000>(20, std::make_unique<WeightedQuickUnion>());
	//decltype(auto) uf = std::make_unique<QuickFind>(100);
	//std::cout << typeid(*uf).name();
}