#ifndef _TASK_H_
#define _TASK_H_
#include <string>
#include <stack>
#include <vector>
#include <iostream>
#include <queue>

void digital_sort(int array[], int array_size)
{
	int i = 0, j = array_size - 1;
	while (i < j)
	{
		while (array[i] < 0)
		{
			i++;
		}

		while (array[j] >= 0)
		{
			j--;
		}
		if (i < j)
		{
			int temp = array[i];
			array[i] = array[j];
			array[j] = temp;
		}
	}

	j = array_size - 1;

	while (i < j)
	{
		while (array[j] != 0)
		{
			j--;
		}

		int temp = array[i];
		array[i++] = array[j];
		array[j] = temp;
		
	}
	
	for (int i = 0; i < array_size; i++)
	{
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
}

int sign_priority(const char sign)
{
	if (sign == '*' || sign == '/') return 2;
	if (sign == '+' || sign == '-') return 1;
	if (sign == '(') return -1;
	if (sign == ')') return -2;
	return 0;
}

int sign_identify(std::string& sign)
{
	if (sign == "+") return 1;
	if (sign == "-") return 2;
	if (sign == "*") return 3;
	if (sign == "/") return 4;
	return 0;
}

double suffix_value(std::vector<std::string>& exp)
{
	std::stack<double> nums;
	for (int i = 0; i < exp.size(); i++)
	{
		if (!sign_identify(exp[i]))
		{
			nums.push(std::stod(exp[i]));
		}
		else
		{
			double a = nums.top();
			nums.pop();
			double b = nums.top();
			nums.pop();
			switch (sign_identify(exp[i]))
			{
			case 1:
				nums.push(b + a);
				break;
			case 2:
				nums.push(b - a);
				break;
			case 3:
				nums.push(b * a);
				break;
			case 4:
				nums.push(b / a);
				break;
			}
		}
	}
	return nums.top();
}


void infixtosuffix(const std::string& exp)
{
	std::string num;
	std::string sign;
	std::vector<std::string> se;
	std::stack<char> signs;
	for (int i = 0; i < exp.size(); i++)
	{
		if (!sign_priority(exp[i]))
		{
			num.push_back(exp[i]);
		}
		else
		{
			if (num != "")
			{
				se.push_back(num);
				num.clear();
			}
			if (signs.empty())
			{
				signs.push(exp[i]);
			}
			else
			{
				switch (sign_priority(exp[i]))
				{
				case 1:
					while (signs.size() && sign_priority(exp[i]) <= sign_priority(signs.top()))
					{
						sign.push_back(signs.top());
						se.push_back(sign);
						signs.pop();
						sign.clear();
					}
					signs.push(exp[i]);
					break;
				case 2:
					signs.push(exp[i]);
					break;
				case -1:
					signs.push(exp[i]);
					break;
				case -2:
					while (sign_priority(signs.top()) != -1)
					{
						sign.push_back(signs.top());
						se.push_back(sign);
						signs.pop();
						sign.clear();
					}
					signs.pop();
					break;
				}
			}
		}
	}
	se.push_back(num);
	if (signs.size())
	{
		while (signs.size())
		{
			sign.push_back(signs.top());
			se.push_back(sign);
			signs.pop();
			sign.clear();
		}
	}
	for (std::string& s : se)
	{
		std::cout << s;
	}
	std::cout << std::endl;
	std::cout <<"表达式结果为: "<< suffix_value(se) << std::endl;
}

void freey_manage(int _busSize, int _truckSize)
{
	std::queue<char> bus;
	std::queue<char> truck;
	std::queue<char> freey;
	for (int i = 0; i < _busSize; i++)
	{
		bus.push('*');
	}
	for (int i = 0; i < _truckSize; i++)
	{
		truck.push('#');
	}


	int times = 0;
	while (!bus.empty() || !truck.empty())
	{
		int busSize = 0, truckSize = 0, totalSize = 0;
		while (totalSize != 10 && (!bus.empty() || !truck.empty()))
		{
			if (busSize < 4 && !bus.empty())
			{
				freey.push(bus.front());
				bus.pop();
				busSize++;
				totalSize++;
			}

			if (busSize < 4 && bus.empty() && !truck.empty())
			{
				freey.push(truck.front());
				truck.pop();
				truckSize++;
				totalSize++;
			}

			if (busSize >= 4 && !truck.empty())
			{
				freey.push(truck.front());
				truck.pop();
				truckSize++;
				busSize = 0;
				totalSize++;
			}

			if (busSize >= 4 && truck.empty() && !bus.empty())
			{
				freey.push(bus.front());
				bus.pop();
				busSize++;
				truckSize = 0;
				totalSize++;
			}
		}
		times++;
		std::cout << "The " << times << " time :" << std::endl;
		while (freey.size())
		{
			std::cout << freey.front();
			freey.pop();
		}
		std::cout << std::endl;
		
	}
}

void inOrder(int tree[], int pos, int size)
{
	if (tree[pos] != -1 && pos < size)
	{
		inOrder(tree, (pos + 1) * 2 - 1, size);
		std::cout << tree[pos] << " ";
		inOrder(tree, (pos + 1) * 2, size);
	}
}

#endif // !TASK_H_

