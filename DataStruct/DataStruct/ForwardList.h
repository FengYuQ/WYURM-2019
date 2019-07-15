#ifndef _FORWARDLIST_H_
#define _FORWARDLIST_H_
#include <iostream>
#include <cstdlib>
#include <initializer_list>

template <class T>
struct LinkNode
{
	T				_data;
	LinkNode<T>*	_next;
 
	LinkNode(LinkNode<T>* next = nullptr)
	{
		_next = next;
	}

	LinkNode(const T& data, LinkNode<T>* next = nullptr)
	{
		_data = data;
		_next = next;
	}
};

template <class T>
class ForwardList
{
public:
	ForwardList();
	ForwardList(const T& obj);
	ForwardList(ForwardList<T>& forwardlist);
	ForwardList(std::initializer_list<T> init_list);
	~ForwardList();
	int		getLength() const;
	T		getData(int i) const;
	void	setData(int i, const T& obj);
	void	insert(int i, const T& obj);
	void	push_back(const T& obj);
	void	push_front(const T& obj);
	T		remove(int i);
	bool	isEmpty() const;
	void	printList() const;
	ForwardList<T>& operator=(ForwardList<T>& forwardlist);

private:
	LinkNode<T>*		head;
	int					length;

private:
	LinkNode<T>* Locate(int i) const;
	LinkNode<T>* get_head() const;
};

template <class T>
ForwardList<T>::ForwardList() :length(0)
{
	head = new LinkNode<T>;
}

template <class T>
ForwardList<T>::ForwardList(const T& obj) : ForwardList()
{
	head->next = new LinkNode<T>(obj);
	length++;
}

template <class T>
ForwardList<T>::ForwardList(ForwardList<T>& forwardlist) : ForwardList()
{
	LinkNode<T>* node = forwardlist.get_head()->_next;
	LinkNode<T>* currentNode = head;
	for (; node; node = node->_next)
	{
		LinkNode<T>* tempNode = new LinkNode<T>(node->_data);
		currentNode->_next = tempNode;
		currentNode = currentNode->_next;
		length++;
	}
}

template <class T>
ForwardList<T>::~ForwardList()
{
}

template <class T>
LinkNode<T>* ForwardList<T>::Locate(int i) const
{
	if (i == -1) return head;
	if (i < 0) return nullptr;
	int count = 0;
	LinkNode<T>* node = head;
	while (count < i)
	{
		if (node->_next == nullptr)return nullptr;
		node = node->_next;
		count++;
	}
	return node->_next;
}

template <class T>
int ForwardList<T>::getLength() const
{
	return length;
}

template <class T>
T ForwardList<T>::getData(int i) const
{
	LinkNode<T>* node = Locate(i);
	if (node)
	{
		return node->_data;
	}
	std::abort();
}

template <class T>
void ForwardList<T>::setData(int i, const T& obj)
{
	LinkNode<T>* node = Locate(i);
	if (node)
	{
		node->_data = obj;
	}
}

template <class T>
void ForwardList<T>::insert(int i, const T& obj)
{
	if (i >= 0)
	{
		LinkNode<T>* node = Locate(i - 1);
		if (node)
		{
			LinkNode<T>* newNode = new LinkNode<T>;
			newNode->_data = obj;
			newNode->_next = node->_next;
			node->_next = newNode;
			length++;
		}
	}
}

template <class T>
void ForwardList<T>::push_back(const T& obj)
{
	LinkNode<T>* newNode = new LinkNode<T>(obj);
	LinkNode<T>* node = head;
	while (node->_next)
	{
		node = node->_next;
	}
	node->_next = newNode;
	length++;
}

template <class T>
void ForwardList<T>::push_front(const T& obj)
{
	LinkNode<T>* newNode = new LinkNode<T>(obj);
	newNode->_next = head->_next;
	head->_next = newNode;
	length++;
}

template <class T>
T ForwardList<T>::remove(int i)
{
	LinkNode<T>* node = Locate(i - 1);
	if (node)
	{
		LinkNode<T>* tempNode = node->_next;
		T tempData = tempNode->_data;
		node->_next = node->_next->_next;
		delete tempNode;
		length--;
		return tempData;
	}

	std::abort();
}

template <class T>
bool ForwardList<T>::isEmpty() const
{
	if (length != 0)return true;
	return false;
}

template <class T>
void ForwardList<T>::printList() const
{
	if (head->_next)
	{
		for (LinkNode<T>* node = head->_next; node; node = node->_next)
		{
			std::cout << node->_data << std::endl;
		}
	}
}

template <class T>
ForwardList<T>& ForwardList<T>::operator=(ForwardList<T>& forwardlist)
{
	this->head = new LinkNode<T>;
	LinkNode<T>* node = forwardlist.get_head()->_next;
	LinkNode<T>* currentNode = head;
	for (; node; node = node->_next)
	{
		LinkNode<T>* tempNode = new LinkNode<T>(node->_data);
		currentNode->_next = tempNode;
		currentNode = currentNode->_next;
		length++;
	}

	return *this;
}

template <class T>
ForwardList<T>::ForwardList(std::initializer_list<T> init_list)
{
	head = new LinkNode<T>;
	LinkNode<T>* node = head;
	for (const auto& o : init_list)
	{
		LinkNode<T>* newNode = new LinkNode<T>(o);
		node->_next = newNode;
		node = node->_next;
		length++;
	}
}

template <class T>
LinkNode<T>* ForwardList<T>::get_head() const
{
	return head;
}

#endif
