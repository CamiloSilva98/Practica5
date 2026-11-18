#ifndef OBSTACULOGRAFICO_H
#define OBSTACULOGRAFICO_H
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include "obstaculo.h"

class obstaculografico : public QGraphicsRectItem
{
private:
    obstaculo *Logico;
    QGraphicsTextItem *Texto;

public:
    obstaculografico(obstaculo *logico);

    // vuelve a leer la resistencia del obstaculo y la redibuja
    void actualizar();
};

#endif