#ifndef JUEGO_H
#define JUEGO_H

#include <vector>
#include "caja.h"
#include "obstaculo.h"
#include "proyectil.h"
#include "colisionproyectil.h"

class juego
{
private:
    caja MiCaja;
    std::vector<obstaculo *> Obstaculos;
    int jugadorActual;
    proyectil *proyectilActual;
    bool vuelo;          // hay un proyectil en vuelo
    bool huboChoque;     // el proyectil ya choco en este turno
    double tiempoVuelo;
    int ganador;         // 0 si nadie ha ganado

    // valores de partida, se ajustan probando el juego
    static constexpr double GRAVEDAD = 9.81;
    static constexpr double MASA_PROYECTIL = 1.0;
    static constexpr double RADIO_PROYECTIL = 5.0;
    static constexpr double VELOCIDAD_MINIMA = 3.0;
    static constexpr double TIEMPO_MAXIMO = 40.0;
    static constexpr double LARGO_CANON = 50.0;
    static constexpr double MARGEN_CANON = 40.0;
    static constexpr double ALTURA_CANON = 260.0;

    void terminarTurno();
    void revisarVictoria();
    void crearObstaculos();

public:
    juego(double ancho, double alto);
    ~juego();

    const caja &getCaja() const { return MiCaja; }
    const std::vector<obstaculo *> &getObstaculos() const { return Obstaculos; }
    // devuelve false si ya hay un proyectil en vuelo o hay ganador
    bool lanzar(double angulo, double velocidad);

    // avanza un paso de tiempo y devuelve lo que paso, para que la interfaz se actualice
    ResultadoColision paso(double dt);

    int getJugadorActual() const { return jugadorActual; }
    bool enVuelo() const { return vuelo; }
    proyectil *getProyectil() const { return proyectilActual; }
    int getGanador() const { return ganador; }

    // posicion del canon de cada jugador, la interfaz debe dibujarlo ahi
    double canonX(int jugador) const;
    double canonY() const { return ALTURA_CANON; }
    double getLargoCanon() const { return LARGO_CANON; }
};
#endif // JUEGO_H