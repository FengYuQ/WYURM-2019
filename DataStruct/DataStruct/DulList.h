#ifndef _DULLIST_H_
#define _DULLIST_H_
#include <iostream>
#include <cstdlib>
#include <initializer_list>

template <class T>
struct DulNode
{
	T				_data;
	DulNode<T>*		_prior;
	DulNode<T>*		_next;

	DulNode() : _prior(nullptr),
				_next(nullptr)
	{
	}

	DulNode(const T& data,
		DulNode<T>* prior = nullptr,
		DulNode<T>* next = nullptr)
	{
		_data = data;
	}
};

template <class T>
class DulList
{
public:
	DulList();
	DulList(DulList<T>& dullist);
	DulList(std::initializer_list<T> init_list);
	~DulList();
	int  get_length() const;
	T	 get_data(int i) const;
	bool set_data(int i, const T& obj);
	void insert(int i, const T& obj);
	T    remove(int i);
	void push_back(const T& obj);
	void push_front(const T& obj);
	bool is_empty() const;
	bool is_circles() const;
	bool is_forward() const;
	void turn_to_circles();
	void turn_to_forward();
	void turn_back();
	void print_list_forward() const;
	void print_list_rev() const;
	DulNode<T>*		get_rear() const;
	DulList<T>& operator=(DulList<T>& dullist);
	
private: 
	DulNode<T>*			head;
	DulNode<T>*			rear;
	int					length;
	bool				circle_flag = true;
	bool				forward_flag = false;

private:
	DulNode<T>*		Locate(int i) const;
	DulNode<T>*		get_head() const;
	
};

template <class T>
DulList<T>::DulList()
{
	head = new DulNode<T>;
	rear = head->_next;
}

template <class T>
DulList<T>::DulList(DulList<T>& dullist)
{
	head = new DulNode<T>;
	DulNode<T>* node = dullist.getHead()->_next;
	DulNode<T>* currentNode = head;
	while (node)
	{
		DulNode<T>* tempNode = new DulNode<T>(node->_data);
		tempNode->_prior = currentNode;
		currentNode->_next = tempNode;
		currentNode = currentNode->_next;
		node = node->_next;
		length++;
	}
	rear = currentNode;
}

template <class T>
DulList<T>::~DulList()
{
}

template <class T>
int DulList<T>::get_length() const
{
	return length;
}

template <class T>
void DulList<T>::insert(int i, const T& obj)
{
	if (i >= 0)
	{
		DulNode<T>* node = Locate(i);
		if (node)
		{
			DulNode<T>* newNode = new DulNode<T>(obj);
			node->_prior->_next = newNode;
			newNode->_prior = node->_prior;
			newNode->_next = node;
			node->_prior = newNode;
			length++;
		}
	}
}

template <class T>
DulNode<T>* DulList<T>::Locate(int i) const
{
	if (i < 0) return nullptr;
	int count = 0;
	DulNode<T>* node = head;
	while (count < i)
	{
		if (node->_next == nullptr) return nullptr;
		node = node->_next;
		count++;
	}

	return node->_next;
}

template <class T>
DulNode<T>* DulList<T>::get_head() const
{
	return head;
}

template <class T>
DulNode<T>* DulList<T>::get_rear() const
{
	return rear;
}

template <class T>
T DulList<T>::remove(int i)
{
	DulNode<T>* node = Locate(i);
	if (node)
	{
		node->_prior->_next = node->_next;
		if (node == rear)
		{
			rear = node->_prior;
		}
		else
		{
			node->_next->_prior = node->_prior;
		}
		T	temp_data = node->_data;
		delete node;
		length--;
		return temp_data;
	}

	std::abort();
}

template <class T>
void DulList<T>::push_back(const T& obj)
{
	DulNode<T>* newNode = new DulNode<T>(obj);
	rear->_next = newNode;
	newNode->_prior = rear;
	rear = newNode;
	length++;
}

template <class T>
void DulList<T>::push_front(const T& obj)
{
	DulNode<T>* newNode = new DulNode<T>(obj);
	head->_next->_prior = newNode;
	newNode->_next = head->_next;
	newNode->_prior = head;
	head->_next = newNode;
	length++;
}

template <class T>
T DulList<T>::get_data(int i) const
{
	DulNode<T>* node = Locate(i);
	if (node)
	{
		return node->_data;
	}
	std::abort();
}

template <class T>
bool DulList<T>::set_data(int i, const T& obj)
{
	DulNode<T>* node = Locate(i);
	if (node)
	{
		node->_data = obj;
		return true;
	}
	return false;
}

template <class T>
void DulList<T>::turn_to_circles()
{
	rear->_next = head;
	head->_prior = rear;
	circle_flag = true;
	forward_flag = false;
}

template <class T>
void DulList<T>::turn_to_forward()
{
	DulNode<T>* node = head->_next;
	if (circle_flag)
	{
		head->_prior = nullptr;
		rear->_next = nullptr;
	}
	while (node)
	{
		node->_prior = nullptr;
		node = node->_next;
	}
	forward_flag = true;
	circle_flag = false;
}

template <class T>
void DulList<T>::turn_back()
{
	DulNode<T>* node = head->_next;
	DulNode<T>* tempNode = head;
	while (node)
	{
		node->_prior = tempNode;
		node = node->_next;
		tempNode = tempNode->_next;
	}
	forward_flag = false;
	circle_flag = true;
}

template <class T>
bool DulList<T>::is_empty() const
{
	if (length == 0) return true;
	return false;
}

template <class T>
void DulList<T>::print_list_forward() const
{

	DulNode<T>* node = head->_next;
	while (node != rear->_next)
	{
		std::cout << node->_data << " ";
		node = node->_next;
	}
	std::cout << std::endl;
}

template <class T>
void DulList<T>::print_list_rev() const
{
	if (circle_flag)
	{
		DulNode<T>* node = rear;
		while (node != head)
		{
			std::cout << node->_data << " ";
			node = node->_prior;
		}
		std::cout << std::endl;
	}
}

template <class T>
bool DulList<T>::is_circles() const
{
	return circle_flag;
}

template <class T>
bool DulList<T>::is_forward() const
{
	return forward_flag;
}

template <class T>
DulList<T>& DulList<T>::operator=(DulList<T>& dulist)
{
	head = new DulNode<T>;
	DulNode<T>* currentNode = head;
	DulNode<T>* node = dulist.get_head()->_next;
	while (node)
	{
		DulNode<T>* newNode = new DulNode<T>(node->_data);
		currentNode->_next = newNode;
		newNode->_prior = currentNode;
		currentNode = currentNode->_next;
		node = node->_next;
	}
	rear = currentNode;

	return *this;
}

template <class T>
DulList<T>::DulList(std::initializer_list<T> init_list)
{
	head = new DulNode<T>;
	DulNode<T>* node = head;
	for (const auto& o : init_list)
	{
		DulNode<T>* newNode = new DulNode<T>(o);
		node->_next = newNode;
		newNode->_prior = node;
		node = node->_next;
		length++;
	}
	rear = node;
}

#endif

