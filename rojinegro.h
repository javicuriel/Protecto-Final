#ifndef ROJINEGRO
#define ROJINEGRO

#include "avl.h"
#include <vector>
#include <math.h>
#include <iostream>


template <class T>
class Rojinegro : public AVLTree<T> {

public:
  Rojinegro() {}

  NodoB<T> * abuelo(NodoB<T> * nodo);
  NodoB<T> * tio(NodoB<T> * nodo);
  NodoB<T> * hermano(NodoB<T> * nodo);

  NodoB<T> * nodoMaximo(NodoB<T> * nodo);

  void verificar(NodoB<T> * raiz);
  void checarPropiedadUno(NodoB<T> * nodo);
  void checarPropiedadTres(NodoB<T> * nodo);

  std::string color(NodoB<T> * nodo);

  void rotarIzq(Rojinegro<T> * arbol, NodoB<T> * nodo);
  void rotarDer(Rojinegro<T> * arbol, NodoB<T> * nodo);

  void RBinsert(NodoB<T> * nodo);
  void insert(NodoB<T> * parent, NodoB<T> * node);

  void insertarCasoUno(Rojinegro<T> * arbol, NodoB<T> * nodo);
  void insertarCasoDos(Rojinegro<T> * arbol, NodoB<T> * nodo);
  void insertarCasoTres(Rojinegro<T> * arbol, NodoB<T> * nodo);
  void insertarCasoCuatro(Rojinegro<T> * arbol, NodoB<T> * nodo);
  void insertarCasoCinco(Rojinegro<T> * arbol, NodoB<T> * nodo);

  void RBdelete(T valor);
  void borrarCasoUno(Rojinegro * arbol, NodoB<T> * nodo);
  void borrarCasoDos(Rojinegro * arbol, NodoB<T> * nodo);
  void borrarCasoTres(Rojinegro * arbol, NodoB<T> * nodo);
  void borrarCasoCuatro(Rojinegro * arbol, NodoB<T> * nodo);
  void borrarCasoCinco(Rojinegro * arbol, NodoB<T> * nodo);
  void borrarCasoSeis(Rojinegro * arbol, NodoB<T> * nodo);

  void bfs();

};

template <class T>
NodoB<T> * Rojinegro<T>::abuelo(NodoB<T> * nodo)
{
  if(nodo != NULL && nodo->getPadre() != NULL)
    return nodo->getPadre()->getPadre();
  else
    return NULL;
}

template <class T>
NodoB<T> * Rojinegro<T>::tio(NodoB<T> * nodo)
{
  NodoB<T> * abu = abuelo(nodo);

  if(abu == NULL)
    return NULL;
  else if(nodo->getPadre() == abu->getIzquierdo())
    return abu->getDerecho();
  else
    return abu->getIzquierdo();
}

template <class T>
NodoB<T> * Rojinegro<T>::hermano(NodoB<T> * nodo)
{
  if(nodo != NULL && nodo->getPadre() != NULL)
  {
    if(nodo == nodo->getPadre()->getIzquierdo())
      return nodo->getPadre()->getDerecho();
    else
      return nodo->getPadre()->getIzquierdo();
  }
  else
    return NULL;
}

template <class T>
NodoB<T> * Rojinegro<T>::nodoMaximo(NodoB<T> * nodo)
{
  while (nodo->getDerecho() != NULL)
  {
    nodo = nodo->getDerecho();
  }
  return nodo;
}

template <class T>
void Rojinegro<T>::verificar(NodoB<T>* raiz)
{
  checarPropiedadUno(raiz);
  checarPropiedadTres(raiz);
}

template <class T>
void Rojinegro<T>::checarPropiedadUno(NodoB<T> * nodo)
{
  if(nodo == NULL)
    return;

  checarPropiedadUno(nodo->getIzquierdo());
  checarPropiedadUno(nodo->getDerecho());
}

