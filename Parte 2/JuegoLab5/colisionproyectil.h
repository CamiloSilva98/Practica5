#ifndef COLISIONPROYECTIL_H
#define COLISIONPROYECTIL_H

#include <vector>
#include "caja.h"
#include "obstaculo.h"
#include "proyectil.h"

// Resultado de un paso de colision, para que la interfaz actualice la pantalla
struct ResultadoColision
{
    bool ChocoPared = false;     // hubo rebote elastico en la caja
    int IndiceGolpeado = -1;     // primer obstaculo golpeado (-1 si ninguno)
    double Dano = 0.0;           // dano total aplicado en este paso
    bool Destruyo = false;       // algun obstaculo quedo destruido en este paso
};

class colisionproyectil
{
public:
    // Choque del proyectil con UN obstaculo. Devuelve el dano aplicado (0 si no hubo choque).
    static double ContraObstaculo(proyectil &P, obstaculo &O);

    // Un paso completo: paredes (elastico) y todos los obstaculos (inelastico + dano)
    static ResultadoColision Resolver(proyectil &P, const caja &Caja,
                                      const std::vector<obstaculo *> &Obstaculos);
};

#endif // COLISIONPROYECTIL_H
