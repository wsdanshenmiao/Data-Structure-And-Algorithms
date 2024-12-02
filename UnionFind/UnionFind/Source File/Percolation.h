#pragma once
#ifndef __PERCOLATION__H__
#define __PERCOLATION__H__

#include <vector>
#include <memory>
#include "IUnionFind.h"

namespace DSM {
	class Percolation
	{
	public:
		// creates n-by-n m_Grid, with all sites initially blocked
		Percolation(const std::size_t& count, std::unique_ptr<IUnionFind> uf) noexcept;

		// opens the site (row, col) if it is not open already
		void Open(const std::size_t& row, const std::size_t& col) noexcept;

		// is the site (row, col) open?
		bool IsOpen(const std::size_t& row, const std::size_t& col) const noexcept;

		// is the site (row, col) full?
		// 当当前点与第一行某一点联通时当前点是满的
		bool IsFull(const std::size_t& row, const std::size_t& col)const noexcept;

		// returns the number of open sites
		std::size_t NumberOfOpenSites() const noexcept;

		// does the system percolate?
		// 当第一行某一点与最后一行某一点联通时渗透
		bool Percolates() const noexcept;

		void Reset(const std::size_t& count) noexcept;

		bool OutOfRange(
			const std::size_t& row,
			const std::size_t& col,
			const std::size_t& min,
			const std::size_t& max) const noexcept;

	private:
		void Init(const std::size_t& count) noexcept;

	private:
		std::vector<bool> m_Grid;
		std::unique_ptr<IUnionFind> m_UF;
		std::size_t m_Count;
	};


}

#endif // !__PERCOLATION__H__
