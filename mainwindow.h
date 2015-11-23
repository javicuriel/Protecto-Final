#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QDialog>
#include <QtGui>
#include <QtCore>
#include <QDir>
#include "nodoB.h"
#include "rojinegro.h"
#include "arboldostres.h"
#include "lectorarchivos.h"


template <class T> class NodoB;
template <class T> class Rojinegro;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    bool eventFilter(QObject *object, QEvent *event);

    ~MainWindow();

    void addNode();
    void buscarNodo();
    void deleteNode();

private slots:
    void on_pushButton_released();

    void on_buscar_released();

    void on_borrar_released();

    void on_comboBox_currentIndexChanged(int index);

    void on_botonLeer_clicked();

private:
    QGraphicsScene *scene;
    Ui::MainWindow *ui;
    int currentArbol = 0;
    AVLTree<int> * avl;
    Rojinegro<int> * rojinegro;
    ArbolDosTres<int> * dosTres;

};

#endif // MAINWINDOW_H
