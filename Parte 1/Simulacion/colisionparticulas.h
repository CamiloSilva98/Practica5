#ifndef COLISIONPARTICULAS_H
#define COLISIONPARTICULAS_H
#include <vector>
#include "particula.h"

//datos de una fusion, para anotarla en el archivo de salida
struct Fusion
{
    int IdA; //ids de las dos particulas que chocan
    int IdB;
    double X, Y; //posicion de la nueva particula(centro de la masa)
};

//Colisiones completamenteinelasticas entre particulas
class colisionparticulas
{
public:
    //deteccion cuando chocan su distancia entre centros <= r1+r2
    static bool Hay(const particula &A, const particula &B);

    //fusion de dos particulas en una nueva con las siguientes formulas
    //      M  = m1 + m2
    //      v' = (m1*v1 + m2*v2) / (m1 + m2)
    //      posicion = centro de masa
    //      radio = sqrt(r1^2 + r2^2)   (se conserva el area)
    //      id = el de la particula con mas masa

    static particula Fusionar(const particula &A, const particula &B);

    //particula que desaparece: recorre vector, fusiona par, choque la nueva posicion queda y la segunda se borra
    //repite hasta que ninguna particula se choque y devuelve la fusiones ocurridas, en orden.

    std::vector<Fusion>
    ResolverFusiones(std::vector<particula>&Particulas);

    //energia cinetica qie se pierde en la union (siempre>=0)
    static double EnergiaPerdida(const particula &A, const particula &B);
};

#endif // COLISIONPARTICULAS_H
