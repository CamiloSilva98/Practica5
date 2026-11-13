#ifndef CAJA_H
#define CAJA_H
#include "particula.h"

class caja
{
private:
    double ancho;
    double alto;
public:
    caja();
    caja(double ancho, double alto);

    double getAncho() const { return ancho; }
    double getAlto() const { return alto; }

    bool colisionarParticula(particula &p) const;
};

#endif // CAJA_H