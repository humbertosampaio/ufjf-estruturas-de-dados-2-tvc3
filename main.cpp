#include <iostream>
#include <string>
#include "Headers/HuffmanTree.h"
#include "Headers/HuffmanNode.h"
#include "Headers/LZW.h"
#include "Headers/Huffman.h"
#include "Headers/Question.h"
#include "Headers/FileUtils.h"
#include "Headers/TrieTernaria.h"

using namespace std;

int main()
{
	string text = "bookkeeper";
	//HuffmanTree* tree = new HuffmanTree(text);

	LZW lz;

	vector<Question> q;
	//FileUtils::readFileQuestion("/home/edson/pythonquestions/Questions.csv", q);
    lz.compressText("bananabanabofana");
    //lz.compressQuestions(q);

	Huffman hf;
    /*
	string teste = hf.encode(q[0].getBody());
    cout << teste;
	cout << hf.decode(teste);*/
	//hf.compressQuestions(q);
	//system("PAUSE");
	return 0;
}