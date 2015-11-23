#include "nodoB.h"
#include <iomanip>
#include <iostream>
#include <QPropertyAnimation>
#include <QGraphicsScene>

template <class T>
class BinaryTree {
protected:
    NodoB<T> * root = NULL;
    QGraphicsScene *scene;

public:
    BinaryTree() {}
    virtual ~BinaryTree();


    void bfs();
    void animacionMov(qreal & xInicial, qreal & yInicial, qreal & xFinal, qreal & yFinal, NodoB<T> * nodo);

    void setScene(QGraphicsScene *x);
    bool empty();

    void clear();
    void clear(NodoB<T> * node);

    NodoB<T> * getRoot() const;
    void setRoot(NodoB<T> * node);


    virtual void insert(T value);
    virtual void insert(NodoB<T> * parent, NodoB<T> * node);


    void preOrder() const;
    void preOrder(NodoB<T> * node) const;


    void inOrder() const;
    void inOrder(NodoB<T> * node) const;
    void reverseInOrder() const;
    void reverseInOrder(NodoB<T> * node) const;


    void postOrder() const;
    void postOrder(NodoB<T> * node) const;

    void isLeaf() const;
    void isLeaf(NodoB<T> * node) const;

    void ancestors(NodoB<T> * node) const;

    int getHeight() const;
    int getHeight(NodoB<T> * node) const ;

    int getDepth() const;
    int getDepth(NodoB<T> * node) const;

    int getLevel() const;
    int getLevel(NodoB<T> * node) const;

    int getBalanceFactor() const;
    int getBalanceFactor(NodoB<T> * node) const ;


    void prettyPrint(NodoB<T>* p, int indent)
    {
        if(p != NULL) {
            if(p->getDerecho()) {
                prettyPrint(p->getDerecho(), indent+4);
            }
            if (indent) {
                std::cout << std::setw(indent) << ' ';
            }
            if (p->getDerecho()) std::cout<<" /\n" << std::setw(indent) << ' ';
            std::cout<< p->getInfo() << "\n ";
            if(p->getIzquierdo()) {
                std::cout << std::setw(indent) << ' ' <<" \\\n";
                prettyPrint(p->getIzquierdo(), indent+4);
            }

        }
    }

};


template <class T>
BinaryTree<T>::~BinaryTree()
{
    clear();
}

template <class T>
bool BinaryTree<T>::empty()
{
    return root == NULL;
}

template <class T>
void BinaryTree<T>::clear()
{
    clear(root);
    scene->update();
}

template <class T>
void BinaryTree<T>::clear(NodoB<T> * node)
{
    if (node) {
        clear(node->getIzquierdo());
        clear(node->getDerecho());

        node->borrar(scene);
    }
}

template <class T>
NodoB<T> * BinaryTree<T>::getRoot() const
{
    return root;
}

template <class T>
void BinaryTree<T>::setRoot(NodoB<T> * node)
{
    root = node;
}




template <class T>
void BinaryTree<T>::insert(T value){
    NodoB<T> * node = new NodoB<T>(value);
    insert(this->root, node);
}

template <class T>
void BinaryTree<T>::insert(NodoB<T> * parent, NodoB<T> * node){
    if (empty())
    {
        setRoot(node);
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
        else
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
        }
    }
}



template <class T>
void BinaryTree<T>::preOrder() const
{
    preOrder(root);
}

template <class T>
void BinaryTree<T>::preOrder(NodoB<T> * node) const
{
    if (node) {
        /* Procesar el nodo */
        std::cout << *node << std::endl;

        /* Invocar a los hijos */
        preOrder(node->getIzquierdo());
        preOrder(node->getDerecho());

    }
}

template <class T>
void BinaryTree<T>::inOrder() const
{
    inOrder(root);
}

template <class T>
void BinaryTree<T>::inOrder(NodoB<T> * node) const
{
    if (node) {

        /* Invocar al hijo izquierdo */
        inOrder(node->getIzquierdo());

        /* Procesar el nodo */
        std::cout << *node << std::endl;

        /* Invocar al hijo derecho */
        inOrder(node->getDerecho());
    }
}

template <class T>
void BinaryTree<T>::reverseInOrder() const{
    reverseInOrder(root);
    
}
template <class T>
void BinaryTree<T>::reverseInOrder(NodoB<T> * node) const{
    
    if (node) {
        reverseInOrder(node->getDerecho());
        std::cout << *node << std::endl;
        reverseInOrder(node->getIzquierdo());
    }
}

template <class T>
void BinaryTree<T>::postOrder() const
{
    postOrder(root);
}

template <class T>
void BinaryTree<T>::postOrder(NodoB<T> * node) const
{
    if (node) {
        /* Invocar a los hijos */
        postOrder(node->getIzquierdo());
        postOrder(node->getDerecho());

        /* Procesar el nodo */
        std::cout << *node << std::endl;
    }
}

template <class T>
void BinaryTree<T>::isLeaf() const
{
    isLeaf(root);
}