template <class T>
void Rojinegro<T>::checarPropiedadTres(NodoB<T> * nodo)
{
  if (nodo == NULL)
    return;


  checarPropiedadTres(nodo->getIzquierdo());
  checarPropiedadTres(nodo->getDerecho());
}

template <class T>
std::string Rojinegro<T>::color(NodoB<T> * nodo)
{
  if(nodo == NULL)
    return "negro";
  else
    return nodo->getColor();
}

template <class T>
void Rojinegro<T>::rotarIzq(Rojinegro<T> * arbol, NodoB<T> * node_x)
{
  NodoB<T> *node_y;

  if(node_x->getDerecho() == NULL){
    return;
  }

  node_y = node_x->getDerecho();

  if(node_y->getIzquierdo() != NULL){
    node_y->getIzquierdo()->setPadre(node_x);
    node_x->setDerecho(node_y->getIzquierdo());
  }

  node_y->setPadre(node_x->getPadre());

  if(node_x->getPadre() == NULL){
    this->setRoot(node_y);
    node_y->setIndex(1);
  }else if(node_x == node_x->getPadre()->getIzquierdo()){
    node_x->getPadre()->setIzquierdo(node_y);
  }else{
    node_x->getPadre()->setDerecho(node_y);
  }

  node_x->setDerecho(node_y->getIzquierdo());
  node_y->setIzquierdo(node_x);
  node_x->setPadre(node_y);

}

template <class T>
void Rojinegro<T>::rotarDer(Rojinegro<T> * arbol, NodoB<T> * node_y)
{
  NodoB<T> *node_x;

  if(node_y->getIzquierdo() == NULL){
    return;
  }

  node_x = node_y->getIzquierdo();

  if(node_x->getDerecho() != NULL){
    node_x->getDerecho()->setPadre(node_y);
    node_y->setIzquierdo(node_x->getDerecho());
  }

  node_x->setPadre(node_y->getPadre());

  if(node_y->getPadre() == NULL){
    this->setRoot(node_x);
    node_x->setIndex(1);
  }else if(node_y == node_y->getPadre()->getIzquierdo()){
    node_y->getPadre()->setIzquierdo(node_x);
  }else{
    node_y->getPadre()->setDerecho(node_x);
  }

  node_y->setIzquierdo(node_x->getDerecho());
  node_x->setDerecho(node_y);
  node_y->setPadre(node_x);
}

template <class T>
void Rojinegro<T>::insert(NodoB<T> * parent, NodoB<T> * node){

    if (this->empty()) {
        this->setRoot(node);
        node->setIndex(1);
        //se le asigna un index de 1 a la raiz
        node->setIndex(1);
    }
    else {
        if(node->getInfo() < parent->getInfo()) {
            if (parent->getIzquierdo() == NULL) {
                parent->setIzquierdo(node);
                node->setPadre(parent);
            }
            else {
                 insert(parent->getIzquierdo(), node);
            }
        }
        else if(node->getInfo() >= parent->getInfo()) {
            if (parent->getDerecho() == NULL) {
                parent->setDerecho(node);
                node->setPadre(parent);
            }
            else{
                insert(parent->getDerecho(), node);
            }
        }
        else {
            return;
        }

    }
}

template <class T>
void Rojinegro<T>::RBinsert(NodoB<T> * nodo)
{

  insert(this->root, nodo);
  nodo->setColor("rojo");
  insertarCasoUno(this, nodo);
  verificar(this->getRoot());
  this->bfs();
  this->scene->addItem(nodo);

}

template <class T>
void Rojinegro<T>::insertarCasoUno(Rojinegro<T> * arbol, NodoB<T> * nodo)
{
  if(nodo->getPadre() == NULL)
    nodo->setColor("negro");
  else
    insertarCasoDos(this, nodo);
}

template <class T>
void Rojinegro<T>::insertarCasoDos(Rojinegro<T> * arbol, NodoB<T> * nodo)
{
  if(nodo->getPadre()->getColor() == "negro")
    return;
  else
    insertarCasoTres(this, nodo);
}

