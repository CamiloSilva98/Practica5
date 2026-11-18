#include "juego.h"
#include <cmath>

namespace {
const double PI = 3.14159265358979323846;
}

juego::juego(double ancho, double alto)
    : MiCaja(ancho, alto), jugadorActual(1), proyectilActual(nullptr),
    vuelo(false), huboChoque(false), tiempoVuelo(0.0), ganador(0)
{
    crearObstaculos();
}

juego::~juego()
{
    for (obstaculo *o : Obstaculos)
        delete o;
    delete proyectilActual;
}

void juego::crearObstaculos()
{
    // x, y (esquina superior izquierda), ancho, alto, e, resistencia
    // estructura izquierda: dos columnas de 200 y una viga de 100 encima
    Obstaculos.push_back(new obstaculo(100, 450, 50, 100, 0.6, 150, 1, false));
    Obstaculos.push_back(new obstaculo(300, 450, 50, 100, 0.6, 150, 1, false));
    Obstaculos.push_back(new obstaculo(100, 420, 250, 30, 0.6, 300,1, false));
    Obstaculos.push_back(new obstaculo(195, 500, 60, 50, 0.4, 50, 1, true));

    // estructura derecha, igual que la izquierda
    Obstaculos.push_back(new obstaculo(1050, 450, 50, 100, 0.6, 150, 2, false));
    Obstaculos.push_back(new obstaculo(850, 450, 50, 100, 0.6, 150, 2, false));
    Obstaculos.push_back(new obstaculo(850, 420, 250, 30, 0.6, 300, 2, false));
    Obstaculos.push_back(new obstaculo(945, 500, 60, 50, 0.4, 50, 2, true));
}

double juego::canonX(int jugador) const
{
    return (jugador == 1) ? MARGEN_CANON : MiCaja.getAncho() - MARGEN_CANON;
}

bool juego::lanzar(double angulo, double velocidad)
{
    // no se lanza si hay un proyectil en vuelo o ya hay ganador
    if (vuelo || ganador != 0)
        return false;

    // el proyectil del turno anterior se borra aqui, ya no tiene grafico
    delete proyectilActual;

    // el proyectil sale de la punta del canon
    int direccion = (jugadorActual == 1) ? 1 : -1;
    double rad = angulo * PI / 180.0;
    double x0 = canonX(jugadorActual) + direccion * LARGO_CANON * std::cos(rad);
    double y0 = ALTURA_CANON - LARGO_CANON * std::sin(rad);

    proyectilActual = new proyectil(jugadorActual, x0, y0, velocidad, angulo,
                                    direccion, MASA_PROYECTIL, RADIO_PROYECTIL);
    vuelo = true;
    huboChoque = false;
    tiempoVuelo = 0.0;
    return true;
}

ResultadoColision juego::paso(double dt)
{
    ResultadoColision R;
    if (!vuelo)
        return R;

    proyectilActual->mover(dt, GRAVEDAD);
    tiempoVuelo += dt;

    R = colisionproyectil::Resolver(*proyectilActual, MiCaja, Obstaculos);
    if (R.ChocoPared || R.IndiceGolpeado != -1)
        huboChoque = true;

    revisarVictoria();

    // el turno termina por tiempo o por velocidad baja, pero esta ultima solo despues
    // del primer choque, porque en lo alto de la trayectoria la velocidad tambien baja
    double rapidez = std::hypot(proyectilActual->getVx(), proyectilActual->getVy());
    if (ganador != 0 || tiempoVuelo >= TIEMPO_MAXIMO
        || (huboChoque && rapidez < VELOCIDAD_MINIMA))
        terminarTurno();

    return R;
}

void juego::terminarTurno()
{
    vuelo = false;
    jugadorActual = (jugadorActual == 1) ? 2 : 1;
}

void juego::revisarVictoria()
{
    // gana el jugador contrario al dueno del representante destruido
    for (obstaculo *o : Obstaculos)
        if (o->esRepresentante() && o->estaDestruido())
            ganador = 3 - o->getDueno();
}