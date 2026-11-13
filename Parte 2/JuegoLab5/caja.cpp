#include "caja.h"

caja::caja()
    : ancho(100), alto(100){}

caja::caja(double ancho, double alto)
    : ancho(ancho), alto(alto){}

bool caja::colisionarParticula(particula &p) const
{
    bool choco = false;
    double x = p.getX();
    double y = p.getY();
    double vx = p.getVx();
    double vy = p.getVy();
    double r = p.getRadio();

    // paredes izquierda y derecha, se invierte vx
    if (x - r < 0)
    {
        x = r;
        vx = -vx;
        choco = true;
    }
    else if (x + r > ancho)
    {
        x = ancho - r;
        vx = -vx;
        choco = true;
    }

    // piso y techo, se invierte vy
    if (y - r < 0)
    {
        y = r;
        vy = -vy;
        choco = true;
    }
    else if (y + r > alto)
    {
        y = alto - r;
        vy = -vy;
        choco = true;
    }

    if (choco)
    {
        p.setPosicion(x, y);
        p.setVelocidad(vx, vy);
    }

    return choco;
}