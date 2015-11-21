#ifndef NODOB_H
#define NODOB_H

#include <QPainter>
#include <QDebug>
#include <QGraphicsItem>
#include <iostream>
#include <QList>
#include "edge.h"


template <class T> class Edge;
template <class T>
std::ostream& operator<<(std::ostream&, NodoB<T>&);

template <class T>
class NodoB: public QGraphicsItem{
    T info;
    NodoB<T> * derecho;
    NodoB<T> * izquierdo;
    NodoB<T> * padre;
    QList<Edge<T> *> edgeList;


    bool pressed;
    int index;
    double x,y;
    bool enc;

    /***************************************AVL**********************************************/
    int bfactor = 0;
    int niv;

    /***************************************Rojinegro**********************************************/
    std::string color;



protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
public:
    NodoB();
    NodoB(T info);

    void borrar(QGraphicsScene *scene);
    ~NodoB();

    void setCoordinates(int x,int y);
    void setX(int x);
    void setY(int y);
    int getX();
    int getY();

    void encontrado(bool x);

    void borrarEdges(QGraphicsScene *scene);

    QList<Edge<T> *> edges() const;
    void addEdge(Edge<T> *edge);

    void setIndex(int index);
    int getIndex();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    T getInfo();
    void setInfo(T value);

    NodoB<T> * getDerecho();
    void setDerecho(NodoB<T> * value);

    NodoB<T> * getIzquierdo();
    void setIzquierdo(NodoB<T> * value);

    NodoB<T> * getPadre();
    void setPadre(NodoB<T> * value);

    friend std::ostream& operator<< <>(std::ostream&, NodoB<T>&);

    /***************************************AVL**********************************************/
    void setNivel(int n);
    void setBFactor(int b);

    int getNivel();
    int getBFactor();

    /***************************************Rojinegro**********************************************/
    void setColor(std::string color);
    std::string getColor();

};

template <class T>
void NodoB<T>::addEdge(Edge<T> *edge)
{
    edgeList << edge;
    edge->adjust();
}

//template <class T>
//void NodoB<T>::setEdgeDerecha(Edge<T> *edge){
//    this->edgeDerecha = edge;
//    edge->adjust();
//}

//template <class T>
//void NodoB<T>::setEdgeIzquierda(Edge<T> *edge){
//    this->edgeIzquierda = edge;
//    edge->adjust();
//}

//template <class T>
//void NodoB<T>::setEdgePadre(Edge<T> *edge){
//    this->edgePadre = edge;
//    edge->adjust();
//}

//template <class T>
//Edge<T> * NodoB<T>::getEdgeDerecha(){
//    return edgeDerecha;
//}

//template <class T>
//Edge<T> * NodoB<T>::getEdgeIzquierda(){
//    return edgeIzquierda;
//}

//template <class T>
//Edge<T> * NodoB<T>::getEdgePadre(){
//    return edgePadre;
//}

template <class T>
QList<Edge<T> *> NodoB<T>::edges() const
{
    return edgeList;
}


template <class T>
void NodoB<T>::setCoordinates(int x,int y){
    this->x = x;
    this->y = y;
    setPos(x,y);
}


template <class T>
void NodoB<T>::setX(int x){
    this->x = x;
}

template <class T>
void NodoB<T>::setY(int y){
    this->y = y;
}

template <class T>
int NodoB<T>::getX(){
    return x;
}

template <class T>
int NodoB<T>::getY(){
    return y;
}

template <class T>
QRectF NodoB<T>::boundingRect() const
{
    return QRectF(-15.5, -15.5, 34, 34);
}

