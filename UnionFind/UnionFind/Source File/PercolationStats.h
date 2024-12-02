#pragma once
#ifndef __PERCOLATIONSTATS__H__
#define __PERCOLATIONSTATS__H__

#include <array>
#include <random>
#include <type_traits>
#include "Percolation.h"

namespace DSM {

	template<typename T = double, std::size_t N = 10>
	class PercolationStats {
	public:
		// perform independent trials on an n-by-n grid
		PercolationStats(
			const std::size_t& n,
			std::unique_ptr<IUnionFind> pUF);

		// sample mean of percolation threshold
		T Mean() const noexcept;

		// sample standard deviation of percolation threshold
		T Stddev() const noexcept;

		// low endpoint of 95% confidence interval
		T ConfidenceLo() const noexcept;

		// high endpoint of 95% confidence interval
		T ConfidenceHi() const noexcept;

	private:
		std::array<T, N> m_Result;
	};


	template<typename T, std::size_t N>
	inline PercolationStats<T, N>::PercolationStats(
		const std::size_t& n,
		std::unique_ptr<IUnionFind> pUF)
	{
		if (n == 0) throw std::out_of_range("n should more than 0");
		std::random_device rd;
		std::mt19937 gen(rd());
		// 指定随机数的类型和范围
		Percolation p(n, std::move(pUF));
		std::uniform_int_distribution<size_t> dis(0, n - 1);
		for (std::size_t i = 0; i < N; ++i) {
			while (!p.Percolates()) {
				p.Open(dis(gen), dis(gen));
			}
			m_Result[i] = static_cast<T>(p.NumberOfOpenSites()) / (n * n);
			p.Reset(n);
		}
	}

	template<typename T, std::size_t N>
	inline T PercolationStats<T, N>::Mean() const noexcept
	{
		T ret{ 0 };
		for (const auto& result : m_Result) {
			ret += result;
		}
		return ret / m_Result.size();
	}

	template<typename T, std::size_t N>
	inline T PercolationStats<T, N>::Stddev() const noexcept
	{
		T avg = Mean();
		T sum = { 0 };
		for (std::size_t i = 0; i < m_Result.size(); i++) {
			sum += (m_Result[i] - avg) * (m_Result[i] - avg);
		}
		return sum / (m_Result.size() - 1);
	}

	template<typename T, std::size_t N>
	inline T PercolationStats<T, N>::ConfidenceLo() const noexcept
	{
		return Mean() - Stddev();
	}

	template<typename T, std::size_t N>
	inline T PercolationStats<T, N>::ConfidenceHi() const noexcept
	{
		return Mean() + Stddev();
	}

}

#endif // !__PERCOLATIONSTATS__H__
