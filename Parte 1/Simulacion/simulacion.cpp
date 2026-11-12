#include "simulacion.h"
#include "colisionparticulas.h"
#include <stdexcept>
using namespace std;

simulacion::simulacion(const caja &CajaSim, double PasoTiempo, double Duracion): MiCaja(CajaSim), Dt(PasoTiempo), TiempoTotal(Duracion), Tiempo(0.0){
    if (Dt <= 0 || Duracion <= 0)
        throw invalid_argument("El paso de tiempo y la duracion deben ser positivos");
}

void simulacion::AgregarObstaculo(const obstaculo &O){
    Obstaculos.push_back(O);
}

void simulacion::AgregarParticula(const particula &P){
    Particulas.push_back(P);
}

int simulacion::CantidadParticulas() const{
    return static_cast<int>(Particulas.size());
}

void simulacion::Ejecutar(const string &Ruta){
    Salida.open(Ruta.c_str());
    if (!Salida.is_open())
        throw runtime_error("No se pudo crear el archivo: " + Ruta);

    Tiempo = 0.0;
    EscribirEncabezado();
    EscribirPosiciones(); // estado inicial, t = 0

    // Contador entero para no acumular error de punto flotante
    long Pasos = static_cast<long>(TiempoTotal / Dt + 0.5);
    for (long i = 1; i <= Pasos; i++)
    {
        Tiempo = i * Dt;
        Paso();
        EscribirPosiciones();
    }
    Salida.close();
}

// Orden de verificacion en cada paso:mover,paredes, obstaculos,particula-particula
// Primero lo que no cambia el numero de particulas y al final las fusiones
void simulacion::Paso(){
    for (particula &P : Particulas)
        P.mover(Dt);

    ColisionesParedes();
    ColisionesObstaculos();
    ColisionesParticulas();
}

void simulacion::ColisionesParedes(){
    for (particula &P : Particulas)
        if (MiCaja.colisionarParticula(P))
            RegistrarColision("PARED", P.getId(), -1, P.getX(), P.getY());
}

void simulacion::ColisionesObstaculos(){
    for (particula &P : Particulas)
        for (obstaculo &O : Obstaculos)
            if (O.colisionarParticula(P))
                RegistrarColision("OBSTACULO", P.getId(), -1, P.getX(), P.getY());
}

void simulacion::ColisionesParticulas(){
    // La fusion la hace colisionparticulas, solo se anota cada una con el instante actual
    colisionparticulas Colision;
    vector<Fusion> Fusiones = Colision.ResolverFusiones(Particulas);
    for (const Fusion &F : Fusiones)
        RegistrarColision("PARTICULA", F.IdA, F.IdB, F.X, F.Y);
}

// Archivo de salida

void simulacion::EscribirEncabezado(){
    Salida << "# Simulacion de colisiones - Practica 5\n";
    Salida << "# B,ancho,alto | O,x,y,ancho,alto | P,t,id,x,y,radio | C,t,tipo,id1,id2,x,y\n";
    Salida << "B," << MiCaja.getAncho() << "," << MiCaja.getAlto() << "\n";
    for (const obstaculo &O : Obstaculos)
        Salida << "O," << O.getX() << "," << O.getY() << ","
               << O.getAncho() << "," << O.getAlto() << "\n";
}

void simulacion::EscribirPosiciones(){
    for (const particula &P : Particulas)
        Salida << "P," << Tiempo << "," << P.getId() << ","
               << P.getX() << "," << P.getY() << "," << P.getRadio() << "\n";
}

void simulacion::RegistrarColision(const string &Tipo, int Id1, int Id2, double X, double Y){
    Salida << "C," << Tiempo << "," << Tipo << "," << Id1 << "," << Id2 << ","
           << X << "," << Y << "\n";
}