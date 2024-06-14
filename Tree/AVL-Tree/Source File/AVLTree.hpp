#ifndef __AVLTREE__HPP__
#define __AVLTREE__HPP__

#include "allocator.hpp"
#include "Tree.hpp"

namespace DSM {

// Ê÷
template <typename Keytype, typename Compare = std::less<Keytype>>
class AVLTree
{
public:
	using TreeNode = TreeNode<Keytype>;

	AVLTree();
	~AVLTree();

private:
	TreeNode* m_Head;
	size_t m_Size;
};

template <typename K, typename C>
AVLTree<K, C>::AVLTree()
{
	DSM::allocator<TreeNode> nAllocate;
	m_Head = nAllocate.allocate(1);
	m_Head->m_Parent = nullptr;
	m_Head->m_Left = nullptr;
	m_Head->m_Right = nullptr;
	m_Size = 0;
}

template <typename K, typename C>
AVLTree<K, C>::~AVLTree()
{

}



}

#endif // !__AVLTREE__HPP__
