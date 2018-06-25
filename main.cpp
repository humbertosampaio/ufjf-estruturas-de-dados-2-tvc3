#include <iostream>
#include <string>
#include "Headers/HuffmanTree.h"
#include "Headers/HuffmanNode.h"

using namespace std;

int main()
{
	string text = "bookkeeper";
	HuffmanTree* tree = new HuffmanTree(text);


	system("PAUSE");
	return 0;
}