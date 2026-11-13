#include "obstaculo.h"
#include <algorithm>
#include <cmath>

obstaculo::obstaculo(double x, double y, double ancho, double alto, double e)
    : x(x), y(y), ancho(ancho), alto(alto), e(e){}

bool obstaculo::colisionarParticula(particula &p) const
{
    double px = p.getX();
    double py = p.getY();
    double vx = p.getVx();
    double vy = p.getVy();
    double r = p.getRadio();

    // punto del rectangulo mas cercano al centro de la particula
    double cx = std::max(x, std::min(px, x + ancho));
    double cy = std::max(y, std::min(py, y + alto));
    double dx = px - cx;
    double dy = py - cy;

    // si la distancia es mayor o igual al radio no hay choque
    if (dx * dx + dy * dy >= r * r)
        return false;

    // lado del choque: 0 izquierdo, 1 derecho, 2 inferior, 3 superior
    int lado;

    if (dx == 0 && dy == 0)
    {
        // el centro quedo dentro del obstaculo, se toma el lado mas cercano
        double dIzq = px - x;
        double dDer = x + ancho - px;
        double dInf = py - y;
        double dSup = y + alto - py;
        double menor = std::min(std::min(dIzq, dDer), std::min(dInf, dSup));

        if (menor == dIzq) lado = 0;
        else if (menor == dDer) lado = 1;
        else if (menor == dInf) lado = 2;
        else lado = 3;
    }
    else if (std::abs(dx) > std::abs(dy))
    {
        lado = (dx < 0) ? 0 : 1;
    }
    else
    {
        lado = (dy < 0) ? 2 : 3;
    }

    // se corrige la posicion y se aplica -e a la velocidad perpendicular al lado
    // la velocidad paralela no se toca
    switch (lado)
    {
    case 0:
        px = x - r;
        if (vx > 0) vx = -e * vx;
        break;
    case 1:
        px = x + ancho + r;
        if (vx < 0) vx = -e * vx;
        break;
    case 2:
        py = y - r;
        if (vy > 0) vy = -e * vy;
        break;
    default:
        py = y + alto + r;
        if (vy < 0) vy = -e * vy;
        break;
    }

    p.setPosicion(px, py);
    p.setVelocidad(vx, vy);

    return true;
}