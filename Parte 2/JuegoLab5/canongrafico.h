#ifndef CANONGRAFICO_H
#define CANONGRAFICO_H

#include <QGraphicsItemGroup>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QPointF>

// Dibujo del arma: una base circular y un tubo que gira segun el angulo
class canongrafico : public QGraphicsItemGroup
{
private:
    QGraphicsEllipseItem *Base;
    QGraphicsRectItem *Tubo;
    double Largo;      // largo del tubo
    double Angulo;     // grados, positivo hacia arriba (igual que proyectil)
    int Direccion;     // 1 dispara a la derecha, -1 a la izquierda

public:
    // x, y: centro de la base en la escena
    canongrafico(double x, double y, int direccion, double largo = 50, double grosor = 14);

    // cambia el angulo (grados) y gira el tubo
    void setAngulo(double grados);
    double getAngulo() const { return Angulo; }

    // punto de la escena por donde sale el proyectil
    QPointF punta() const;
};

#endif // CANONGRAFICO_H
