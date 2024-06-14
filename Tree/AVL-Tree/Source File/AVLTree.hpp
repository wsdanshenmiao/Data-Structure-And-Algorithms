#ifndef __AVLTREE__HPP__
#define __AVLTREE__HPP__

#include <utility>
#include "allocator.hpp"

namespace DSM {

// 树的节点
template <typename KeyType>
struct AVLTreeNode
{
	AVLTreeNode* m_Left;
	AVLTreeNode* m_Right;
	int m_Height;
	KeyType m_Key;

	AVLTreeNode() = default;
	AVLTreeNode(const KeyType& key, int height = 0, AVLTreeNode* left = nullptr, AVLTreeNode* right = nullptr);
	AVLTreeNode(const AVLTreeNode& other) = default;
};

template <typename K>
AVLTreeNode<K>::AVLTreeNode(const K& key, int height, AVLTreeNode* left, AVLTreeNode* right)
	:m_Key(key), m_Height(height), m_Left(left), m_Right(right) {}




// 树
template <typename KeyType, typename Compare = std::less<KeyType>>
class AVLTree
{
public:
	using Node = AVLTreeNode<KeyType>;
	using NAllocator = DSM::allocator<AVLTreeNode<KeyType>>;
	using KAllocator = DSM::allocator<KeyType>;

	AVLTree();
	~AVLTree();

