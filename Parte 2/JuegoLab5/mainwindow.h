#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <vector>
#include "juego.h"
#include "obstaculografico.h"
#include <QTimer>
#include "canongrafico.h"
#include "proyectilgrafico.h"
#include <QMediaPlayer>
#include <QAudioOutput>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    QGraphicsScene *escena;
    QGraphicsView *vista;
    juego *Juego;
    std::vector<obstaculografico *> ObstaculosGraficos;

    canongrafico *CanonJ1;   // canon del jugador 1 (izquierda, dispara a la derecha)
    canongrafico *CanonJ2; // canon del jugador 2 (derecha, dispara a la izquierda)
    QSlider *SliderAngulo;
    QLabel *EtiquetaAngulo;
    QSlider *SliderVelocidad;
    QLabel *EtiquetaVelocidad;
    QPushButton *BotonLanzar;
    QTimer *Reloj;
    proyectilgrafico *ProyGrafico = nullptr;

    QMediaPlayer *musica;
    QAudioOutput *salidaAudio;

    void dibujarObstaculos();

    void crearCanones();
    void crearControlAngulo(QVBoxLayout *layout);
    void crearControlDisparo(QVBoxLayout *layout);
    void lanzar();               // clic en el boton: dispara con el angulo y la velocidad del control
    void tick();                 // un paso de la animacion
    void terminarLanzamiento();  // el proyectil se detuvo: limpia y pasa al siguiente turno
    void habilitarControles(bool activo);


public:
    // gira el canon del jugador (1 o 2); angulo en grados, positivo hacia arriba
    void setAnguloCanon(int jugador, double angulo);

    // pone el control en el angulo del canon del jugador en turno (llamar al cambiar de turno)
    void sincronizarControl();

};
#endif // MAINWINDOW_H