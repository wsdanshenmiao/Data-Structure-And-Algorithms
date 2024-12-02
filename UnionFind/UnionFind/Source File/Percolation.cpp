#include "Percolation.h"

namespace DSM {

	Percolation::Percolation(const std::size_t& count, std::unique_ptr<IUnionFind> uf) noexcept
		:m_Count(count), m_UF(std::move(uf)) {
		Init(count);
	}

	void Percolation::Open(const std::size_t& row, const std::size_t& col) noexcept
	{
		if (OutOfRange(row, col, 0, m_Count - 1)) {
			return;
		}
		if (m_Grid[row * m_Count + col]) return;

		auto currPos = row * m_Count + col;
		if (row > 0 && m_Grid[currPos - m_Count])
			m_UF->Union(currPos, currPos - m_Count);    // Union up
		if (row < m_Count - 1 && m_Grid[currPos + m_Count])
			m_UF->Union(currPos, currPos + m_Count);   // Union down
		if (col > 0 && m_Grid[currPos - 1])
			m_UF->Union(currPos, currPos - 1);    // Union left
		if (col < m_Count - 1 && m_Grid[currPos + 1])
			m_UF->Union(currPos, currPos + 1);   // Union right

		m_Grid[currPos] = true;
	}

	bool Percolation::IsOpen(const std::size_t& row, const std::size_t& col) const noexcept
	{
		if (OutOfRange(row, col, 0, m_Count - 1)) {
			return false;
		}
		return m_Grid[row * m_Count + col];
	}

	bool Percolation::IsFull(const std::size_t& row, const std::size_t& col)const noexcept
	{
		if (OutOfRange(row, col, 0, m_Count - 1)) {
			return false;
		}
		auto currPos = row * m_Count + col;
		if (!m_Grid[currPos]) return false;
		if (m_UF->Find(m_Count * m_Count) == m_UF->Find(currPos)) {
			return true;
		}
		return false;
	}

	std::size_t Percolation::NumberOfOpenSites() const noexcept
	{
		std::size_t ret = 0;
		for (const auto& grid : m_Grid) {
			if (grid)
				++ret;
		}
		return ret;
	}

	bool Percolation::Percolates() const noexcept
	{
		auto powN = m_Count * m_Count;
		if (m_UF->Find(powN) == m_UF->Find(powN + 1))
			return true;
		return false;
	}

	void Percolation::Reset(const std::size_t& count) noexcept
	{
		Init(count);
	}

	bool Percolation::OutOfRange(
		const std::size_t& row,
		const std::size_t& col,
		const std::size_t& min,
		const std::size_t& max) const noexcept
	{
		return !(min <= row && row <= max && min <= col && col <= max);
	}
	void Percolation::Init(const std::size_t& count) noexcept
	{
		m_UF->Reset(count * count + 2);
		// init member
		m_Grid.clear();
		m_Grid.resize(count * count, false);
		// 创建两个虚拟节点
		// 将第一个虚拟节点和第一行链接
		for (std::size_t i = 0; i < count; ++i) {
			m_UF->Union(count * count, i);
		}
		std::size_t lastRow = count * (count - 1);
		// 第二个虚拟节点和最后一行链接
		for (std::size_t i = 0; i < count; ++i) {
			m_UF->Union(count * count + 1, lastRow + i);
		}
	}
}