	inline Node* Find(const KeyType& key) const;
	inline Node* FindMax(const Node* node) const;
	inline Node* FindMin(const Node* node) const;
	inline std::pair<bool, Node*> Insert(const KeyType& key);

private:
	inline std::pair<bool, Node*> _Insert(const KeyType& key, Node* node, Node* parent);
	inline bool IsRight(const Node* node) const;	// 判断是否是右子树
	inline bool IsLeft(const Node* node) const;	// 判断是否是左子树
	inline int Height(const Node* node) const;	// 获取节点高度，若为空则返回-1
	inline Node* LeftSingleRotate(Node* node);	// 左旋
	inline Node* RightSingleRotate(Node* node);	// 右旋
	inline Node* LeftDoubleRotate(Node* node);	// 左右旋
	inline Node* RightDoubleRotate(Node* node);	// 右左旋

private:
	Node* m_Root;
	size_t m_Size;
};

template <typename K, typename C>
AVLTree<K, C>::AVLTree()
{
	m_Root = nullptr;
	m_Size = 0;
}

template <typename K, typename C>
AVLTree<K, C>::~AVLTree()
{

}



template <typename K, typename C>
inline AVLTreeNode<K>* 
AVLTree<K, C>::Find(const K& key) const
{
	Node* node = m_Root->m_Left;
	C compare;
	for (; node && node->m_Key != key;) {
		if (compare(key, node->m_Key)) {
			node = node->m_Left;
		}
		else {
			node = node->m_Right;
		}
	}
	return node;
}

template <typename K, typename C>
inline AVLTreeNode<K>* 
AVLTree<K, C>::FindMax(const AVLTreeNode<K>* node) const
{
	if (!node) {
		return node;
	}
	while (node->m_Right) {
		node = node->m_Right;
	}
	return node;
}

template <typename K, typename C>
inline AVLTreeNode<K>* 
AVLTree<K, C>::FindMin(const AVLTreeNode<K>* node) const
{
	if (!node) {
		return node;
	}
	while (node->m_Left) {
		node = node->m_Left;
	}
	return node;
}




template <typename K, typename C>
inline bool AVLTree<K, C>::IsLeft(const AVLTreeNode<K>* node) const
{
	return node->m_Parent->m_Left == node;
}

template <typename K, typename C>
inline bool AVLTree<K, C>::IsRight(const AVLTreeNode<K>* node) const
{
	return node->m_Parent->right == node;
}

template <typename K, typename C>
inline int AVLTree<K, C>::Height(const AVLTreeNode<K>* node) const
{
	return node ? node->m_Height : -1;
}



template <typename K, typename C>
inline AVLTreeNode<K>* AVLTree<K, C>::LeftSingleRotate(Node* node)	// 左旋
{
	Node* k1 = node->m_Left;
	node->m_Left = k1->m_Right;
	k1->m_Right = node;

	// 旋转后底下的节点高度不变，但要更新旋转的节点
	node->m_Height = std::max(Height(node->m_Left), Height(node->m_Right)) + 1;
	k1->m_Height = std::max(Height(k1->m_Left), Height(k1->m_Right)) + 1;

	return k1;
}
template <typename K, typename C>
inline AVLTreeNode<K>* AVLTree<K, C>::RightSingleRotate(Node* node)	// 右旋
{
	Node* k1 = node->m_Right;
	node->m_Right = k1->m_Left;
	k1->m_Left = node;

	node->m_Height = std::max(Height(node->m_Left), Height(node->m_Right)) + 1;
	k1->m_Height = std::max(Height(k1->m_Left), Height(k1->m_Right)) + 1;

	return k1;
}
template <typename K, typename C>
inline AVLTreeNode<K>* AVLTree<K, C>::LeftDoubleRotate(Node* node)	// 左右旋
{
	// 先右后左
	node->m_Left = RightSingleRotate(node->m_Left);
	return LeftSingleRotate(node);
}
template <typename K, typename C>
inline AVLTreeNode<K>* AVLTree<K, C>::RightDoubleRotate(Node* node)	// 右左旋
{
	// 先左后右
	node->m_Right = LeftSingleRotate(node->m_Right);
	return RightSingleRotate(node);
}

template <typename K, typename C>
inline std::pair<bool, AVLTreeNode<K>*>
AVLTree<K, C>::_Insert(const K& key, AVLTreeNode<K>* node, AVLTreeNode<K>* parent)
{
	C compare;
	if (!node) {	//
		NAllocator nallocate;
		node = nallocate.allocate(1);
		nallocate.construct(node, Node(key));
		if (compare(key, parent->m_Key)) {	// 插入到树内
			parent->m_Left = node;
		}
		else {
			parent->m_Right = node;
		}
	}
	else if(key == node->m_Key) {	// 键值重复，插入失败
		return { false,node };
	}
	else if (compare(key, node->m_Key)) {	// 插入左侧
		auto mes = _Insert(key, node->m_Left, node);	// 左侧高度加一
		if (!mes.first) {
			return mes;
		}
		node->m_Left = mes.second;
		if (Height(node->m_Left) - Height(node->m_Right) == 2) {	// 插入后破坏平衡，旋转
			Node* changeNode = compare(key, node->m_Left->m_Key) ? LeftSingleRotate(node) : LeftDoubleRotate(node);
			m_Root = node == m_Root ? changeNode : m_Root;
			node = changeNode;
		}
	}
	else {	// 插入右侧
		auto mes = _Insert(key, node->m_Right, node);
		if (!mes.first) {
			return mes;
		}
		node->m_Right = mes.second;	// 右侧高度加一
		if (Height(node->m_Right) - Height(node->m_Left) == 2) {	// 插入后破坏平衡，旋转
			Node* changeNode = compare(node->m_Right->m_Key, key) ? RightSingleRotate(node) : RightDoubleRotate(node);
			m_Root = node == m_Root ? changeNode : m_Root;
			node = changeNode;
		}
	}
	// 更新高度 
	node->m_Height = std::max(Height(node->m_Left), Height(node->m_Right)) + 1;

	return { true, node };
}

template <typename K, typename C>
inline std::pair<bool, AVLTreeNode<K>*> 
AVLTree<K, C>::Insert(const K& key)
{
	if (!m_Root) {	// 若为根节点
		NAllocator nallocate;
		m_Root = nallocate.allocate(1);
		nallocate.construct(m_Root, Node(key));
		++m_Size;
		return { true,m_Root };
	}

	auto ret = _Insert(key, m_Root, nullptr);
	if (ret.first) {
		++m_Size;
	}
	return ret;
}




}

#endif // !__AVLTREE__HPP__
