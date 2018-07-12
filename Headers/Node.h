//
// Created by Luis on 12/07/2018.
//

#ifndef TRABALHO_ED2_3_NODE_H
#define TRABALHO_ED2_3_NODE_H

class Node{

public:

    Node(){
        left = nullptr;
        right = nullptr;
        next = nullptr;
        character = 0;
    }

    Node *getLeft() const {
        return left;
    }

    void setLeft(Node *left) {
        Node::left = left;
    }

    Node *getRight() const {
        return right;
    }

    void setRight(Node *right) {
        Node::right = right;
    }

    Node *getNext() const {
        return next;
    }

    void setNext(Node *next) {
        Node::next = next;
    }

    char getCharacter() const {
        return character;
    }

    void setCharacter(char character) {
        Node::character = character;
    }

    int getFrequency() const {
        return frequency;
    }

    void setFrequency(int frequency) {
        Node::frequency = frequency;
    }

private:
    Node* left;
    Node* right;
    Node* next;
    char character;
    int frequency;

};

#endif //TRABALHO_ED2_3_NODE_H
