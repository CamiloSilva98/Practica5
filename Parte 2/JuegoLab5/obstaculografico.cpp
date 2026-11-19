#include "obstaculografico.h"
#include <QBrush>
#include <QColor>
#include <QPen>
#include <QString>
#include <QGraphicsPixmapItem>
#include <QPixmap>

obstaculografico::obstaculografico(obstaculo *logico)
    : QGraphicsRectItem(0, 0, logico->getAncho(), logico->getAlto()), Logico(logico)
{
    // la fisica tiene el eje y hacia arriba y Qt hacia abajo, aqui se convierte
    setPos(logico->getX(), logico->getY());

    // el representante lleva la foto de su jugador
    if (logico->esRepresentante())
    {
        QString ruta = (logico->getDueno() == 1) ? ":/new/prefix1/archivos/1.jpg"
                                                 : ":/new/prefix1/archivos/2.jpg";
        QPixmap foto(ruta);
        if (!foto.isNull())
        {
            // se ajusta al rectangulo sin deformarla y se centra
            QPixmap ajustada = foto.scaled(static_cast<int>(logico->getAncho()),
                                           static_cast<int>(logico->getAlto()),
                                           Qt::KeepAspectRatio, Qt::SmoothTransformation);
            QGraphicsPixmapItem *imagen = new QGraphicsPixmapItem(ajustada, this);
            imagen->setPos((logico->getAncho() - ajustada.width()) / 2,
                           (logico->getAlto() - ajustada.height()) / 2);
        }
    }
    else
        setBrush(QBrush(QColor(92, 64, 51)));
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

    QString etiqueta = QString::number(Logico->getResistencia(), 'f', 0);
    if (Logico->esRepresentante())
        etiqueta = "\n\n" + etiqueta;
    Texto->setPlainText(etiqueta);

    // centra el numero dentro del rectangulo
    QRectF r = Texto->boundingRect();
    Texto->setPos((Logico->getAncho() - r.width()) / 2,
                  (Logico->getAlto() - r.height()) / 2);
}
