// Created by Luis on 12/07/2018.
//

#include "../Headers/Huffman.h"

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

    while(firstElement != nullptr){
        n = new Node();
        n->setLeft(getSmallerNode());
        n->setRight(getSmallerNode());
        n->setFrequency(n->getLeft()->getFrequency() + n->getRight()->getFrequency());
        lastElement->setNext(n);
        lastElement = n;
    }

    firstElement = n;
}

string Huffman::generateStringCodes(string s){

    string *code = new string;
    string::iterator it = s.begin();
    while(it != s.end()){

        if(*it >= 97 && *it <= 122){

            *code += lowerLetters[*it - 97];

        }else if(*it >= 65 && *it <= 90){

            *code += upperLetters[*it - 65];

        }else{

            if(*it == ','){

                *code += accents[0];

            }else if(*it == '.'){

                *code += accents[1];

            }else if(*it == ' '){

                *code += accents[2];

            }else if(*it == '?'){

                *code += accents[3];

            }else if(*it == '!'){

                *code += accents[4];

            }

        }
        it++;
    }
    return *code;
}


void Huffman::generateCode(string s,Node*n){

    if(n != nullptr){

        if(n->getCharacter() != 0){

            if(n->getCharacter() >= 97 && n->getCharacter() <= 122){

                lowerLetters[n->getCharacter() - 97] = s;

            }else if(n->getCharacter() >= 65 && n->getCharacter() <=90){

                upperLetters[n->getCharacter() - 65] = s;

            }else{

                if(n->getCharacter() == ','){

                    accents[0] = s;

                }else if(n->getCharacter() == '.'){

                    accents[1] = s;

                }else if(n->getCharacter() == ' '){

                    accents[2] = s;

                }else if(n->getCharacter() == '?'){

                    accents[3] = s;

                }else if(n->getCharacter() == '!'){

                    accents[4] = s;

                }

            }

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

string Huffman::encode(string text) {
    string code;

    if(firstElement == nullptr){

        string::iterator it;
        it = text.begin();

        while(it != text.end()){
            insert(*it, 1);
            it++;
        }

        generateTree();
        generateCode(code, firstElement);

        return generateStringCodes(text);
    }

    return code;
}

string Huffman::encode(vector<Question> &questionList, int n) {
    string code;
    string finalText;

    if(firstElement == nullptr){

        for(int i = 0; i < n; i++) {
            string text = questionList[i].getBody();
            string::iterator it;
            it = text.begin();

            while (it != text.end()) {
                insert(*it, 1);
                it++;
            }

            finalText += questionList[i].getBody();
        }

        generateTree();
        generateCode(code, firstElement);

        return generateStringCodes(finalText);
    }

    return code;
}


string Huffman::decode(string text){

    Node*aux = firstElement;
    string::iterator it = text.begin();
    string decode;
    while(it != text.end()+1){

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
    return decode;

}


void Huffman::compressQuestions(vector<Question> &questionList){
    string question;
    int size = questionList.size();

    //question.reserve(880000000);


    for(int i = 0; i < 10000; i++){
        question.append(questionList[i].getBody());
    }



    cout << "Teste: ";

    string codificacao = this->encode(question);

    cout << "Codificacao: " << codificacao << endl;

    cout << "Decodificacao: " << this->decode(codificacao);
}


void Huffman::deleteHuffman(Node *node) {
    if(node != nullptr){
        deleteHuffman(node->getLeft());
        deleteHuffman(node->getRight());
        delete node;
    }
}