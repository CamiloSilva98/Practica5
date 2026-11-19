#include "canongrafico.h"
#include <QBrush>
#include <QColor>
#include <QPen>


canongrafico::canongrafico(double x, double y, int direccion, double largo, double grosor)
    : Angulo(0), Direccion(direccion)
{
    // tubo: nace en el centro de la base y se extiende hacia la derecha; luego se gira
    Tubo = new QGraphicsRectItem(0, -grosor / 2, largo, grosor);
    Tubo->setBrush(QBrush(QColor(90, 90, 90)));
    Tubo->setPen(QPen(Qt::black));

    Base = new QGraphicsEllipseItem(-grosor, -grosor, 2 * grosor, 2 * grosor);
    Base->setBrush(QBrush(QColor(50, 50, 50)));
    Base->setPen(QPen(Qt::black));

    addToGroup(Tubo);
    addToGroup(Base);   // la base queda sobre el tubo
    setPos(x, y);
    setZValue(1);
    setAngulo(45);
}

void canongrafico::setAngulo(double grados)
{
    Angulo = grados;
    // Qt gira en sentido horario con y hacia abajo: a la derecha se sube con -grados,
    // a la izquierda el tubo apunta a 180 grados y sube con +grados
    Tubo->setTransformOriginPoint(0, 0);
    Tubo->setRotation(Direccion == 1 ? -grados : 180 + grados);
}

void canongrafico::setColor(const QColor &tubo, const QColor &base)
{
    Tubo->setBrush(QBrush(tubo));
    Base->setBrush(QBrush(base));
}
