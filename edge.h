#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>

#include <math.h>

#include <QPainter>

#include "nodoB.h"

#include <QGraphicsScene>

template <class T> class NodoB;

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;


template <class T>
class Edge : public QGraphicsItem
{
public:
    Edge(NodoB<T> *hijoNodo, NodoB<T> *padreNodo);

    NodoB<T> *getHijo() const;
    NodoB<T> *getPadre() const;

    void adjust();
    void setHijo(NodoB<T> * nodo);
    void setPadre(NodoB<T> * nodo);

    enum { Type = UserType + 2 };
    int type() const Q_DECL_OVERRIDE { return Type; }
    void removeScene(QGraphicsScene *scene);

protected:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

private:
    NodoB<T> *hijo, *padre;

    QPointF hijoPunto;
    QPointF padrePunto;
    qreal arrowSize;


};

template <class T>
void Edge<T>::removeScene(QGraphicsScene * scene){
    scene->removeItem(this);

}

template <class T>
Edge<T>::Edge(NodoB<T> *hijoNodo, NodoB<T> *padreNodo)
    : arrowSize(10)
{

    setAcceptedMouseButtons(0);
    hijo = hijoNodo;
    padre = padreNodo;
    hijo->addEdge(this);
    padre->addEdge(this);
}

template <class T>
NodoB<T> *Edge<T>::getHijo() const
{
    return hijo;
}

template <class T>
NodoB<T> *Edge<T>::getPadre() const
{
    return padre;
}

template <class T>
void Edge<T>::setHijo(NodoB<T> * nodo){
    hijo = nodo;
}

template <class T>
void Edge<T>::setPadre(NodoB<T> * nodo){
    padre = nodo;
}

template <class T>
void Edge<T>::adjust()
{
    if (!hijo || !padre)
        return;

    QLineF line(mapFromItem(hijo, 0, 0), mapFromItem(padre, 0, 6));
    qreal length = line.length();

    prepareGeometryChange();

    if (length > qreal(20.)) {
        QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
        hijoPunto = line.p1() + edgeOffset;
        padrePunto = line.p2() - edgeOffset;
    } else {
        hijoPunto = padrePunto = line.p1();
    }
}

template <class T>
QRectF Edge<T>::boundingRect() const
{
    if (!hijo || !padre)
        return QRectF();

    qreal penWidth = 1;
    qreal extra = (penWidth + arrowSize) / 2.0;

    return QRectF(hijoPunto, QSizeF(padrePunto.x() - hijoPunto.x(),
                                    padrePunto.y() - hijoPunto.y()))
            .normalized()
            .adjusted(-extra, -extra, extra, extra);
}

template <class T>
void Edge<T>::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!hijo || !padre)
        return;

    QLineF line(hijoPunto, padrePunto);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;
    //! [4]

    //! [5]
    // Draw the line itself
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);
    //! [5]

    //! [6]
    // Draw the arrows
    double angle = ::acos(line.dx() / line.length());
    if (line.dy() >= 0)
        angle = TwoPi - angle;

    QPointF hijoArrowP1 = hijoPunto + QPointF(sin(angle + Pi / 3) * arrowSize,
                                              cos(angle + Pi / 3) * arrowSize);
    QPointF hijoArrowP2 = hijoPunto + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
                                              cos(angle + Pi - Pi / 3) * arrowSize);
    //    QPointF padreArrowP1 = padrePunto + QPointF(sin(angle - Pi / 3) * arrowSize,
    //                                              cos(angle - Pi / 3) * arrowSize);
    //    QPointF padreArrowP2 = padrePunto + QPointF(sin(angle - Pi + Pi / 3) * arrowSize,
    //                                              cos(angle - Pi + Pi / 3) * arrowSize);

    painter->setBrush(Qt::black);
    painter->drawPolygon(QPolygonF() << line.p1() << hijoArrowP1 << hijoArrowP2);
    //painter->drawPolygon(QPolygonF() << line.p1() << sourceArrowP1);
    //painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
    painter->drawPolygon(QPolygonF() << line.p2());
}

#endif // EDGE_H