template <class T>
void Rojinegro<T>::insertarCasoTres(Rojinegro<T> * arbol, NodoB<T> * nodo)
{
  if(color(tio(nodo)) == "rojo")
  {
    nodo->getPadre()->setColor("negro");
    tio(nodo)->setColor("negro");
    abuelo(nodo)->setColor("rojo");
    insertarCasoUno(arbol, abuelo(nodo));
  }
  else
  {
    insertarCasoCuatro(arbol, nodo);
  }
}

template <class T>
void Rojinegro<T>::insertarCasoCuatro(Rojinegro<T> * arbol, NodoB<T> * nodo)
{
  if(nodo == nodo->getPadre()->getDerecho() && nodo->getPadre() == abuelo(nodo)->getIzquierdo())
  {
    rotarIzq(arbol, nodo->getPadre());
    nodo = nodo->getIzquierdo();
  }
  else if(nodo == nodo->getPadre()->getIzquierdo() && nodo->getPadre() == abuelo(nodo)->getDerecho())
  {
    rotarDer(arbol, nodo->getPadre());
    nodo = nodo->getDerecho();
  }
  insertarCasoCinco(arbol, nodo);
}

template <class T>
void Rojinegro<T>::insertarCasoCinco(Rojinegro<T> * arbol, NodoB<T> * nodo)
{
  nodo->getPadre()->setColor("negro");
  abuelo(nodo)->setColor("rojo");
  if (nodo == nodo->getPadre()->getIzquierdo() && nodo->getPadre() == abuelo(nodo)->getIzquierdo())
  {
    rotarDer(arbol, abuelo(nodo));
  }
  else
  {
    rotarIzq(arbol, abuelo(nodo));
  }
}

template <class T>
void Rojinegro<T>::RBdelete(T valor)
{
  NodoB<T> * hijo;
  NodoB<T> * nodo;
  nodo = this->search(valor);
  if (nodo == NULL)
    return;

  if (nodo->getIzquierdo() != NULL && nodo->getDerecho() != NULL)
  {
    NodoB<T> * pred = nodoMaximo(nodo->getIzquierdo());
    nodo->setInfo(pred->getInfo());
    nodo = pred;
  }
  hijo = nodo->getDerecho() == NULL ? nodo->getIzquierdo()  : nodo->getDerecho();
  if (color(nodo) == "negro")
  {
    nodo->getColor() = color(hijo);
    borrarCasoUno(this, nodo);
  }


  if (nodo->getPadre() == NULL)
  {
    this->setRoot(hijo);
    hijo->setIndex(1);
  }
  else
  {
    if (nodo == nodo->getPadre()->getIzquierdo())
      nodo->getPadre()->setIzquierdo(hijo);
    else
      nodo->getPadre()->setDerecho(hijo);
  }
  if (hijo != NULL)
  {
    hijo->setPadre(nodo->getPadre());
  }
  nodo->borrar(this->scene);
  bfs();
  verificar(this->getRoot());
}

template <class T>
void Rojinegro<T>::borrarCasoUno(Rojinegro<T> * arbol, NodoB<T> * nodo)
{
  if(nodo->getPadre() == NULL)
    return;
  else
    borrarCasoDos(this, nodo);
}

template <class T>
void Rojinegro<T>::borrarCasoDos(Rojinegro<T> * arbol, NodoB<T> * nodo)
{
  if (color(hermano(nodo)) == "rojo")
  {
    nodo->getPadre()->setColor("rojo");
    hermano(nodo)->setColor("negro");
    if (nodo == nodo->getPadre()->getIzquierdo())
      rotarIzq(this, nodo->getPadre());
    else
      rotarDer(this, nodo->getPadre());
  }
  borrarCasoTres(this, nodo);
}

template <class T>
void Rojinegro<T>::borrarCasoTres(Rojinegro<T> * arbol, NodoB<T> * nodo)
{
  if (color(nodo->getPadre()) == "negro" && color(hermano(nodo)) == "negro" &&
      color(hermano(nodo)->getIzquierdo()) == "negro" && color(hermano(nodo)->getDerecho()) == "negro")
  {
    hermano(nodo)->setColor("rojo");
    borrarCasoUno(this, nodo->getPadre());
  }
  else
    borrarCasoCuatro(this, nodo);
}

