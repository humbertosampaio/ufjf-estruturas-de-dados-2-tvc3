#include <string>
#include "../Headers/HuffmanNode.h"

using namespace std;

HuffmanNode::HuffmanNode()
{
	this->key = '\0';
	this->path = "";
	this->frequency = 1;
	this->father = nullptr;
	this->left = nullptr;
	this->right = nullptr;
}

HuffmanNode::HuffmanNode(char key)
{
	this->key = key;
	this->path = "";
	this->frequency = 1;
	this->father = nullptr;
	this->right = nullptr;
	this->left = nullptr;
}

HuffmanNode::HuffmanNode(char key, string path)
{
	this->key = key;
	this->path = path;
	this->frequency = 1;
	this->father = nullptr;
	this->right = nullptr;
	this->left = nullptr;
}

HuffmanNode* HuffmanNode::getFather()
{
	return father;
}

void HuffmanNode::setFather(HuffmanNode* father)
{
	this->father = father;
}

HuffmanNode* HuffmanNode::getRight()
{
	return right;
}

void HuffmanNode::setRight(HuffmanNode* node)
{
	this->right = node;
}

HuffmanNode* HuffmanNode::getLeft()
{
	return left;
}

void HuffmanNode::setLeft(HuffmanNode* node)
{
	this->left = node;
}

int HuffmanNode::getFrequency()
{
	return frequency;
}

void HuffmanNode::setFrequency(int frequency)
{
	this->frequency = frequency;
}

void HuffmanNode::incrementFrequency()
{
	frequency++;
}

char HuffmanNode::getKey()
{
	return key;
}

void HuffmanNode::setKey(char key)
{
	this->key = key;
}

string HuffmanNode::getPath()
{
	return path;
}

void HuffmanNode::setPath(string path)
{
	this->path = path;
}