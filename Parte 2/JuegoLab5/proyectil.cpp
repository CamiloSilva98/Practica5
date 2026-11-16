#include "proyectil.h"
#include <cmath>

namespace {
const double PI = 3.14159265358979323846;
const double FACTOR_DANO = 1.5;
}
proyectil::proyectil(int id, double x, double y, double velocidad, double anguloGrados,
                     int direccion, double masa, double radio)
    : particula(id, x, y,
                direccion * velocidad * std::cos(anguloGrados * PI / 180.0),
                velocidad * std::sin(anguloGrados * PI / 180.0),
                masa, radio){}

double proyectil::calcularDano(double velocidadImpacto) const
{
    // dano = factor * masa * |v impacto|, como pide la guia
    return FACTOR_DANO * getMasa() * velocidadImpacto;
}