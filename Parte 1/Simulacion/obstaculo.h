#ifndef OBSTACULO_H
#define OBSTACULO_H
#include "particula.h"


class obstaculo
{
private:
    double x, y;        // esquina inferior izquierda
    double ancho, alto;
    double e;           // coeficiente de restitucion
public:
    obstaculo(double x, double y, double ancho, double alto, double e);

    double getX() const { return x; }
    double getY() const { return y; }
    double getAncho() const { return ancho; }
    double getAlto() const { return alto; }
    double getE() const { return e; }

    bool colisionarParticula(particula &p) const;
};

#endif // OBSTACULO_H
