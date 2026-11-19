#include "colisionproyectil.h"
#include <cmath>

using namespace std;

double colisionproyectil::ContraObstaculo(proyectil &P, obstaculo &O)
{
    // un obstaculo destruido ya no choca
    if (O.estaDestruido())
        return 0.0;

    // rapidez de impacto: se mide ANTES del rebote
    double Vx0 = P.getVx();
    double Vy0 = P.getVy();
    double Rapidez = hypot(Vx0, Vy0);

    if (!O.colisionarParticula(P))
        return 0.0;

    // si la velocidad no cambio, el proyectil ya se alejaba: solo se corrigio la posicion
    if (P.getVx() == Vx0 && P.getVy() == Vy0)
        return 0.0;

    double Dano = P.calcularDano(Rapidez);
    O.recibirDano(Dano);
    return Dano;
}

ResultadoColision colisionproyectil::Resolver(proyectil &P, const caja &Caja,
                                              const vector<obstaculo *> &Obstaculos)
{
    ResultadoColision R;

    R.ChocoPared = Caja.colisionarParticula(P);

    for (size_t i = 0; i < Obstaculos.size(); i++)
    {
        double Dano = ContraObstaculo(P, *Obstaculos[i]);
        if (Dano > 0.0)
        {
            if (R.IndiceGolpeado == -1)
                R.IndiceGolpeado = static_cast<int>(i);
        }
    }
    return R;
}