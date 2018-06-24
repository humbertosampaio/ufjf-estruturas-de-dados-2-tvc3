#ifndef TRABALHO_3_NODE_H
#define TRABALHO_3_NODE_H

template <class T> class Node
{
    protected:
        T value;
        Node<T>* right;
        Node<T>* left;

    public:
        Node<T>();
        Node<T>(T data);
        ~Node<T>() = default;
        void setRight(Node<T>* right);
        void setLeft(Node<T>* left);
        T getValue();

        virtual Node<T> *getRight();
        virtual Node<T> *getLeft();
        void setValue(T value);
};

#endif //TRABALHO_3_NODE_H
