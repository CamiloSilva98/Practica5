#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Juego = new juego(1200, 550);
    const caja &c = Juego->getCaja();

    escena = new QGraphicsScene(0, 0, c.getAncho(), c.getAlto(), this);
    escena->addRect(0, 0, c.getAncho(), c.getAlto(), QPen(Qt::black));

    vista = new QGraphicsView(escena, this);
    vista->setFixedSize(c.getAncho() + 4, c.getAlto() + 4);
    setCentralWidget(vista);

    dibujarObstaculos();
}

MainWindow::~MainWindow()
{
    delete Juego;
    delete ui;
}

void MainWindow::dibujarObstaculos()
{
    for (obstaculo *o : Juego->getObstaculos())
    {
        obstaculografico *g = new obstaculografico(o);
        escena->addItem(g);
        ObstaculosGraficos.push_back(g);
    }
}