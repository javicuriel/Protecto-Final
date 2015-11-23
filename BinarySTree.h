#include "BinaryTree.h"

template <class T>
class BinarySTree: public BinaryTree<T> {
    
    
public:
    BinarySTree();
    ~BinarySTree();
    
    NodoB<T> * search(const T value) const;
    NodoB<T> * search(const T value, NodoB<T> * node) const;
};

template <class T>
BinarySTree<T>::BinarySTree() : BinaryTree<T>(){}

template <class T>
BinarySTree<T>::~BinarySTree()
{
    
}

template <class T>
NodoB<T> * BinarySTree<T>::search(const T value) const{
    return search(value, this->root);

}

template <class T>
NodoB<T> * BinarySTree<T>::search(const T value, NodoB<T> * node)const {
    if (node == NULL)
    {
        return NULL;
    }
    else {
        T value2 = node->getInfo();
        if (value == value2)
        {
            return node;
        }
        else if (value < value2)
        {
            return search(value, node->getIzquierdo());
        }
        else {
            return search(value, node->getDerecho());
        }
    }
}
