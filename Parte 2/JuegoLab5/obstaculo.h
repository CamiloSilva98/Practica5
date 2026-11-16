#ifndef OBSTACULO_H
#define OBSTACULO_H
#include "particula.h"


class obstaculo
{
private:
    double x, y;        // esquina inferior izquierda
    double ancho, alto;
    double e;           // coeficiente de restitucion
    double resistencia;
public:
    obstaculo(double x, double y, double ancho, double alto, double e, double resistencia);

    double getX() const { return x; }
    double getY() const { return y; }
    double getAncho() const { return ancho; }
    double getAlto() const { return alto; }
    double getE() const { return e; }
    double getResistencia() const { return resistencia; }

    bool colisionarParticula(particula &p) const;
    bool estaDestruido() const { return resistencia <= 0; }

    void recibirDano(double dano);
};

#endif // OBSTACULO_H