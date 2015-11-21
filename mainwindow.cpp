#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "edge.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    setFixedSize(1000,800);
    setWindowTitle("Arboles");
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->insNum->installEventFilter(this);
    ui->borrarNum->installEventFilter(this);
    ui->buscNum->installEventFilter(this);
    ui->graphicsView->showMaximized();
    avl = new AVLTree<int>();
    avl->setScene(scene);
    rojinegro = new Rojinegro<int>();
    rojinegro->setScene(scene);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_released()
{
    addNode();
}



void MainWindow::addNode(){
    QString numString = ui->insNum->toPlainText();
    if(!numString.isEmpty()){
        int num = numString.toInt();
        switch (currentArbol){
        case 1:{
            // Avl
            NodoB<int> *nuevo = new NodoB<int>(num);
            avl->insert(nuevo);
            break;
        }
        case 2:{
            //Rojinegro
            NodoB<int> *nuevo = new NodoB<int>(num);
            rojinegro->RBinsert(nuevo);
            break;
        }
        case 3:{
            //2/3
            //dostres->insert(num);
            break;
        }
        }
    }
    ui->insNum->clear();
    update();
}

void MainWindow::deleteNode(){
    QString numString = ui->borrarNum->toPlainText();
    if(!numString.isEmpty()){
        int num = numString.toInt();
        switch (currentArbol){
        case 1:
            // Avl
            avl->remove(num);
            break;
        case 2:
            //Rojinegro
            rojinegro->RBdelete(num);
            break;
        case 3:
            //2/3
            //dostres->remove(num);
            break;
        }
    }
    ui->borrarNum->clear();
    update();
}

void MainWindow::buscarNodo(){
    QString numString = ui->buscNum->toPlainText();
    if(!numString.isEmpty()){
        int num = numString.toInt();
        switch (currentArbol){
        case 1:{
            // Avl
            NodoB<int> * buscar = avl->search(num);
            if(buscar)
                buscar->encontrado(true);
                avl->bfs();
            break;
        }
        case 2:{
            //Rojinegro
            NodoB<int> * buscar = rojinegro->search(num);
            if(buscar)
                buscar->encontrado(true);
                rojinegro->bfs();
            break;
        }
        case 3:{
            //2/3
            //dostres->buscar(num);
            break;
        }
        }
    }
    ui->buscNum->clear();
    update();
}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    if (object == ui->insNum && event->type() == QEvent::KeyPress){
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Return){
            addNode();
            return true;
        }
        else{
            return QMainWindow::eventFilter(object, event);
        }
    }
    else if (object == ui->borrarNum && event->type() == QEvent::KeyPress){
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Return){
            deleteNode();
            return true;
        }
        else{
            return QMainWindow::eventFilter(object, event);
        }
    }
    else if (object == ui->buscNum && event->type() == QEvent::KeyPress){
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Return){
            buscarNodo();
            return true;
        }
        else{
            return QMainWindow::eventFilter(object, event);
        }
    }
    else{
        return QMainWindow::eventFilter(object, event);
    }
}

void MainWindow::on_buscar_released()
{
    buscarNodo();
}

void MainWindow::on_borrar_released()
{
    deleteNode();
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    switch (currentArbol){
    case 1:
        avl->clear();
        break;
    case 2:
        //Rojinegro
        rojinegro->clear();
        break;
    case 3:
        //2/3
        //dostres->clear();
        break;
    }
    currentArbol = index;

    //avl->clear();
    std::cout << index << endl;
}
