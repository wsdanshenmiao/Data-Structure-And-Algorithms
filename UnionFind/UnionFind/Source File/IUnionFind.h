#pragma once
#ifndef __IUNIONFIND__H__
#define __IUNIONFIND__H__

#include <vector>
#include <memory>

namespace DSM {
	class IUnionFind
	{
	public:
		virtual void Union(const std::size_t& p, const std::size_t& q) noexcept = 0;
		virtual bool Connected(const std::size_t& p, const std::size_t& q) noexcept = 0;
		virtual std::size_t Find(const std::size_t& p) noexcept = 0;
		virtual std::size_t SetsCount() const noexcept = 0;
		virtual void Reset(const std::size_t& size) noexcept = 0;
	};
}

#endif // !__IUNIONFIND__H__
