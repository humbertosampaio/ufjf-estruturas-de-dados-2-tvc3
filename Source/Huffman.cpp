// Created by Luis on 12/07/2018.
//

#include "../Headers/Huffman.h"

Huffman::Huffman() {

    firstElement = nullptr;
    lastElement = nullptr;
}

//Insere o carctere no final se ele não existir, caso contrário atualiza sua frequência
void Huffman::insert(char c, int f) {

    if(firstElement == nullptr){
        firstElement = new Node();
        firstElement->setCharacter(c);
        firstElement->setFrequency(f);
        lastElement = firstElement;
    }

    else{
        Node* n = firstElement;

        while(n != nullptr && n->getCharacter() != c)
            n = n->getNext();

        if(n == nullptr){
            lastElement->setNext(new Node());
            lastElement = lastElement->getNext();
            lastElement->setCharacter(c);
            lastElement->setFrequency(f);
        }

        else{
            n->setFrequency(n->getFrequency()+1);
        }
    }

}


void Huffman::generateTree() {
    Node* n;

    while(firstElement != nullptr){

    }
}