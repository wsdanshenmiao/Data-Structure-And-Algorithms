#include "WeightedQuickUnion.h"

namespace DSM {

	WeightedQuickUnion::WeightedQuickUnion(std::size_t size) noexcept
		:m_Count(size) {
		m_Id.reserve(size);
		m_Depth.resize(size, 1);
		for (std::size_t i = 0; i < size; ++i) {
			m_Id.emplace_back(i);
		}
	}

	void WeightedQuickUnion::Union(const std::size_t& p, const std::size_t& q) noexcept
	{
		auto idp = Find(p), idq = Find(q);
		if (idp == idq)return;	// 已经联通
		if (m_Depth[idp] > m_Depth[idq]) {	//  p所在树的深度更深
			m_Id[idq] = idp;	// 让q树成为p的子树
			m_Depth[idp] += m_Depth[idq];
		}
		else {
			m_Id[idp] = idq;
			m_Depth[idq] += m_Depth[idp];
		}
	}

	bool WeightedQuickUnion::Connected(const std::size_t& p, const std::size_t& q) noexcept
	{
		return Find(p) == Find(q);
	}

	std::size_t WeightedQuickUnion::Find(const std::size_t& p) noexcept
	{
		std::size_t ret = p;
		for (; ret != m_Id[ret]; m_Id[ret] = m_Id[m_Id[ret]], ret = m_Id[ret]);
		return ret;
	}

	std::size_t WeightedQuickUnion::SetsCount() const noexcept
	{
		return m_Count;
	}

	void WeightedQuickUnion::Reset(const std::size_t& size) noexcept
	{
		m_Count = size;
		m_Id.resize(size);
		m_Depth.resize(size);
		for (std::size_t i = 0; i < size; ++i) {
			m_Id[i] = i;
			m_Depth[i] = 1;
		}
	}


}
