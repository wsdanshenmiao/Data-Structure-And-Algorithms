#pragma once
#ifndef __QUICKFIND__H__
#define __QUICKFIND__H__

#include "IUnionFind.h"

namespace DSM {

	/// <summary>
	/// 查找很快速的并查集
	/// </summary>
	/// <typeparam name="N"></typeparam>
	class QuickFind : public IUnionFind
	{
	public:
		QuickFind() = default;
		QuickFind(const std::size_t& size) noexcept;

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


#endif // !__QUICKFIND__H__
