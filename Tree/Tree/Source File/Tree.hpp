#ifndef __TREE__HPP__
#define __TREE__HPP__

#include "allocator.hpp"
#include <utility>

namespace DSM {


/*****************************
Class Declaration
*****************************/

// 树的节点
template <typename KeyType>
struct TreeNode
{
	TreeNode* m_Parent;
	TreeNode* m_Left;
	TreeNode* m_Right;
	KeyType m_Key;

	TreeNode();
	TreeNode(const KeyType& key, TreeNode* parent = nullptr, TreeNode* left = nullptr, TreeNode* right = nullptr);
	TreeNode(KeyType&& key, TreeNode* parent = nullptr, TreeNode* left = nullptr, TreeNode* right = nullptr);
	TreeNode(const TreeNode& other) = default;
	TreeNode& operator=(const TreeNode& other) = default;
};

/*****************************
Class Definition
*****************************/

template <typename K>
TreeNode<K>::TreeNode()
	:m_Parent(nullptr), m_Left(nullptr), m_Right(nullptr) {}

template <typename K>
TreeNode<K>::TreeNode(const K& key, TreeNode* parent, TreeNode* left, TreeNode* right)
	: m_Key(key), m_Parent(parent), m_Left(left), m_Right(right) {}

template <typename K>
TreeNode<K>::TreeNode(K&& key, TreeNode* parent, TreeNode* left, TreeNode* right)
	: m_Key(std::move(key)), m_Parent(parent), m_Left(left), m_Right(right) {}


/*****************************
Class Declaration
*****************************/

// 树
template <typename KeyType, typename Compare = std::less<KeyType>>
class Tree
{
public:
	using TreeNode = TreeNode<KeyType>;

	Tree();
	~Tree();