template <class T>
void Rojinegro<T>::borrarCasoCuatro(Rojinegro<T> * arbol, NodoB<T> * nodo)
{
  if (color(nodo->getPadre()) == "rojo" && color(hermano(nodo)) == "negro" &&
      color(hermano(nodo)->getIzquierdo()) == "negro" && color(hermano(nodo)->getDerecho()) == "negro")
  {
    hermano(nodo)->setColor("rojo");
    nodo->getPadre()->setColor("negro");
  }
  else
    borrarCasoCinco(this, nodo);
}

template <class T>
void Rojinegro<T>::borrarCasoCinco(Rojinegro<T> * arbol, NodoB<T> * nodo)
{
  if (nodo == nodo->getPadre()->getIzquierdo() && color(hermano(nodo)) == "negro" &&
      color(hermano(nodo)->getIzquierdo()) == "rojo" && color(hermano(nodo)->getDerecho()) == "negro")
  {
    hermano(nodo)->setColor("rojo");
    hermano(nodo)->getIzquierdo()->setColor("negro");
    rotarDer(this, hermano(nodo));
  }
  else if (nodo == nodo->getPadre()->getDerecho() && color(hermano(nodo)) == "negro" &&
           color(hermano(nodo)->getDerecho()) == "rojo" && color(hermano(nodo)->getIzquierdo()) == "negro")
  {
    hermano(nodo)->setColor("rojo");
    hermano(nodo)->getDerecho()->setColor("negro");
    rotarIzq(this, hermano(nodo));
  }
  borrarCasoSeis(this, nodo);
}

template <class T>
void Rojinegro<T>::borrarCasoSeis(Rojinegro<T> * arbol, NodoB<T> * nodo)
{
  hermano(nodo)->setColor(color(nodo->getPadre()));
  nodo->getPadre()->setColor("negro");
  if (nodo == nodo->getPadre()->getIzquierdo())
  {
    hermano(nodo)->getDerecho()->setColor("negro");
    rotarIzq(this, nodo->getPadre());
  }
  else
  {
    hermano(nodo)->getIzquierdo()->setColor("negro");
    rotarDer(this, nodo->getPadre());
  }
}

template <class T>
void Rojinegro<T>::bfs() {
    std::vector<NodoB<T> *> cola;
    int nivel = 0; //nivel del nodo
    int index = 0; //index del nodo

    cola.push_back(this->root);
    while(!cola.empty()){
        NodoB<T> * temp = cola[0];
        temp->borrarEdges(this->scene);
        nivel = this->getLevel(temp);//se obtiene el nivel del nodo
        index = temp->getIndex();//se obtiene el indice del nodo

        //parte de arriba de la formula para obtener la posicion en x.
        //index * widthOfWindow

        double numerador = index * (this->scene->width()+100);
        //parte de abajo de la formula para obtener la posicion en x.
        //(2^nivel) + 1
        double denominador = pow(2.0, double(nivel)) + 1;
        //division de la parte de arriba entre la de abajo para obtener
        //la posicion en x que va a llevar el nodo
        double x = numerador / denominador;

        //altura que va a llevar el nodo
        double y = 0.0;

        //cuando existe un padre entra al if
        if (temp->getPadre() != NULL){
            //temp->getPadre()->borrarEdges();
            //se toma la altura del padre
            double altura = temp->getPadre()->scenePos().y();
            //double altura = temp->getPadre()->getY();
            //se le suma 50 a la altura anterior y se le asigna al nodo
            y = altura + 50;
            this->scene->addItem(new Edge<T>(temp, temp->getPadre()));
        }

        //se asignan las coordenadas del nodo para que se dibuje correctamente
        //QPoint coor()
        temp->setCoordinates(x,y);


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


#endif // ROJINEGRO
