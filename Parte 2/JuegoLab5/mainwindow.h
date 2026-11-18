#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>
#include <vector>
#include "juego.h"
#include "obstaculografico.h"
<<<<<<< Updated upstream
#include <QTimer>
=======
#include "canongrafico.h"
>>>>>>> Stashed changes
#include "proyectilgrafico.h"

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
    canongrafico *CanonJ2;
    QSlider *SliderAngulo;
    QLabel *EtiquetaAngulo;
    QSlider *SliderVelocidad;
    QLabel *EtiquetaVelocidad;
    QPushButton *BotonLanzar;
    QTimer *Reloj;
    proyectilgrafico *ProyGrafico = nullptr;   // canon del jugador 2 (derecha, dispara a la izquierda)

    void dibujarObstaculos();
<<<<<<< Updated upstream
    QTimer *temporizador;
    proyectilgrafico *ProyectilGrafico;

    // paso de tiempo de la simulacion en cada tick
    static constexpr double DT = 0.048;

    void tick();
=======
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

    // angulo (grados) que marca el control en este momento, para usarlo al disparar
    double getAnguloControl() const { return SliderAngulo->value(); }

    // pone el control en el angulo del canon del jugador en turno (llamar al cambiar de turno)
    void sincronizarControl();
>>>>>>> Stashed changes
};
#endif // MAINWINDOW_H