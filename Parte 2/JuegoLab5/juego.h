#include <vector>
#include "caja.h"
#include "obstaculo.h"

class juego
{
private:
    caja MiCaja;
    std::vector<obstaculo *> Obstaculos;

    void crearObstaculos();

public:
    juego(double ancho, double alto);
    ~juego();

    const caja &getCaja() const { return MiCaja; }
    const std::vector<obstaculo *> &getObstaculos() const { return Obstaculos; }
};
