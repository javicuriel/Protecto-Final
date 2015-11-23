#include "BinarySTree.h"

#include <vector>
#include <math.h>

#include <iostream>

template <class T>
class AVLTree : public BinarySTree<T>{

public:
    AVLTree(){}
    ~AVLTree();

    void l_rotation(NodoB<T> * node);
    void r_rotation(NodoB<T> * node);
    void lr_rotation(NodoB<T> * node);
    void rl_rotation(NodoB<T> * node);
    bool isAVL(NodoB<T> * node);
    void insert(NodoB<T> * parent, NodoB<T> * node);
    void insert(NodoB<T> * node);
    void remove(T value);

    NodoB<T> * getMaxMin(NodoB<T> * node) const;
    NodoB<T> * getMaxMin() const;

};

template <class T>
AVLTree<T>::~AVLTree(){

}


template <class T>
bool AVLTree<T>::isAVL(NodoB<T> * node){

    if (node)
    {
        if (abs(this->getBalanceFactor(node)) > 1 )
        {
            return false;
        }
        return  isAVL(node->getDerecho()) && isAVL(node->getIzquierdo());
    }
    else
    {
        return true;
    }

}

template <class T>
void AVLTree<T>::r_rotation(NodoB<T> * pivot){
    //Rotar hacia la derecha al rededor del padre de node

    NodoB<T> * temp = pivot->getIzquierdo();
    if(pivot->getPadre() && pivot->getInfo() <= pivot->getPadre()->getInfo() ){
        pivot->getPadre()->setIzquierdo(temp);
    }else if (pivot->getPadre()){
        pivot->getPadre()->setDerecho(temp);
    }else{
        this->setRoot(temp);
        temp->setIndex(1);
    }

    temp->setPadre(pivot->getPadre());
    pivot->setPadre(temp);

    pivot->setIzquierdo(temp->getDerecho());

    temp->setDerecho(pivot);

    if(pivot->getIzquierdo())
        pivot->getIzquierdo()->setPadre(pivot);

}

template <class T>
void AVLTree<T>::l_rotation(NodoB<T> * pivot){
    //Rotar hacia la izquierda alrededor del padre de node
    NodoB<T> * temp = pivot->getDerecho();

    if(pivot->getPadre() && pivot->getInfo() <= pivot->getPadre()->getInfo() ){
        pivot->getPadre()->setIzquierdo(temp);
    }else if (pivot->getPadre()){
        pivot->getPadre()->setDerecho(temp);
    }else{
        this->setRoot(temp);
        temp->setIndex(1);
    }

    temp->setPadre(pivot->getPadre());
    pivot->setPadre(temp);

    pivot->setDerecho(temp->getIzquierdo());

    temp->setIzquierdo(pivot);

    if(pivot->getDerecho())
        pivot->getDerecho()->setPadre(pivot);

    //std::cout << "Hola" << std::endl;
}

template <class T>
void AVLTree<T>::lr_rotation(NodoB<T> * pivot){
    //Rotar hacia la izquierda alrededor de node y rotar hacia la derecha alrededor del padre de node
    NodoB<T> * temp = pivot->getDerecho();

    l_rotation(pivot);


    r_rotation(temp->getPadre());

}

template <class T>
void AVLTree<T>::rl_rotation(NodoB<T> * pivot){
    //Rotar hacia la derecha alrededor de node y rotar hacia la izquierda alrededor del padre de node
    NodoB<T> * temp = pivot->getIzquierdo();

    r_rotation(pivot);


    l_rotation(temp->getPadre());

}

template <class T>
void AVLTree<T>::insert(NodoB<T> * parent, NodoB<T> * node){
    if (this->empty())
    {
        this->setRoot(node);
        //se le asigna un index de 1 a la raiz
        node->setIndex(1);


    }
    else
    {
        if(node->getInfo() < parent->getInfo())
        {

            if (parent->getIzquierdo() == NULL)
            {
                parent->setIzquierdo(node);

                node->setPadre(parent);


            }
            else
            {
                insert(parent->getIzquierdo(), node);
            }
        }
        else if(node->getInfo() >= parent->getInfo())
        {
            if (parent->getDerecho() == NULL)
            {
                parent->setDerecho(node);

                node->setPadre(parent);


            }
            else
            {
                insert(parent->getDerecho(), node);
            }
        } else {
            return;
        }
        //     std::cout<<"L"<<std::endl;

        if(this->getBalanceFactor(parent->getPadre()) == -2 && this->getBalanceFactor(parent->getPadre()->getIzquierdo())== -1){

            r_rotation(parent->getPadre());
            //std::cout<<"R"<<std::endl;

        }
        if(this->getBalanceFactor(parent->getPadre()) == -2 && this->getBalanceFactor(parent->getPadre()->getIzquierdo())== 1){

            lr_rotation(parent);

            std::cout<<"LR - Doble Derecha"<<std::endl;
        }
        if(this->getBalanceFactor(parent->getPadre()) == 2 && this->getBalanceFactor(parent->getPadre()->getDerecho())== 1){

            l_rotation(parent->getPadre());


            //std::cout<<"L"<<std::endl;
        }
        if( (this->getBalanceFactor(parent->getPadre()) == 2 && this->getBalanceFactor(parent->getPadre()->getDerecho())== -1)){

            rl_rotation(parent);

            std::cout<<"RL - Doble Izquierda"<<std::endl;
        }

    }


}


