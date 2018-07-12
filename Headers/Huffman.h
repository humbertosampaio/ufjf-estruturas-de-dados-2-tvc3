//
// Created by Luis on 12/07/2018.
//

#ifndef TRABALHO_ED2_3_HUFFMAN_H
#define TRABALHO_ED2_3_HUFFMAN_H

#include "../Headers/Node.h"
#include <iostream>
using namespace std;

class Huffman {

public:
    Huffman();
    ~Huffman();

    string encode(string text);
    string decode(string text);
    void generateTree();


private:
    void insert(char c, int f);
    string lowerLetters[26];
    string upperLetters[26];
    string accents[5]; //virgula, ponto, espaço, interrogação, exclamação
    Node* firstElement;
    Node* lastElement;
};


#endif //TRABALHO_ED2_3_HUFFMAN_H
