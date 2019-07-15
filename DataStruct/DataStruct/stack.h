#ifndef _STACK_H_
#define _STACK_H_
#include <iostream>
#include <vector>
#include <cstdlib>

template <class T>
class stack
{
public:
	stack();
	stack(stack<T>& stack);
	~stack();
	bool	is_empty() const;
	size_t  size()	   const;
	size_t  max_size() const;
	T		top()	   const;
	T		pop();
	void	push(const T& obj);
	void    print_list() const;
	stack<T>& operator=(stack<T>& stack);

private:
	int					top_index = -1;
	int					max = 10;
	std::vector<T>		vec_stack;

};

template <class T>
stack<T>::stack()
{
	vec_stack.resize(max);
}

template <class T>
stack<T>::stack(stack<T>& stack)
{
	this->vec_stack = stack.vec_stack;
	this->max = stack.max;
	this->top_index = stack.top_index;
}

template <class T>
stack<T>::~stack()
{
}

template <class T>
bool stack<T>::is_empty() const
{
	if (vec_stack.size() == 0) return true;
	return false;
}

template <class T>
T stack<T>::top() const
{
	if (top_index == -1) std::abort();
	return vec_stack[top_index];
}

template <class T>
T stack<T>::pop()
{
	if (top_index == -1) std::abort();
	return vec_stack[top_index--];
}

template <class T>
void stack<T>::push(const T& obj)
{
	if (top_index == 9) std::abort();
	top_index++;
	vec_stack[top_index] = obj;
}

template <class T>
size_t stack<T>::size() const
{
	return ++top_index;
}

template <class T>
size_t stack<T>::max_size() const
{
	return max;
}

template <class T>
stack<T>& stack<T>::operator=(stack<T>& stack)
{
	this->vec_stack = stack.vec_stack;
	this->max = stack.max;
	this->top_index = stack.top_index;

	return *this;
}

template <class T>
void stack<T>::print_list() const
{
	for (size_t i = 0; i <= top_index; i++)
	{
		std::cout << vec_stack[i] << std::endl;
	}
}

#endif
