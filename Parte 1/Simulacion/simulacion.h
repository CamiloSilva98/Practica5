#ifndef SIMULACION_H
#define SIMULACION_H

#include <fstream>
#include <string>
#include <vector>

#include "caja.h"
#include "obstaculo.h"
#include "particula.h"

// Bucle de tiempo discreto
// En cada paso mueve las particulas, aplica las colisiones
// (paredes y obstaculos), (particula-particula), y escribe
// el archivo de salida con las posiciones y cada colision con su instante.
class simulacion
{
private:
    caja MiCaja;
    std::vector<obstaculo> Obstaculos;
    std::vector<particula> Particulas;
    double Dt;            // paso de tiempo
    double TiempoTotal;   // duracion de la simulacion
    double Tiempo;        // instante actual
    std::ofstream Salida;

    void Paso();
    void ColisionesParedes();
    void ColisionesObstaculos();
    void ColisionesParticulas();

    void EscribirEncabezado();
    void EscribirPosiciones();
    void RegistrarColision(const std::string &Tipo, int Id1, int Id2, double X, double Y);

public:
    simulacion(const caja &CajaSim, double PasoTiempo, double Duracion);

    void AgregarObstaculo(const obstaculo &O);
    void AgregarParticula(const particula &P);

    // Corre toda la simulacion y guarda el resultado en Ruta.
    // Lanza std::runtime_error si no se puede crear el archivo.
    void Ejecutar(const std::string &Ruta);

    int CantidadParticulas() const;
};

#endif // SIMULACION_H