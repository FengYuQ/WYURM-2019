#include "pch.h"
#include <iostream>
#include "BinaryTree.h"
#include "BothStack.h"
#include "CirQueue.h"
#include "DulList.h"
#include "ForwardList.h"
#include "stack.h"
#include "task.h"
#include <string>
#include <iostream>
#include <stack>
#include <queue>
#include <sstream>

int main()
{
	std::cout << "----------------实验一 （1）--------------"<< std::endl;
	std::cout << "输入序列：1, -1, 5, 0, 0" << std::endl;
	int test1[5] = { 1, -1, 5, 0, 0};
	std::cout << "输出序列：";
	digital_sort(test1, 5);
	std::cout << "------------------------------------------" << std::endl;
	system("pause");
	std::cout << std::endl;

	std::cout << "----------------实验一 （2）--------------" << std::endl;
	std::cout << "输入序列：1,2,3,4,5" << std::endl;
	DulList<int> dl = { 1,2,3,4,5 };
	std::cout << "顺序遍历： ";
	dl.print_list_forward();
	std::cout << "逆序遍历： ";
	dl.print_list_rev();
	std::cout << "------------------------------------------" << std::endl;
	system("pause");
	std::cout << std::endl;
	
	std::cout << "---------------实验二 （1）---------------" << std::endl;
	std::cout << "输入的中缀表达式为：1+2*3+(4*5+6)*7" << std::endl;
	std::cout << "后缀表达式为：";
	infixtosuffix("1+2*3+(4*5+6)*7");
	std::cout << "------------------------------------------" << std::endl;
	system("pause");
	std::cout << std::endl;

	std::cout << "---------------实验二（2）-----------------" << std::endl;
	BothStack<int> bs;
	std::cout << "栈1入栈顺序：1，2，3; 栈2入栈顺序：4，5，6" << std::endl;
	bs.push_one(1);
	bs.push_one(2);
	bs.push_one(3);
	bs.push_two(4);
	bs.push_two(5);
	bs.push_two(6);
	std::cout << "栈1遍历：";
	bs.print_list_one();
	std::cout << "栈2遍历：";
	bs.print_list_two();
	std::cout << "栈1出栈" << std::endl;
	bs.pop_one();
	std::cout << "出栈后 ：";
	bs.print_list_one();
	std::cout << "栈2出栈" << std::endl;
	bs.pop_two();
	std::cout << "出栈后 ：";
	bs.print_list_two();
	std::cout << "------------------------------------------" << std::endl;
	system("pause");
	std::cout << std::endl;

	std::cout << "-----------------实验三（1）---------------" << std::endl;
	CirQueue<int> cq;
	std::cout << "入队顺序：1，2，3，4，5" << std::endl;
	cq.enQueue(1);
	cq.enQueue(2);
	cq.enQueue(3);
	cq.enQueue(4);
	cq.enQueue(5);
	std::cout << "队头元素:" << cq.getQueue() << std::endl;
	std::cout << "出队前2个元素" << std::endl;
	cq.deQueue();
	cq.deQueue();
	std::cout << "队列遍历：";
	cq.print_list();
	std::cout << "------------------------------------------" << std::endl;
	system("pause");
	std::cout << std::endl;

	std::cout << "------------------实验三（2）---------------" << std::endl;
	std::cout << "客车总数：7，货车总数：9  (*代表客车，#代表火车)" << std::endl;
	freey_manage(7,9);
	std::cout << "------------------------2------------------" << std::endl;
	system("pause");
	std::cout << std::endl;

	std::cout << "------------------实验四（1）---------------" << std::endl;
	std::cout << "二叉树输入序列为：6,2,8,1,5,3,4 " << std::endl;
	BinaryTree<int> bt = { 6,2,8,1,5,3,4 };
	std::cout << "前序遍历序列：";
	bt.preOrder();
	std::cout << std::endl;
	std::cout << "------------------------------------------" << std::endl;
	system("pause");
	std::cout << std::endl;

	std::cout << "------------------实验四（2）---------------" << std::endl;
	std::cout << "输入的完全二叉树序列为：1,2,3,-1,5,6,-1,-1,-1,10,-1,-1,13" << std::endl;
	int test2[13] = { 1,2,3,-1,5,6,-1,-1,-1,10,-1,-1,13 };
	std::cout << "中序遍历为：";
	inOrder(test2, 0, 13);


	return 0;
}
