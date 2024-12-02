#pragma once
#ifndef __WEIGHTEDQUICKUNION__H__
#define __WEIGHTEDQUICKUNION__H__

#include "IUnionFind.h"

namespace DSM {

	class WeightedQuickUnion : public IUnionFind
	{
	public:
		WeightedQuickUnion() = default;
		WeightedQuickUnion(std::size_t size) noexcept;

		// 通过 IUnionFind 继承
		void Union(const std::size_t& p, const std::size_t& q) noexcept override;
		bool Connected(const std::size_t& p, const std::size_t& q) noexcept override;
		std::size_t Find(const std::size_t& p) noexcept override;
		std::size_t SetsCount() const noexcept override;
		void Reset(const std::size_t& size) noexcept override;

	private:
		std::vector<std::size_t> m_Depth;
		std::vector<std::size_t> m_Id;
		std::size_t m_Count;

	};
}

#endif // !__WEIGHTEDQUICKUNION__H__