template <class T>
void NodoB<T>::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{



    QString disp = QString::number(info);
    QRectF chan = QRectF(-15.5, -15.5, 34, 34);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::HighQualityAntialiasing);

    if (enc){
        painter->setPen(Qt::yellow);
        if(this->getColor() == "negro"){
            painter->setBrush(QBrush(Qt::black));
        }
        else if(this->getColor() == "rojo"){
            painter->setBrush(QBrush(Qt::red));
        }
        else{
            painter->setBrush(QBrush(Qt::white));
        }
    }
    else{
        if(this->getColor() == "negro"){
            painter->setPen(Qt::white);
            painter->setBrush(QBrush(Qt::black));
        }
        else if(this->getColor() == "rojo"){
            painter->setPen(Qt::black);
            painter->setBrush(QBrush(Qt::red));
        }
        else{
            painter->setPen(Qt::black);
            painter->setBrush(QBrush(Qt::white));
        }
    }




    painter->drawEllipse(-15, -15, 30, 30);
    painter->drawText(QRectF(-16.5, -16.5, 35, 35),Qt::AlignCenter, disp);


}

template <class T>
void NodoB<T>::encontrado(bool x){
    enc = x;
}

template <class T>
void NodoB<T>::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = true;
    update();
    std::cout << "Se pico el nodo " << info << std::endl;
    std::cout << "(" << x << "," << y << ")" << std::endl;
    if(padre != NULL){
        std::cout << "Padre  " << padre->getInfo() << std::endl;

    }

    QGraphicsItem::mousePressEvent(event);
}

template <class T>
void NodoB<T>::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}


template <class T>
NodoB<T>::NodoB() {
    this->izquierdo = this->derecho = this->padre = NULL;
    index = 0;

}

template <class T>
NodoB<T>::NodoB(T info) : info(info) {
    this->derecho = this->izquierdo = this->padre = NULL;
    pressed = false;
    enc = false;
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
}

template <class T>
NodoB<T>::~NodoB() {
    izquierdo = derecho = padre = NULL;
}

template <class T>
void NodoB<T>::borrar(QGraphicsScene *scene) {
    scene->removeItem(this);
    borrarEdges(scene);
    delete this;
}


template <class T>
T NodoB<T>::getInfo() {
    return info;
}

template <class T>
void NodoB<T>::setInfo(T value) {
    info = value;
}

template <class T>
NodoB<T> * NodoB<T>::getDerecho() {
    return derecho;
}

template <class T>
void NodoB<T>::setDerecho(NodoB<T> * value) {
    derecho = value;

}

template <class T>
NodoB<T> * NodoB<T>::getIzquierdo() {
    return izquierdo;
}

template <class T>
void NodoB<T>::setIzquierdo(NodoB<T> * value) {
    izquierdo = value;

}

template <class T>
NodoB<T> * NodoB<T>::getPadre() {
    return padre;
}

template <class T>
void NodoB<T>::setPadre(NodoB<T> * value) {
    padre = value;
    //edgePadre = new Edge<T>(this,padre);

}

template <class T>
std::ostream& operator <<(std::ostream& os, NodoB<T>& NodoB) {
    os << NodoB.info;
    return os;
}

template <class T>
void NodoB<T>::setNivel(int n)
{
    niv = n;
}

template <class T>
int NodoB<T>::getNivel()
{
    return niv;
}

template <class T>
void NodoB<T>::setBFactor(int b)
{
    bfactor = b;
}

template <class T>
int NodoB<T>::getBFactor()
{
    return bfactor;
}

template <class T>
void NodoB<T>::setColor(std::string color)
{
    this->color = color;
}

template <class T>
std::string NodoB<T>::getColor()
{
    return color;
}

template <class T>
void NodoB<T>::setIndex(int index){
    this->index = index;
}

template <class T>
int NodoB<T>::getIndex(){
    return index;
}

template <class T>
QVariant NodoB<T>::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        foreach (Edge<T> *edge, edgeList)
            edge->adjust();
        //graph->itemMoved();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

template <class T>
void NodoB<T>::borrarEdges(QGraphicsScene * scene){
    foreach (Edge<T> *edge, edgeList){
        edge->removeScene(scene);
    }
    edgeList.clear();
}








#endif // NODOB_H
