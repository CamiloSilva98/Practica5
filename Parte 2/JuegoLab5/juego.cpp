#include "juego.h"

juego::juego(double ancho, double alto)
    : MiCaja(ancho, alto)
{
    crearObstaculos();
}

juego::~juego()
{
    for (obstaculo *o : Obstaculos)
        delete o;
}

void juego::crearObstaculos()
{
    // x, y (esquina superior izquierda), ancho, alto, e, resistencia
    // el piso esta en y = 500
    // estructura izquierda: dos columnas de 200 y una viga de 100 encima
    Obstaculos.push_back(new obstaculo(100, 450, 50, 100, 0.6, 150));
    Obstaculos.push_back(new obstaculo(300, 450, 50, 100, 0.6, 150));
    Obstaculos.push_back(new obstaculo(100, 420, 250, 30, 0.6, 300));

    // estructura derecha, igual que la izquierda
    Obstaculos.push_back(new obstaculo(1050, 450, 50, 100, 0.6, 150));
    Obstaculos.push_back(new obstaculo(850, 450, 50, 100, 0.6, 150));
    Obstaculos.push_back(new obstaculo(850, 420, 250, 30, 0.6, 300));
}