#include "proyectilgrafico.h"
#include <QBrush>
#include <QColor>
#include <QPen>

proyectilgrafico::proyectilgrafico(proyectil *logico)
    : QGraphicsEllipseItem(-logico->getRadio(), -logico->getRadio(),
                           2 * logico->getRadio(), 2 * logico->getRadio()),
    Logico(logico)
{
    // el rectangulo esta centrado en (0,0), asi setPos recibe el centro del proyectil
    setBrush(QBrush(QColor(255, 0, 203)));
    setPen(QPen(Qt::black));
    setZValue(2);   // por encima de los obstaculos
    actualizar();
}

void proyectilgrafico::actualizar()
{
    setPos(Logico->getX(), Logico->getY());
}