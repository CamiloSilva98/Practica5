#ifndef PROYECTIL_H
#define PROYECTIL_H
#include "particula.h"

class proyectil : public particula
{
public:
    // direccion: 1 dispara hacia la derecha, -1 hacia la izquierda
    proyectil(int id, double x, double y, double velocidad, double anguloGrados,
              int direccion, double masa, double radio);

    double calcularDano(double velocidadImpacto) const;
};

#endif