#include "obstaculografico.h"
#include <QBrush>
#include <QColor>
#include <QPen>
#include <QString>

obstaculografico::obstaculografico(obstaculo *logico)
    : QGraphicsRectItem(0, 0, logico->getAncho(), logico->getAlto()), Logico(logico)
{
    // la fisica tiene el eje y hacia arriba y Qt hacia abajo, aqui se convierte
    setPos(logico->getX(), logico->getY());

    setBrush(QBrush(QColor(255, 228, 196)));
    setPen(QPen(QColor(200, 140, 40)));

    Texto = new QGraphicsTextItem(this);
    actualizar();
}

void obstaculografico::actualizar()
{
    // si ya se destruyo, deja de mostrarse
    if (Logico->estaDestruido())
    {
        hide();
        return;
    }

    Texto->setPlainText(QString::number(Logico->getResistencia(), 'f', 0));

    // centra el numero dentro del rectangulo
    QRectF r = Texto->boundingRect();
    Texto->setPos((Logico->getAncho() - r.width()) / 2,
                  (Logico->getAlto() - r.height()) / 2);
}
