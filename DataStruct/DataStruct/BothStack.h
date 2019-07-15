#ifndef _BOTHSTACK_H_
#define _BOTHSTACK_H_
#include <vector>
#include <iostream>
#include <cstdlib>

template <class T>
class BothStack
{
public:
	BothStack();
	BothStack(BothStack<T>& bothstack);
	~BothStack();
	void	push_one(const T& obj);
	void	push_two(const T& obj);
	T		pop_one();
	T		pop_two();
	T		top_one() const;
	T		top_two() const;
	size_t	one_size() const;
	size_t	two_size() const;
	bool	empty_one() const;
	bool	empty_two() const;
	void	print_list_one() const;
	void    print_list_two() const;
	BothStack<T>& operator=(BothStack<T>& bothstack);

private:
	size_t					stack_one_size = 0;
	size_t					stack_two_size = 0;
	size_t					max_size = 20;
	int						top_index_one = -1;
	int						top_index_two = 20;
	std::vector<T>			both_stack;
};

template <class T>
BothStack<T>::BothStack()
{
	both_stack.resize(20);
}

template <class T>
BothStack<T>::BothStack(BothStack<T>& bothstack)
{
	this->both_stack = bothstack.both_stack;
	this->max_size = bothstack.max_size;
	this->stack_one_size = bothstack.stack_one_size;
	this->stack_two_size = bothstack.stack_two_size;
	this->top_index_one = bothstack.top_index_one;
	this->top_index_two = bothstack.top_index_two;
}

template <class T>
BothStack<T>::~BothStack()
{
}

template <class T>
void BothStack<T>::push_one(const T& obj)
{
	if ((top_index_two - top_index_one) > 1)
	{
		top_index_one++;
		both_stack[top_index_one] = obj;
		stack_one_size++;
	}
}

template <class T>
void BothStack<T>::push_two(const T& obj)
{
	if ((top_index_two - top_index_one) > 1)
	{
		top_index_two--;
		both_stack[top_index_two] = obj;
		stack_two_size++;
	}
}

template <class T>
T	BothStack<T>::pop_one()
{
	if (top_index_one == -1) std::abort();
	stack_one_size--;
	return both_stack[top_index_one--];
}

template <class T>
T	BothStack<T>::pop_two()
{
	if (top_index_two == 20) std::abort();
	stack_two_size--;
	return both_stack[top_index_two++];
}

template <class T>
size_t BothStack<T>::one_size() const
{
	return stack_one_size;
}

template <class T>
size_t BothStack<T>::two_size() const
{
	return stack_two_size;
}

template <class T>
T BothStack<T>::top_one() const
{
	if (top_index_one == -1) std::abort();
	return both_stack[top_index_one];
}

template <class T>
T BothStack<T>::top_two() const
{
	if (top_index_two == 20) std::abort();
	return both_stack[top_index_two];
}

template <class T>
bool BothStack<T>::empty_one() const
{
	if (stack_one_size == 0) return true;
	return false;
}

template <class T>
bool BothStack<T>::empty_two() const
{
	if (stack_two_size == 0) return true;
	return false;
}

template <class T>
void BothStack<T>::print_list_one() const
{
	if (top_index_one != -1) {
		for (int i = 0; i <= top_index_one; i++)
		{
			std::cout << both_stack[i] << " ";
		}
		std::cout << std::endl;
	}
}

template <class T>
void BothStack<T>::print_list_two() const
{
	if (top_index_two != 20) {
		for (int i = 19; i >= top_index_two; i--)
		{
			std::cout << both_stack[i] << " ";
		}
		std::cout << std::endl;
	}
}

template <class T>
BothStack<T>& BothStack<T>::operator=(BothStack<T>& bothstack)
{
	this->both_stack = bothstack.both_stack;
	this->max_size = bothstack.max_size;
	this->stack_one_size = bothstack.stack_one_size;
	this->stack_two_size = bothstack.stack_two_size;
	this->top_index_one = bothstack.top_index_one;
	this->top_index_two = bothstack.top_index_two;

	return *this;
}

#endif

