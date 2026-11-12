#include <filesystem>
#include <iostream>
#include <stdexcept>

#include "simulacion.h"

using namespace std;

int main(int argc, char *argv[])
{
    // Sin argumentos el archivo se crea en la carpeta desde donde corre el
    // programa (en Qt Creator, la carpeta build-...). Tambien se puede pasar
    // una ruta completa como argumento.
    string Ruta = (argc > 1) ? argv[1] : "salida.txt";

    try
    {
        caja MiCaja(100.0, 60.0);
        simulacion Sim(MiCaja, 0.01, 15.0);      // dt = 0.01 s, 15 s en total

        // 4 obstaculos cuadrados (x, y, ancho, alto, e)
        Sim.AgregarObstaculo(obstaculo(20, 15, 8, 8, 0.7));
        Sim.AgregarObstaculo(obstaculo(70, 15, 8, 8, 0.7));
        Sim.AgregarObstaculo(obstaculo(20, 40, 8, 8, 0.7));
        Sim.AgregarObstaculo(obstaculo(70, 40, 8, 8, 0.7));

        // 5 particulas (id, x, y, vx, vy, masa, radio)
        Sim.AgregarParticula(particula(1, 10, 30,  12,   3, 2.0, 2.0));
        Sim.AgregarParticula(particula(2, 90, 30, -10,   2, 1.0, 1.5));
        Sim.AgregarParticula(particula(3, 50, 10,   1,  11, 3.0, 2.5));
        //Sim.AgregarParticula(particula(4, 50, 50,  -2, -12, 1.5, 1.8));
        Sim.AgregarParticula(particula(5, 45, 30,   6,   0, 2.5, 2.2));

        Sim.Ejecutar(Ruta);
        cout << "Simulacion terminada. Particulas al final: "
             << Sim.CantidadParticulas() << "\n"
             << "Resultado guardado en: "
             << filesystem::absolute(Ruta).string() << "\n";
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
