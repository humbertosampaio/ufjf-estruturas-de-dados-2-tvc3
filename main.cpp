#include <iostream>
#include <string>
#include "Headers/HuffmanTree.h"
#include "Headers/HuffmanNode.h"
#include "Headers/LZW.h"
#include "Headers/Huffman.h"

using namespace std;

int main()
{
	string text = "bookkeeper";
	//HuffmanTree* tree = new HuffmanTree(text);

	LZW lz;
	lz.compressText("bananabanabofana");

	Huffman hf;

	string teste = hf.encode("bananabanabofana");

	cout << hf.decode(teste);

	//system("PAUSE");
	return 0;
}