	inline void MakeEmpty();	// 清空树
	inline virtual TreeNode* Insert(const KeyType& key);	// 插入节点
	inline virtual bool Delete(const KeyType& key);	// 删除节点
	inline TreeNode* Find(const KeyType& key) const;	// 查找元素
	inline TreeNode* FindMax(TreeNode* node) const;	// 寻找某个节点的下的最大值，默认为根节点，也就是整棵树
	inline TreeNode* FindMin(TreeNode* node) const;	// 寻找某个节点的下的最小值，默认为根节点，也就是整棵树

protected:
	inline TreeNode* _Insert(const KeyType& key, TreeNode* node, TreeNode* parent);	// 插入的递归实现
	inline std::pair<bool, TreeNode*> UpdataHeadI(const KeyType& key);	// 更新头节点，插入版
	inline bool IsRight(const TreeNode* node) const;
	inline bool IsLeft(const TreeNode* node) const;
	inline void _Delete(TreeNode* node);

private:
	TreeNode* m_Head;
	size_t m_Size;
};

template <typename K, typename C>
Tree<K, C>::Tree()
{
	DSM::allocator<TreeNode> nAllocate;
	m_Head = nAllocate.allocate(1);
	m_Head->m_Parent = nullptr;
	m_Head->m_Left = nullptr;
	m_Head->m_Right = nullptr;
	m_Size = 0;
}

template <typename K, typename C>
Tree<K, C>::~Tree()
{
	MakeEmpty();	// 清空树
	DSM::allocator<TreeNode> nAllocate;
	nAllocate.destroy(m_Head);	// 释放头节点
}



// 插入元素元素时更新头节点,同时执行插入或删除操作
template <typename K, typename C>
inline std::pair<bool, TreeNode<K>*> Tree<K, C>::UpdataHeadI(const K& key)
{
	TreeNode* left = m_Head->m_Left, * right = m_Head->m_Right;
	DSM::allocator<TreeNode> nAllo;
	DSM::allocator<K> kAllo;
	C cmp;
	if (cmp(key, left->m_Key)) {	// 比最小的节点还小
		TreeNode* newNode = nAllo.allocate(1);
		nAllo.construct(newNode, TreeNode(key, left));
		kAllo.construct(&newNode->m_Key, key);
		left->m_Left = newNode;
		m_Head->m_Left = newNode;
		return { true, newNode };
	}
	else if (key > right->m_Key) {	// 比最大的节点大
		TreeNode* newNode = nAllo.allocate(1);
		nAllo.construct(newNode, TreeNode(key, right));
		kAllo.construct(&newNode->m_Key, key);
		right->m_Right = newNode;
		m_Head->m_Right = newNode;
		return { true, newNode };
	}
	return { false,nullptr };
}

template <typename K, typename C>
inline TreeNode<K>* Tree<K, C>::_Insert(const K& key, TreeNode* node, TreeNode* parent)
{
	if (!node) {
		DSM::allocator<TreeNode> nAllo;
		DSM::allocator<K> kAllo;
		node = nAllo.allocate(1);
		nAllo.construct(node, TreeNode(key, parent));
		kAllo.construct(&node->m_Key, key);
		if (key < parent->m_Key) {
			parent->m_Left = node;
		}
		else {
			parent->m_Right = node;
		}
	}
	else if (key < node->m_Key) {
		node->m_Left = _Insert(key, node->m_Left, node);
	}
	else if (key > node->m_Key) {
		node->m_Right = _Insert(key, node->m_Right, node);
	}

	return node;
}

template <typename K, typename C>
inline TreeNode<K>* Tree<K, C>::Insert(const K& key)	// 插入节点
{
	if (!m_Head->m_Parent) {	// 若无根节点，往后不考虑无根节点
		DSM::allocator<TreeNode> nAllo;
		DSM::allocator<K> kAllo;
		TreeNode* newNode = nAllo.allocate(1);
		nAllo.construct(newNode, TreeNode(key, m_Head));
		kAllo.construct(&newNode->m_Key, key);
		m_Head->m_Parent = m_Head->m_Left = m_Head->m_Right = newNode;
		++m_Size;
		return newNode;
	}

	auto isExtreme = UpdataHeadI(key);
	if (isExtreme.first) {
		++m_Size;
		return isExtreme.second;
	}

	TreeNode* node = _Insert(key, m_Head->m_Parent, m_Head);
	if (node) {
		++m_Size;
	}
	return node;
}



template <typename K, typename C>
inline TreeNode<K>* Tree<K, C>::Find(const K& key) const
{
	TreeNode* node;
	for (node = m_Head->m_Parent; node && node->m_Key != key;) {
		C cmp;
		if (cmp(key, node->m_Key)) {
			node = node->m_Left;
		}
		else {
			node = node->m_Right;
		}
	}

	return node;
}

template <typename K,typename C>
inline TreeNode<K>* Tree<K, C>::FindMax(TreeNode* node) const
{
	while (node->m_Right) {
		node = node->m_Right;
	}
	return node;
}

template <typename K, typename C>
inline TreeNode<K>* Tree<K, C>::FindMin(TreeNode* node) const
{
	while (node->m_Left) {
		node = node->m_Left;
	}
	return node;
}




template <typename K, typename C>
inline void Tree<K, C>::_Delete(TreeNode* deNode)
{
	DSM::allocator<TreeNode> nAllo;
	DSM::allocator<K> kAllo;
	TreeNode* parent = deNode->m_Parent;

	if (deNode->m_Key == m_Head->m_Parent->m_Key && !(deNode->m_Left && deNode->m_Right)) {
		if (IsLeft(deNode)) {
			m_Head->m_Parent = deNode->m_Right;
			if (deNode->m_Right) {
				deNode->m_Right->m_Parent = m_Head;
			}
			m_Head->m_Left = deNode->m_Right;
		}
		else {
			m_Head->m_Parent = deNode->m_Left;
			if (deNode->m_Left) {
				deNode->m_Left->m_Parent = m_Head;
			}
			m_Head->m_Right = deNode->m_Left;
		}
	}
	else if (deNode->m_Left && deNode->m_Right) {
		TreeNode* replace = FindMin(deNode->m_Right);
		K tmpKey = replace->m_Key;
		_Delete(replace);
		memcpy(&deNode->m_Key, &tmpKey, sizeof(K));
		return;
	}
	else if (!deNode->m_Left && !deNode->m_Right) {
		if (IsLeft(deNode)) {
			parent->m_Left = nullptr;
		}
		else {
			parent->m_Right = nullptr;
		}
	}
	else {
		if (deNode->m_Left) {
			if (IsLeft(deNode)) {
				parent->m_Left = deNode->m_Left;
			}
			else {
				parent->m_Right = deNode->m_Left;
			}
			deNode->m_Left->m_Parent = parent;
		}
		else {
			if (IsLeft(deNode)) {
				parent->m_Left = deNode->m_Right;
			}
			else {
				parent->m_Right = deNode->m_Right;
			}
			deNode->m_Right->m_Parent = parent;
		}
	}
	kAllo.destroy(&deNode->m_Key);
	nAllo.destroy(deNode);
	nAllo.deallocate(deNode, 1);
}

template <typename K, typename C>
inline bool Tree<K, C>::Delete(const K& key)
{
	if (!m_Head->m_Parent) {
		return false;
	}

	TreeNode* deNode = Find(key);
	if (!deNode) {
		return false;
	}

	_Delete(deNode);
	
	--m_Size;
	if (m_Size > 1) {
		m_Head->m_Left = FindMin(m_Head->m_Parent);
		m_Head->m_Right = FindMax(m_Head->m_Parent);
	}

	return true;
}


template <typename K, typename C>
inline void Tree<K, C>::MakeEmpty()
{
	while (m_Size) {
		Delete(m_Head->m_Left->m_Key);
	}
}



template <typename K, typename C>
inline bool Tree<K, C>::IsLeft(const TreeNode* node) const
{
	return node->m_Parent->m_Left == node;
}

template <typename K, typename C>
inline bool Tree<K, C>::IsRight(const TreeNode* node) const
{
	return node->m_Parent->right == node;
}


}

#endif // !TREE__HPP__
