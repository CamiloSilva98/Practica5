#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <vector>
#include "juego.h"
#include "obstaculografico.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    QGraphicsScene *escena;
    QGraphicsView *vista;
    juego *Juego;
    std::vector<obstaculografico *> ObstaculosGraficos;

    void dibujarObstaculos();
};
#endif // MAINWINDOW_H
