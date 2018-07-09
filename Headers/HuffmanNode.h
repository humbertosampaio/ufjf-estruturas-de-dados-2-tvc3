#ifndef TRABALHO_3_HUFFMANNODE_H
#define TRABALHO_3_HUFFMANNODE_H

#include <iostream>

using namespace std;

class HuffmanNode
{
	protected:
	char key;
	string path;
	int frequency;
	HuffmanNode* father;
	HuffmanNode* right;
	HuffmanNode* left;

	public:
	HuffmanNode();
	HuffmanNode(char key);
	HuffmanNode(char key, string path);
	~HuffmanNode() = default;

	HuffmanNode *getFather();
	void setRight(HuffmanNode* father);

	HuffmanNode *getRight();
	void setFather(HuffmanNode* right);

	HuffmanNode *getLeft();
	void setLeft(HuffmanNode* left);
	
	int getFrequency();
	void setFrequency(int frequency);
	void incrementFrequency();

	char getKey();
	void setKey(char key);

	string getPath();
	void setPath(string path);
};

#endif //TRABALHO_3_HUFFMANNODE_H