//template <class T>
//void AVLTree<T>::insert(T value){
//    NodoB<T> * node = new NodoB<T>(value);
//     insert(this->root, node);
//}

template <class T>
void AVLTree<T>::insert(NodoB<T> * node){
    insert(this->root, node);
    this->bfs();
    this->scene->addItem(node);
}

template <class T>
void AVLTree<T>::remove(T value){
    NodoB<T> * node = this->search(value);

    if(node){
        NodoB<T> * parent = node->getPadre();
        NodoB<T> * nnode = getMaxMin(node);
        if(nnode){
            nnode->setDerecho(node->getDerecho());
            if(nnode->getDerecho())
                nnode->getDerecho()->setPadre(nnode);
            nnode->getPadre()->setDerecho(nnode->getIzquierdo());
            nnode->setPadre(node->getPadre());


            if(node->getIzquierdo() == nnode){
                if(!nnode->getIzquierdo())
                    nnode->setIzquierdo(NULL);
            }
            else{
                nnode->setIzquierdo(node->getIzquierdo());
            }
        }

        if(!node->getPadre()){
            BinaryTree<T>::setRoot(nnode);
            //nnode->setIndex(1);
        }else if(node->getInfo() <= node->getPadre()->getInfo()){
            node->getPadre()->setIzquierdo(nnode);
        } else{
            node->getPadre()->setDerecho(nnode);
        }

        node->borrar(this->scene);
        this->bfs();



        if(this->getBalanceFactor(parent) == -2 && this->getBalanceFactor(parent->getIzquierdo()) == -1){
            r_rotation(parent);
            //        std::cout<<"R"<<std::endl;
        }
        if(this->getBalanceFactor(parent) == -2 && this->getBalanceFactor(parent->getIzquierdo())== 1){
            lr_rotation(parent->getIzquierdo());
            //        std::cout<<"LR"<<std::endl;
        }
        if(this->getBalanceFactor(parent) == 2 && this->getBalanceFactor(parent->getDerecho())== 1){
            l_rotation(parent);
            //        std::cout<<"L"<<std::endl;
        }
        if( (this->getBalanceFactor(parent) == 2 && this->getBalanceFactor(parent->getDerecho())== -1)){
            rl_rotation(parent->getDerecho());
            //        std::cout<<"RL"<<std::endl;
        }
        if(parent)
            parent =  parent->getPadre();


        if(this->getBalanceFactor(nnode) == -2 && this->getBalanceFactor(nnode->getIzquierdo()) == -1){
            r_rotation(nnode);
            //            std::cout<<"R"<<std::endl;
        }
        if(this->getBalanceFactor(nnode) == -2 && this->getBalanceFactor(nnode->getIzquierdo())== 1){
            lr_rotation(nnode->getIzquierdo());
            //            std::cout<<"LR"<<std::endl;
        }
        if(this->getBalanceFactor(nnode) == 2 && this->getBalanceFactor(nnode->getDerecho())== 1){
            l_rotation(nnode);
            //            std::cout<<"L"<<std::endl;
        }
        if( (this->getBalanceFactor(nnode) == 2 && this->getBalanceFactor(nnode->getDerecho())== -1)){
            rl_rotation(nnode->getDerecho());
            //            std::cout<<"RL"<<std::endl;
        }

    }

}

template <class T>
NodoB<T> * AVLTree<T>::getMaxMin() const
{
    return getMaxMin(this->root);
}


template <class T>
NodoB<T> * AVLTree<T>::getMaxMin(NodoB<T> * node) const
{
    if (node)
    {
        NodoB<T> * workingNode = node->getIzquierdo();
        if(workingNode){
            while (workingNode->getDerecho() != NULL)
            {
                workingNode = workingNode->getDerecho();
            }
            return workingNode;
        }
        return NULL;

    } else{
        return NULL;
    }

}


