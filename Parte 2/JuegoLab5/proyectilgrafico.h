#ifndef PROYECTILGRAFICO_H
#define PROYECTILGRAFICO_H

#include <QGraphicsEllipseItem>
#include "proyectil.h"

// Dibujo del proyectil: un circulo que sigue al proyectil logico
class proyectilgrafico : public QGraphicsEllipseItem
{
private:
    proyectil *Logico;

public:
    proyectilgrafico(proyectil *logico);

    // vuelve a leer la posicion del proyectil y mueve el circulo (llamar en cada tick)
    void actualizar();
};

#endif // PROYECTILGRAFICO_H
