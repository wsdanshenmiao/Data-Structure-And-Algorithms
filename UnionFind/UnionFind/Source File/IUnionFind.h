#pragma once
#ifndef __IUNIONFIND__H__
#define __IUNIONFIND__H__

#include <vector>

namespace DSM {
	class IUnionFind
	{
	public:
		virtual void Union(const std::size_t& p, const std::size_t& q) noexcept {};
		virtual bool Connected(const std::size_t& p, const std::size_t& q) const noexcept { return false; };
		virtual std::size_t Find(const std::size_t& p) const noexcept { return 0; };
		virtual std::size_t SetsCount() const noexcept { return 0; };
	};
}

#endif // !__IUNIONFIND__H__
