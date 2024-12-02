#pragma once
#ifndef __QUICKUNION__H__
#define __QUICKUNION__H__

#include "IUnionFind.h"

namespace DSM {

	class QuickUnion : public IUnionFind
	{
	public:
		QuickUnion() = default;
		QuickUnion(const std::size_t& size) noexcept;

		void Union(const std::size_t& p, const std::size_t& q) noexcept override;
		bool Connected(const std::size_t& p, const std::size_t& q) noexcept override;
		std::size_t Find(const std::size_t& p) noexcept override;
		std::size_t SetsCount() const noexcept override;
		void Reset(const std::size_t& size) noexcept override;

	private:
		std::vector<std::size_t> m_Id;
		std::size_t m_Count = 0;
	};

}

#endif // !__QUICKUNION__H__
