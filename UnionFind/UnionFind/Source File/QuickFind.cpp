#include "QuickFind.h"

namespace DSM {
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
	bool QuickFind::Connected(const std::size_t& p, const std::size_t& q) noexcept
	{

		return Find(p) == Find(q);
	}

	/// <summary>
	/// 查找p的所在集合的首元素
	/// </summary>
	/// <typeparam name="N"></typeparam>
	/// <param name="p"></param>	要查找的元素
	/// <returns></returns>			所在集合的首元素
	std::size_t QuickFind::Find(const std::size_t& p) noexcept
	{
		return m_Id[p];
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

	void QuickFind::Reset(const std::size_t& size) noexcept
	{
		m_Id.resize(size);
		for (std::size_t i = 0; i < m_Id.size(); ++i) {
			m_Id[i] = i;
		}
	}



}