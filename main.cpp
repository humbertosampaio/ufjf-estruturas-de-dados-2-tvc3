#include <iostream>
#include <string>
#include "Headers/HuffmanTree.h"
#include "Headers/HuffmanNode.h"
#include <LZW.h>
using namespace std;

int main()
{
	string text = "bookkeeper";
	//HuffmanTree* tree = new HuffmanTree(text);

	LZW lz;
	lz.compressText("bananabanabofana");

	//system("PAUSE");
	return 0;
}