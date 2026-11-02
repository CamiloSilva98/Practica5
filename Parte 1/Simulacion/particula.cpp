#include "particula.h"


particula::particula()
    : id(0), x(0), y(0), vx(0), vy(0), masa(1), radio(1){}

particula::particula(int id, double x, double y, double vx, double vy, double masa, double radio)
    : id(id), x(x), y(y), vx(vx), vy(vy), masa(masa), radio(radio){}

void particula::mover(double dt, double g)
{
    // posicion despues de dt con las ecuaciones
    x += vx * dt;
    y += vy * dt - 0.5 * g * dt * dt;

    // la gravedad solo cambia la velocidad en y
    vy -= g * dt;
}
