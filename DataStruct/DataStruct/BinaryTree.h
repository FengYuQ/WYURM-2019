#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_
#include <iostream>
#include <cstdlib>
#include <queue>
#include <stack>

template <class T>
struct TreeNode
{
	T					_data;
	TreeNode<T>*		_left;
	TreeNode<T>*		_right;

	TreeNode(const T& data, TreeNode<T>* left = nullptr, TreeNode<T>* right = nullptr) : _data(data),
																						 _left(left),
																						 _right(right)

	{
	}

};

template <class T>
class BinaryTree
{
public:
	BinaryTree();
	BinaryTree(std::initializer_list<T> init_list);
	~BinaryTree();
	void insert(const T& obj);
	T	 remove(const T& obj);
	void preOrder() const;
	void inOrder() const;
	void postOrder() const;
	void leverOrder() const; 

private:
	TreeNode<T>*			root = nullptr;

private:
	TreeNode<T>*			Insert(const T& obj, TreeNode<T>* node);
	TreeNode<T>*			Delete(const T& obj, TreeNode<T>* node);
	TreeNode<T>*			findMin(TreeNode<T>* node);
	void					pre_order_iteration(TreeNode<T>* node) const;
	void					pre_order_recursive(TreeNode<T>* node) const;
	void					in_order(TreeNode<T>* node) const;
	void					post_order(TreeNode<T>* node) const;
};

template <class T>
BinaryTree<T>::BinaryTree()
{
}

template <class T>
BinaryTree<T>::BinaryTree(std::initializer_list<T> init_list)
{
	for (const auto& obj : init_list)
	{
		root = Insert(obj, root);
	}
}

template <class T>
BinaryTree<T>::~BinaryTree()
{
}

template <class T>
void BinaryTree<T>::preOrder() const
{
	pre_order_recursive(root);
}

template <class T>
void BinaryTree<T>::inOrder() const
{
	in_order(root);
}

template <class T>
void BinaryTree<T>::postOrder() const
{
	post_order(root);
}

template <class T>
void BinaryTree<T>::leverOrder() const
{
	if (root != nullptr)
	{
		std::queue<TreeNode<T>*> tree;
		int num = 1;
		tree.push(root);
		while (tree.size())
		{
			int i = 0;
			while (i < num)
			{
				TreeNode<T>* node = tree.front();
				if (node->_left) tree.push(node->_left);
				if (node->_right) tree.push(node->_right);
				std::cout << node->_data;
				tree.pop();
				i++;
			}
			num *= 2;
		}
	}
}

template <class T>
TreeNode<T>* BinaryTree<T>::Insert(const T& obj, TreeNode<T>* node)
{
	if (node == nullptr)
	{
		node = new TreeNode<T>(obj);
	}
	else
	{
		if (obj < node->_data)
		{
			node->_left = Insert(obj, node->_left);
		}
		else
		{
			node->_right = Insert(obj, node->_right);
		}
	}

	return node;
}

template <class T>
void BinaryTree<T>::insert(const T& obj)
{
	Insert(obj, root);
}

template <class T>
TreeNode<T>* BinaryTree<T>::Delete(const T& obj, TreeNode<T>* node)
{
	//未找到
	if (node == nullptr) return nullptr;

	//寻找中
	if (obj < node->_data)
	{
		node->_left = Delete(obj, node->_left);
	}
	else
	{
		node->_right = Delete(obj, node->_right);
	}

	//已经找到，分类讨论
	if (node->_left && node->_right)
	{
		TreeNode<T>* minRight = findMin(node->_right);
		node->_data = minRight->_data;
		node->_right = Delete(minRight->_data, node->_right);
	}
	else
	{
		TreeNode<T>* temp = node;
		if (node->_left)
		{
			node = node->_left;
		}
		if (node->_right)
		{
			node = node->_right;
		}
		delete temp;
	}

	return node;
}

template <class T>
TreeNode<T>* BinaryTree<T>::findMin(TreeNode<T>* node)
{
	if (node->_left == nullptr) return node;
	return finMin(node->_left);
}

template <class T>
T BinaryTree<T>::remove(const T& obj)
{
	TreeNode<T>* node = Delete(obj, root);
	if (node) std::abort();
	return node->_data;
}

template <class T>
void BinaryTree<T>::pre_order_iteration(TreeNode<T>* node) const
{
	if (node != nullptr)
	{
		std::cout << node->_data << " ";
		pre_order(node->_left);
		pre_order(node->_right);
	}
}

template <class T>
void BinaryTree<T>::pre_order_recursive(TreeNode<T>* node) const
{
	if (node != nullptr)
	{
		std::stack<TreeNode<T>*> tree;
		TreeNode<T>* tempNode = node;
		while (tree.size() || tempNode)
		{
			while (tempNode)
			{
				std::cout << tempNode->_data << " ";
				tree.push(tempNode);
				tempNode = tree.top()->_left;
			}

			if (tree.size())
			{
				tempNode = tree.top()->_right;
				tree.pop();
			}
		}
	}
}

template <class T>
void BinaryTree<T>::in_order(TreeNode<T>* node) const
{
	if (node != nullptr)
	{
		in_order(node->_left);
		std::cout << node->_data;
		in_order(node->_right);
	}
}

template <class T>
void BinaryTree<T>::post_order(TreeNode<T>* node) const
{
	if (node != nullptr)
	{
		post_order(node->_left);
		post_order(node->_right);
		std::cout << node->_data;
	}
}

#endif

