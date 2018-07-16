// Created by Luis on 12/07/2018.
//

#include "../Headers/Huffman.h"
#include <chrono>

Huffman::Huffman() {

    firstElement = nullptr;
    lastElement = nullptr;
}

Huffman::~Huffman(){
    deleteHuffman(firstElement);
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


//Retira um Nó passado como paramêtro
void Huffman::removeNode(Node *node) {
    Node* n = firstElement;

    if(node == n){
        firstElement = n->getNext();
    }

    else{
        while(n->getNext() != node){
            n = n->getNext();
        }

        n->setNext(node->getNext());

        if(node->getNext() == nullptr){
            lastElement = n;
        }
    }
}

//Retorna o nó que possui a menor frequência
Node* Huffman::getSmallerNode() {
    Node* n1 = firstElement;
    Node* n2 = firstElement;

    if(n1->getNext() == nullptr){
        removeNode(n1);
        return n1;
    }

    else{
        while(n1 != nullptr){
            if(n1->getFrequency() < n2->getFrequency()){
                n2 = n1;
            }

            n1 = n1->getNext();
        }

    }

    if(n2 != nullptr){
        removeNode(n2);
    }

    return n2;
}


void Huffman::generateTree() {
    Node* n;
	int i;

    while(firstElement != nullptr){
		if (i % 1000000 == 0)
			cout << "Gerando arvore: " << i << "\r";
        n = new Node();
        n->setLeft(getSmallerNode());
        n->setRight(getSmallerNode());
        n->setFrequency(n->getLeft()->getFrequency() + n->getRight()->getFrequency());
        lastElement->setNext(n);
        lastElement = n;
    }

	cout << endl;
    firstElement = n;
}

string Huffman::generateStringCodes(string s){
	int i = 0;
    string *code = new string;
    string::iterator it = s.begin();
    while(it != s.end()){
		if (i % 1000000 == 0)
			cout << "Gerando codigos: " << i << "\r";
        *code += ascii[(unsigned char)*it];
        ++it;
		++i;
    }
    return *code;
}


void Huffman::generateCode(string s,Node*n){

    if(n != nullptr){

        if(n->getCharacter() != 0){
            ascii[n->getCharacter()] = s;
        }else{

            if(n->getRight() != nullptr){

                s.push_back('1');
                generateCode(s,n->getRight());
                s.erase(s.end()-1);
            }
            if(n->getLeft() != nullptr){

                s.push_back('0');
                generateCode(s,n->getLeft());
                s.erase(s.end()-1);
            }

        }

    }

}

string Huffman::encode(string &text) {

	clock_t tStart = clock();

    string code;

    if(firstElement == nullptr){

        string::iterator it;
		int i = 0;
        it = text.begin();

        while(it != text.end()){
            insert(*it, 1);
			if (i % 1000000 == 0)
				cout << "Inserindo caracteres na arvore: " << i << " / " << text.length() << "\r";
            ++it;
			++i;
        }
		cout << endl;
        generateTree();
        generateCode(code, firstElement);

		cout << endl << "Tempo gasto na compressao: " << (double)(clock() - tStart) / CLOCKS_PER_SEC << "s" << endl << endl;
        return generateStringCodes(text);
    }

    return code;
}



string Huffman::decode(string &text){
	clock_t tStart = clock();

    Node*aux = firstElement;
    string::iterator it = text.begin();
    string decode;
    while(it != text.end()){

        if(aux->getCharacter() != 0){

            decode.push_back(aux->getCharacter());
            aux = firstElement;

        }else{

            if(*it == '1'){

                aux = aux->getRight();

            }else if(*it == '0'){

                aux = aux->getLeft();

            }
            it++;

        }
    }
	cout << endl << "Tempo gasto na descompressao: " << (double)(clock() - tStart) / CLOCKS_PER_SEC << "s" << endl << endl;

    return decode;
}

void Huffman::deleteHuffman(Node *node) {
    if(node != nullptr){
        deleteHuffman(node->getLeft());
        deleteHuffman(node->getRight());
        delete node;
    }
}