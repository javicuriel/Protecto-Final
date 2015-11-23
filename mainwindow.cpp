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
    ui->boxArchivo->installEventFilter(this);
    //ui->graphicsView->showMaximized();
    avl = new AVLTree<int>();
    avl->setScene(scene);
    rojinegro = new Rojinegro<int>();
    rojinegro->setScene(scene);
    dosTres = new ArbolDosTres<int>();
    dosTres->setScene(scene);


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
            NodoDosTres<int>*nuevo = new NodoDosTres<int>(num);
            dosTres->insertar23(nuevo);
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
            dosTres->borrar(num);
            dosTres->bfs();
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
            NodoDosTres<int> * buscar = dosTres->buscarNodo(num,dosTres->getRaiz());
            if(buscar)
                buscar->encontrado(true);
                dosTres->bfs();
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
    else if (object == ui->boxArchivo && event->type() == QEvent::KeyPress){
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Return){
            leerArchivo();
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
        scene->clear();


        break;
    case 2:
        //Rojinegro
        rojinegro->clear();
        scene->clear();


        break;
    case 3:
        //2/3
        dosTres->clear();
        scene->clear();

        break;
    }
    currentArbol = index;

    //avl->clear();
    std::cout << index << endl;
}

void MainWindow::leerArchivo(){
    QDir directorio;
    QString dir = directorio.homePath();
    std::string home = dir.toStdString();

    QString nomArchivo = ui->boxArchivo->toPlainText();
    std::string nombreArchivo = nomArchivo.toStdString();

    std::string ruta = "";

    if (nombreArchivo.rfind(".txt") != -1) {
        ruta = home + "/Desktop/" + nombreArchivo;
    }
    else {
        ruta = home + "/Desktop/" + nombreArchivo + ".txt";
    }

    LectorArchivos lector;
    std::vector<int> datos = lector.leer(ruta);

    switch (currentArbol){
    case 1:{
        // Avl
        for(int i = 0; i < datos.size(); i++){
            NodoB<int> *nuevo = new NodoB<int>(datos[i]);
            avl->insert(nuevo);
        }
        break;
    }
    case 2:{
        //Rojinegro
        for(int i = 0; i < datos.size(); i++){
            NodoB<int> *nuevo = new NodoB<int>(datos[i]);
            rojinegro->RBinsert(nuevo);
        }
        break;
    }
    case 3:{
        //2/3
        for(int i = 0; i < datos.size(); i++){
            NodoDosTres<int>*nuevo = new NodoDosTres<int>(datos[i]);
            dosTres->insertar23(nuevo);
        }
        break;
    }
    }
}

void MainWindow::on_botonLeer_clicked()
{
    leerArchivo();
//    QDir directorio;
//    QString dir = directorio.homePath();
//    std::string home = dir.toStdString();

//    QString nomArchivo = ui->boxArchivo->toPlainText();
//    std::string nombreArchivo = nomArchivo.toStdString();

//    std::string ruta = "";

//    if (nombreArchivo.rfind(".txt") != -1) {
//        ruta = home + "/Desktop/" + nombreArchivo;
//    }
//    else {
//        ruta = home + "/Desktop/" + nombreArchivo + ".txt";
//    }

//    LectorArchivos lector;
//    std::vector<int> datos = lector.leer(ruta);

//    switch (currentArbol){
//    case 1:{
//        // Avl
//        for(int i = 0; i < datos.size(); i++){
//            NodoB<int> *nuevo = new NodoB<int>(datos[i]);
//            avl->insert(nuevo);
//        }
//        break;
//    }
//    case 2:{
//        //Rojinegro
//        for(int i = 0; i < datos.size(); i++){
//            NodoB<int> *nuevo = new NodoB<int>(datos[i]);
//            rojinegro->RBinsert(nuevo);
//        }
//        break;
//    }
//    case 3:{
//        //2/3
//        for(int i = 0; i < datos.size(); i++){
//            NodoDosTres<int>*nuevo = new NodoDosTres<int>(datos[i]);
//            dosTres->insertar23(nuevo);
//        }
//        break;
//    }
//    }

}
