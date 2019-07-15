#ifndef _CIRQUEUE_H_
#define _CIRQUEUE_H_
#include <iostream>
#include <cstdlib>
#include <array>

template <class T>
class CirQueue
{
public:
	CirQueue();
	~CirQueue();
	void	enQueue(const T& obj);
	T		deQueue();
	T		getQueue();
	bool	empty();
	int		get_size();
	void	print_list();

private:
	int						front = -1;
	int						rear = -1;
	int						size = 0;
	static constexpr int			queue_size = 6;
	std::array<T, queue_size>		queue;
};

template <class T>
CirQueue<T>::CirQueue()
{
}

template <class T>
CirQueue<T>::~CirQueue()
{
}

template <class T>
void CirQueue<T>::enQueue(const T& obj)
{
	if ((rear + 1) % queue_size == front) std::abort();
	rear = (rear + 1) % queue_size;
	queue[rear] = obj;
	size++;
}

template <class T>
T CirQueue<T>::deQueue()
{
	if (front == rear) std::abort();
	front = (front + 1) % queue_size;
	size--;
	return queue[front];
}

template <class T>
T CirQueue<T>::getQueue()
{
	if (front == rear) std::abort();
	return queue[(front + 1) % queue_size];
}

template <class T>
bool CirQueue<T>::empty()
{
	return size ? false : true;
}

template <class T>
int CirQueue<T>::get_size()
{
	return size;
}

template <class T>
void CirQueue<T>::print_list()
{
	if (front != rear)
	{
		for (int i = (front + 1) % queue_size; i != rear; i = (i + 1) % queue_size)
		{
			std::cout << queue[i] << " ";
		}
		std::cout << queue[rear] << std::endl;
	}
}

#endif
