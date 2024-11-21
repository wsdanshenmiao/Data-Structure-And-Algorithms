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
		QuickFind(const std::size_t& size) noexcept;

		void Union(const std::size_t& p, const std::size_t& q) noexcept override;
		bool Connected(const std::size_t& p, const std::size_t& q) const noexcept override;
		std::size_t Find(const std::size_t& p) const noexcept override;
		std::size_t SetsCount() const noexcept override;

	private:
		std::vector<std::size_t> m_Id;
		std::size_t m_Count;
	};


	QuickFind::QuickFind(const std::size_t& size) noexcept
		:m_Count(size) {
		m_Id.reserve(size);
		for (std::size_t i = 0; i < size; ++i) {
			m_Id.emplace_back(i);
		}
	}

	/// <summary>
	/// 联通两个元素
	/// </summary>
	/// <typeparam name="N"></typeparam>
	/// <param name="p"></param>
	/// <param name="q"></param>
	void QuickFind::Union(const std::size_t& p, const std::size_t& q) noexcept
	{
		auto idP = Find(p);
		auto idQ = Find(q);
		if (idP == idQ)return;
		for (auto& id : m_Id) {
			if (id == idP)
				id = idQ;
		}
		--m_Count;
	}

	/// <summary>
	/// 判断两个元素是否在一个集合中
	/// </summary>
	/// <typeparam name="N"></typeparam>
	/// <param name="p"></param>
	/// <param name="q"></param>
	/// <returns></returns>
	bool QuickFind::Connected(const std::size_t& p, const std::size_t& q) const noexcept
	{

		return Find(p) == Find(q);
	}

	/// <summary>
	/// 查找p的所在集合的首元素
	/// </summary>
	/// <typeparam name="N"></typeparam>
	/// <param name="p"></param>	要查找的元素
	/// <returns></returns>			所在集合的首元素
	std::size_t QuickFind::Find(const std::size_t& p) const noexcept
	{
		return p;
	}

	/// <summary>
	/// 当前联合的集合数量
	/// </summary>
	/// <typeparam name="N"></typeparam>
	/// <returns></returns>		集合数量
	std::size_t QuickFind::SetsCount() const noexcept
	{
		return m_Count;
	}

}


#endif // !__QUICKFIND__H__
