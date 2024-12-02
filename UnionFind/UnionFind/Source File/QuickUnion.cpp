#include "QuickUnion.h"

namespace DSM {
	QuickUnion::QuickUnion(const std::size_t& size) noexcept
		:m_Count(size) {
		m_Id.reserve(size);
		for (std::size_t i = 0; i < size; ++i) {
			m_Id.emplace_back(i);
		}
	}

	void QuickUnion::Union(const std::size_t& p, const std::size_t& q) noexcept
	{
		auto idP = Find(p);
		auto idQ = Find(q);
		m_Id[idP] = idQ;	// 将树的首节点连接到另一个树的首节点上
		--m_Count;
	}

	bool QuickUnion::Connected(const std::size_t& p, const std::size_t& q) noexcept
	{
		return Find(p) == Find(q);
	}

	std::size_t QuickUnion::Find(const std::size_t& p) noexcept
	{
		std::size_t ret = p;
		for (; ret != m_Id[ret]; ret = m_Id[ret]);
		return ret;
	}

	std::size_t QuickUnion::SetsCount() const noexcept
	{
		return m_Count;
	}

	void QuickUnion::Reset(const std::size_t& size) noexcept
	{
		m_Count = size;
		m_Id.resize(size);
		for (std::size_t i = 0; i < size; ++i) {
			m_Id[i] = i;
		}
	}


}