template <class T>
void BinaryTree<T>::isLeaf(NodoB<T> * node) const
{
    if (node) {
        if (!node->getIzquierdo() && !node->getDerecho()) {
            std::cout << *node << std::endl;
        }
        else {
            isLeaf(node->getIzquierdo());
            isLeaf(node->getDerecho());
        }
    }
}

template <class T>
void BinaryTree<T>::ancestors(NodoB<T> * node) const
{
    if (node) {
        std::cout << *node << " -> ";
        ancestors(node->getPadre());
    }
}

template <class T>
int BinaryTree<T>::getHeight() const
{
    return getHeight(root);
}

template <class T>
int BinaryTree<T>::getHeight(NodoB<T> * node) const
{
    if (node == NULL)
    {
        return -1;
    }
    else
    {
        int leftCount = getHeight(node->getIzquierdo());
        int rightCount = getHeight(node->getDerecho());
        
        if (leftCount <= rightCount)
        {
            return rightCount +1;
        }
        else
        {
            return leftCount +1;
        }
    }
}

template <class T>
int BinaryTree<T>::getLevel() const
{
    return getLevel(root);
}

template <class T>
int BinaryTree<T>::getLevel(NodoB<T> * node) const
{
    if (node == root)
    {
        return 0;
    }
    if (node == NULL)
    {
        return 0;
    }
    else
    {
        return getLevel(node->getPadre()) + 1;
    }
}

template <class T>
int BinaryTree<T>::getDepth() const
{
    return getDepth(root);
}

template <class T>
int BinaryTree<T>::getDepth(NodoB<T> * node) const
{
    return getLevel(node);
}

template <class T>
int BinaryTree<T>::getBalanceFactor() const
{
    return getBalanceFactor(root);
}

template <class T>
int BinaryTree<T>::getBalanceFactor(NodoB<T> * node) const
{
    if (node)
    {
        return getHeight(node->getDerecho()) - getHeight(node->getIzquierdo());
    }
    return 0;
}

template <class T>
void BinaryTree<T>::setScene(QGraphicsScene *x){
    scene = x;
}

template <class T>
void BinaryTree<T>::bfs() {
    std::vector<NodoB<T> *> cola;
    int nivel = 0; //nivel del nodo
    int index = 0; //index del nodo
    qreal xInicial = 0.0;
    qreal yInicial = 0.0;

    cola.push_back(this->root);

    while(!cola.empty()){
        NodoB<T> * temp = cola[0];
        xInicial = temp->getX();
        yInicial = temp->getY();

        temp->borrarEdges(this->scene);
        nivel = this->getLevel(temp);//se obtiene el nivel del nodo
        index = temp->getIndex();//se obtiene el indice del nodo

        //parte de arriba de la formula para obtener la posicion en x.
        //index * widthOfWindow

        qreal numerador = index * (this->scene->width()+100);

        //parte de abajo de la formula para obtener la posicion en x.
        //(2^nivel) + 1
        qreal denominador = pow(2.0, double(nivel)) + 1;
        //division de la parte de arriba entre la de abajo para obtener
        //la posicion en x que va a llevar el nodo
        qreal x = numerador / denominador;

        //altura que va a llevar el nodo
        qreal y = 0.0;

        //cuando existe un padre entra al if
        if (temp->getPadre() != NULL){
            //temp->getPadre()->borrarEdges();
            //se toma la altura del padre
            qreal altura = temp->getPadre()->getY();
            //se le suma 50 a la altura anterior y se le asigna al nodo
            y = altura + 50;
            this->scene->addItem(new Edge<T>(temp, temp->getPadre()));
        }

        //se asignan las coordenadas del nodo para que se dibuje correctamente
        temp->setCoordinates(x,y);

        animacionMov(xInicial, yInicial, x, y, temp);

        cola.erase(cola.begin());

        if(temp->getIzquierdo()!= NULL){
            //temp->getIzquierdo()->borrarEdges();
            cola.push_back(temp->getIzquierdo());
            //se agarra el index del padre
            int index = temp->getIndex();
            //se calcula y se asigna el index que le corresponde al nodo izquierdo
            temp->getIzquierdo()->setIndex((index * 2) - 1);


        }
        if(temp->getDerecho()!= NULL){
            //temp->getDerecho()->borrarEdges();
            cola.push_back(temp->getDerecho());
            //se agarra el index del padre
            int index = temp->getIndex();
            //se calcula y se asigna el index que le corresponde al nodo derecho
            temp->getDerecho()->setIndex(index * 2);

        }


    }

}

template <class T>
void BinaryTree<T>::animacionMov(qreal & xInicial, qreal & yInicial, qreal & xFinal, qreal & yFinal, NodoB<T> * nodo)
{
    // Aqui crea la animación
    QPointF puntoA = QPointF(xInicial, yInicial);
    QPointF puntoB = QPointF(xFinal, yFinal);

    QPropertyAnimation * animation = new QPropertyAnimation(nodo, "pos");
    animation->setDuration(500); //2 Segundos
    animation->setStartValue(puntoA);
    animation->setEndValue(puntoB);
    animation->start();
}





