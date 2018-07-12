#include <iostream>
#include <string>
#include "Headers/HuffmanTree.h"
#include "Headers/HuffmanNode.h"
#include "Headers/LZW.h"
#include "Headers/Huffman.h"
#include "Headers/Question.h"
#include "Headers/FileUtils.h"

using namespace std;

int main()
{
	string text = "bookkeeper";
	//HuffmanTree* tree = new HuffmanTree(text);

	LZW lz;
	vector<Question> q;
	FileUtils::readFileQuestion("C:/Users/Luis/Desktop/Trabalho_ED2/Questions.csv", q);
    lz.compressQuestions(q);

	Huffman hf;

	string teste = hf.encode("bananabanabofana");

	cout << hf.decode(teste);

	hf.compressQuestions(q);

	//system("PAUSE");
	return 0;
}