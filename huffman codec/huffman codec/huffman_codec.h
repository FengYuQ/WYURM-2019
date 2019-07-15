#pragma once
#include <vector>
#include <map>
#include <string>
#include <utility>
#include <algorithm>
#include <iostream>
#include <fstream>

struct Node
{
	std::pair<std::string, size_t>			_key;
	Node*									_left;
	Node*								    _right;
	Node*									_parent;
	

	Node(std::pair<std::string, size_t> key,
		 Node* left = nullptr,
		 Node* right = nullptr,
		 Node* parent = nullptr) :_key(key),
								 _left(left), 
								 _right(right),
								 _parent(parent)
	{
	}

};

class huffman_codec
{
public:
	huffman_codec();
	~huffman_codec();
	void encoder(const std::string& data, const std::string& fileName);
	std::string decoder(const std::string& code_file);

private:
	void encode(const std::string& data, const std::string& fileName);
	void creat_tree(std::map<std::string, size_t> keys);
	std::string decode(Node* root, const std::string& fileName);
	std::map<std::string, size_t> readData(const std::string& data);
	void save_code_set(Node* root, const std::string code);

private:
	Node*		_root;
	std::map<std::string, std::string> code_set;
};


huffman_codec::huffman_codec():_root(nullptr)
{
}

huffman_codec::~huffman_codec()
{
}


void huffman_codec::creat_tree(std::map<std::string, size_t> keys)
{
	std::vector<Node*> nodes;
	for (auto i : keys)
	{
		Node* node = new Node(i);
		nodes.push_back(node);
	}

	int new_weight;

	while (nodes.size() != 1)
	{
		std::sort(nodes.begin(), nodes.end(),
				  [](Node* a, Node* b) -> bool
				  {
					return a->_key.second < b->_key.second;
				  });
		new_weight = nodes[0]->_key.second + nodes[1]->_key.second;
		Node* new_node = new Node(std::make_pair("", new_weight));
		new_node->_left = nodes[0];
		new_node->_right = nodes[1];
		nodes[0]->_parent = new_node;
		nodes[1]->_parent = new_node;
		nodes.erase(nodes.begin(), nodes.begin() + 2);
		nodes.push_back(new_node);
	}
	
	_root = nodes[0];
}

std::map<std::string, size_t> huffman_codec::readData(const std::string& data)
{
	std::string temp_char;
	std::map<std::string, size_t> temp_map;
	for (auto c : data)
	{
		temp_char = c;
		++temp_map[temp_char];
	}

	return temp_map;
}

void huffman_codec::save_code_set(Node* root, const std::string code)
{
	if (root)
	{
		if (root->_left == nullptr && root->_right == nullptr)
		{
			code_set.insert(std::make_pair(root->_key.first, code));
		}
		else
		{
			save_code_set(root->_left, code + "0");
			save_code_set(root->_right, code + "1");
		}
	}
}

void huffman_codec::encode(const std::string& data,const std::string& fileName)
{
	std::ofstream codeFile(fileName, std::ofstream::out);
	if (codeFile)
	{
		std::string temp_char;
		for (auto c : data)
		{
			temp_char = c;
			codeFile << code_set[temp_char];
		}
	}
	codeFile.close();
}

void huffman_codec::encoder(const std::string& data, const std::string& fileName)
{
	creat_tree(readData(data));
	save_code_set(_root, "");
	encode(data, fileName);
}

std::string huffman_codec::decoder(const std::string& fileName)
{
	return decode(_root, fileName);
}

std::string huffman_codec::decode(Node* root, const std::string& fileName)
{
	std::ifstream codeFile(fileName);
	Node* move_node = root;
	std::string temp, data, code, line;

	try {
		if (codeFile)
		{
			while (std::getline(codeFile, line))
			{
				code += line;
			}
		}
		else
		{
			throw std::runtime_error("Not fine file");
		}
		codeFile.close();
	}
	catch(std::runtime_error e)
	{
		std::cout << e.what() << std::endl;
	}
	
	for (auto c : code)
	{
		temp = c;
		if (temp == "0")
		{
			move_node = move_node->_left;
		}
		else
		{
			move_node = move_node->_right;
		}

		if (move_node->_left == nullptr && move_node->_right == nullptr)
		{
			data = data + move_node->_key.first;
			move_node = root;
		}

	}
	return data;
}