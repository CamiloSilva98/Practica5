#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPen>
#include <QMessageBox>
#include <QString>
#include <QHBoxLayout>
#include <QStatusBar>
#include <QBrush>
#include <QPixmap>
#include <QUrl>

namespace {
const double DT = 0.016;            // segundos de simulacion por paso
const int PASOS_POR_TICK = 4;       // pasos por cada tick del reloj
const int INTERVALO_MS = 16;        // tiempo real entre ticks
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Juego = new juego(1200, 550);
    const caja &c = Juego->getCaja();

    escena = new QGraphicsScene(0, 0, c.getAncho(), c.getAlto(), this);
    // fondo de la escena, ajustado al tamano de la caja
    QPixmap fondo(":/new/prefix1/archivos/fondo.jpg");
    if (!fondo.isNull())
        escena->setBackgroundBrush(QBrush(fondo.scaled(static_cast<int>(c.getAncho()),
                                                       static_cast<int>(c.getAlto()),
                                                       Qt::IgnoreAspectRatio,
                                                       Qt::SmoothTransformation)));
    escena->addRect(0, 0, c.getAncho(), c.getAlto(), QPen(Qt::black));

    vista = new QGraphicsView(escena, this);
    vista->setFixedSize(c.getAncho() + 4, c.getAlto() + 4);
    // el widget central lleva la escena arriba y el control del angulo abajo
    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->addWidget(vista);
    crearControlAngulo(layout);
    crearControlDisparo(layout);
    setCentralWidget(central);

    dibujarObstaculos();
    crearCanones();
    sincronizarControl();

    Reloj = new QTimer(this);
    connect(Reloj, &QTimer::timeout, this, &MainWindow::tick);
    statusBar()->showMessage("Turno del jugador 1");

    // musica de fondo en bucle
    salidaAudio = new QAudioOutput(this);
    salidaAudio->setVolume(0.3);
    musica = new QMediaPlayer(this);
    musica->setAudioOutput(salidaAudio);
    musica->setSource(QUrl("qrc:/new/prefix1/archivos/fondoMusica.mp3"));
    musica->setLoops(QMediaPlayer::Infinite);
    musica->play();
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

void MainWindow::crearCanones()
{
    // la posicion y el largo salen de juego, asi el proyectil sale justo de la punta
    double largo = Juego->getLargoCanon();

    CanonJ1 = new canongrafico(Juego->canonX(1), Juego->canonY(), 1, largo);
    CanonJ1->setColor(QColor(70, 110, 200), QColor(40, 60, 120));
    escena->addItem(CanonJ1);

    CanonJ2 = new canongrafico(Juego->canonX(2), Juego->canonY(), -1, largo);
    CanonJ2->setColor(QColor(200, 70, 70), QColor(120, 40, 40));
    escena->addItem(CanonJ2);
}

void MainWindow::setAnguloCanon(int jugador, double angulo)
{
    if (jugador == 1)
        CanonJ1->setAngulo(angulo);
    else
        CanonJ2->setAngulo(angulo);
}

void MainWindow::crearControlAngulo(QVBoxLayout *layout)
{
    QHBoxLayout *fila = new QHBoxLayout();

    EtiquetaAngulo = new QLabel("Angulo: 45", this);
    EtiquetaAngulo->setMinimumWidth(90);

    SliderAngulo = new QSlider(Qt::Horizontal, this);
    SliderAngulo->setRange(0, 90);
    SliderAngulo->setValue(45);

    fila->addWidget(EtiquetaAngulo);
    fila->addWidget(SliderAngulo);
    layout->addLayout(fila);

    // al mover el control, gira el canon del jugador en turno
    connect(SliderAngulo, &QSlider::valueChanged, this, [this](int valor)
            {
                EtiquetaAngulo->setText(QString("Angulo: %1").arg(valor));
                setAnguloCanon(Juego->getJugadorActual(), valor);
            });
}

void MainWindow::sincronizarControl()
{
    int jugador = Juego->getJugadorActual();
    double angulo = (jugador == 1) ? CanonJ1->getAngulo() : CanonJ2->getAngulo();
    // setValue dispara valueChanged, que deja la etiqueta y el canon iguales al control
    SliderAngulo->setValue(static_cast<int>(angulo));
}

void MainWindow::crearControlDisparo(QVBoxLayout *layout)
{
    QHBoxLayout *fila = new QHBoxLayout();

    EtiquetaVelocidad = new QLabel("Velocidad: 100", this);
    EtiquetaVelocidad->setMinimumWidth(90);

    SliderVelocidad = new QSlider(Qt::Horizontal, this);
    SliderVelocidad->setRange(20, 200);
    SliderVelocidad->setValue(100);

    BotonLanzar = new QPushButton("Lanzar", this);

    fila->addWidget(EtiquetaVelocidad);
    fila->addWidget(SliderVelocidad);
    fila->addWidget(BotonLanzar);
    layout->addLayout(fila);

    connect(SliderVelocidad, &QSlider::valueChanged, this, [this](int valor)
            {
                EtiquetaVelocidad->setText(QString("Velocidad: %1").arg(valor));
            });
    connect(BotonLanzar, &QPushButton::clicked, this, &MainWindow::lanzar);
}

void MainWindow::habilitarControles(bool activo)
{
    BotonLanzar->setEnabled(activo);
    SliderAngulo->setEnabled(activo);
    SliderVelocidad->setEnabled(activo);
}

void MainWindow::lanzar()
{
    // juego rechaza el disparo si ya hay uno en vuelo o hay ganador
    if (!Juego->lanzar(SliderAngulo->value(), SliderVelocidad->value()))
        return;

    ProyGrafico = new proyectilgrafico(Juego->getProyectil());
    escena->addItem(ProyGrafico);

    habilitarControles(false);
    statusBar()->showMessage(QString("Jugador %1 disparo").arg(Juego->getJugadorActual()));
    Reloj->start(INTERVALO_MS);
}

void MainWindow::tick()
{
    for (int i = 0; i < PASOS_POR_TICK && Juego->enVuelo(); i++)
        Juego->paso(DT);

    ProyGrafico->actualizar();
    for (obstaculografico *g : ObstaculosGraficos)
        g->actualizar();

    if (!Juego->enVuelo())
        terminarLanzamiento();
}

void MainWindow::terminarLanzamiento()
{
    Reloj->stop();

    // se quita el dibujo antes de que juego borre el proyectil en el siguiente turno
    escena->removeItem(ProyGrafico);
    delete ProyGrafico;
    ProyGrafico = nullptr;

    if (Juego->getGanador() != 0)
    {
        statusBar()->showMessage(QString("Gano el jugador %1").arg(Juego->getGanador()));
        QMessageBox::information(this, "Fin del juego",
                                 QString("Gano el jugador %1").arg(Juego->getGanador()));
        return;   // los controles quedan desactivados
    }

    habilitarControles(true);
    sincronizarControl();
    statusBar()->showMessage(QString("Turno del jugador %1").arg(Juego->getJugadorActual()));
}

