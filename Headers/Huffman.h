//
// Created by Luis on 12/07/2018.
//

#ifndef TRABALHO_ED2_3_HUFFMAN_H
#define TRABALHO_ED2_3_HUFFMAN_H

#include "../Headers/Node.h"
#include "Question.h"
#include <iostream>
#include <vector>

using namespace std;

class Huffman {

public:
    Huffman();
    ~Huffman();

    string encode(string& text);
    string decode(string text);
    void generateTree();
    void compressQuestions(vector<Question> questionList);

private:
    void insert(char c, int f); //Insere o caractere
    Node* getSmallerNode(); //Retorna nó com a menor frequência
    void removeNode(Node* node);
    string generateStringCodes(string text); //Gera o código de uma string a partir da árvore
    void generateCode(string text, Node* node); //
    string lowerLetters[26];
    string upperLetters[26];
    string accents[5]; //virgula, ponto, espaço, interrogação, exclamação
    Node* firstElement;
    Node* lastElement;
    void deleteHuffman(Node* node);
};


#endif //TRABALHO_ED2_3_HUFFMAN_H
