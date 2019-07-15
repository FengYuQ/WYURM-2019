// huffman codec.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "huffman_codec.h"
#include <iostream>

int main()
{
	huffman_codec hc;
	hc.encoder("shujujiegouahkjbkjlblblkbhkkjbkhlbhjblhviyt##   #######.kj.jbkjhgty", "code.txt");
	std::cout << hc.decoder("code.txt");
	return 0;
}


