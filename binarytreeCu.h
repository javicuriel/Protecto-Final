//#ifndef BINARYTREE
//#define BINARYTREE

//#include "NodoB.h"

//template <class T>
//class BinaryTree {
//private:
//  NodoB<T> * root = NULL;

//public:
//  BinaryTree() {}
//  virtual ~BinaryTree();

//  //Declaracion
//  void insert(T value);
//  void insert(NodoB<T> * nodo);

//  bool empty();

//  void clear();
//  void clear(NodoB<T> * node);

//  NodoB<T> * getRoot() const;
//  void setRoot(NodoB<T> * node);

//  bool insert(NodoB<T> * parent, T value);
//  bool insert(NodoB<T> * parent, NodoB<T> * value);

//};

//template <class T>
//BinaryTree<T>::~BinaryTree()
//{
//  clear();
//}

//template <class T>
//bool BinaryTree<T>::empty()
//{
//  return root == NULL;
//}

//template <class T>
//void BinaryTree<T>::clear()
//{
//  clear(root);
//}

//template <class T>
//void BinaryTree<T>::clear(NodoB<T> * node)
//{
//  if (node) {
//    clear(node->getIzquierdo());
//    clear(node->getDerecho());

//    delete node;
//  }
//}

//template <class T>
//NodoB<T> * BinaryTree<T>::getRoot() const
//{
//  return root;
//}

//template <class T>
//void BinaryTree<T>::setRoot(NodoB<T> * node)
//{
//  if (!empty()) {
//    node->setIzquierdo(root);
//    root->setPadre(node);
//    root = node;
//  }
//  else {
//    root = node;
//  }
//}

//template <class T>
//bool BinaryTree<T>::insert(NodoB<T> * parent, T value)
//{
//  NodoB<T> * node = new NodoB<T>(value);
//  bool inserted = insert(parent, node);

//  if (!inserted) delete node;

//  return inserted;
//}

//template <class T>
//bool BinaryTree<T>::insert(NodoB<T> * parent, NodoB<T> * value)
//{
//  bool inserted = false;

//  if (empty() || !parent) {
//    setRoot(value);
//    inserted = true;
//  }
//  else {
//    if (!parent->getIzquierdo()) {
//      parent->setIzquierdo(value);
//      value->setPadre(parent);
//      inserted = true;
//    }
//    else if (!parent->getDerecho()) {
//      parent->setDerecho(value);
//      value->setPadre(parent);
//      inserted = true;
//    }
//  }

//  return inserted;
//}

////Implementacion
//template <class T>
//void BinaryTree<T>::insert(NodoB<T> * nodo) {

//  if (root == NULL) {
//    root = nodo;
//    return;
//  }
//  NodoB<T> * currentNode = root;
//  bool added = false;

//  do {
//    //recorrer el arbol
//    if (nodo->getInfo() < currentNode->getInfo()) {

//      //ir a la izquierda
//      if (currentNode->getIzquierdo() == NULL) {
//          currentNode->setIzquierdo(nodo);
//          nodo->setPadre(currentNode);
//        added = true;
//      }
//      else {
//        currentNode = currentNode->getIzquierdo();
//      }

//    }
//    if (nodo->getInfo() >= currentNode->getInfo()) {
//      //ir a la derecha
//      if (currentNode->getDerecho() == NULL) {
//        currentNode->setDerecho(nodo);
//        nodo->setPadre(currentNode);
//        added = true;
//      }
//      else {
//        currentNode = currentNode->getDerecho();
//      }

//    }


//  } while (!added);

//}

//template <class T>
//void BinaryTree<T>::insert(T value){

//        if (root == NULL){
//          root = new NodoB<T>(value);
//          return;
//        }
//        NodoB<T> * currentNode = root;
//        bool added = false;

//        do {
//          //recorrer el arbol
//          if (value < currentNode->getInfo()) {

//            //ir a la izquierda
//            if (currentNode->getIzquierdo() == NULL) {
//              currentNode->setIzquierdo(new NodoB<T>(value));
//              added = true;
//            }
//            else {
//              currentNode = currentNode->getIzquierdo();
//            }

//          }
//          if (value >= currentNode->getInfo()) {
//            //ir a la derecha
//            if (currentNode->getDerecho() == NULL) {
//              currentNode->setDerecho(new NodoB<T>(value));
//              added = true;
//            }
//            else {
//              currentNode = currentNode->getDerecho();
//            }

//          }


//        } while (!added);

//}

//#endif // BINARYTREE



