#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPen>
#include <QMessageBox>
#include <QString>

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
    ProyectilGrafico = nullptr;

    temporizador = new QTimer(this);
    connect(temporizador, &QTimer::timeout, this, &MainWindow::tick);
    temporizador->start(16);

    // prueba temporal, borrar cuando esten los controles de Paulina
    Juego->lanzar(45, 80);
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

void MainWindow::tick()
{
    Juego->paso(DT);

    // proyectil en vuelo: su grafico se crea la primera vez y se mueve en cada tick
    if (Juego->enVuelo()) {
        if (!ProyectilGrafico) {
            ProyectilGrafico = new proyectilgrafico(Juego->getProyectil());
            escena->addItem(ProyectilGrafico);
        }
        ProyectilGrafico->actualizar();
    } else if (ProyectilGrafico) {
        // el turno termino, se quita el grafico
        escena->removeItem(ProyectilGrafico);
        delete ProyectilGrafico;
        ProyectilGrafico = nullptr;
    }

    // numeros de resistencia y obstaculos destruidos
    for (obstaculografico *g : ObstaculosGraficos)
        g->actualizar();

    if (Juego->getGanador() != 0) {
        temporizador->stop();
        QMessageBox::information(this, "Fin del juego",
                                 QString("Gano el jugador %1").arg(Juego->getGanador()));
    }
}