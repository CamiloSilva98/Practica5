#ifndef OBSTACULO_H
#define OBSTACULO_H
#include "particula.h"


class obstaculo
{
private:
    double x, y;        // esquina superior izquierda
    double ancho, alto;
    double e;           // coeficiente de restitucion
    double resistencia;
    int dueno;              // jugador 1 o 2
    bool representante;     // true si es el representante del jugador
public:
    obstaculo(double x, double y, double ancho, double alto, double e, double resistencia,
              int dueno, bool representante);

    int getDueno() const { return dueno; }
    bool esRepresentante() const { return representante; }

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