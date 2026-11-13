#ifndef PARTICULA_H
#define PARTICULA_H

class particula
{
private:
    int id;
    double x, y;
    double vx, vy;
    double masa;
    double radio;
public:
    particula();
    particula(int id, double x, double y, double vx, double vy, double masa, double radio);

    int getId() const { return id; }
    double getX() const { return x; }
    double getY() const { return y; }
    double getVx() const { return vx; }
    double getVy() const { return vy; }
    double getMasa() const { return masa; }
    double getRadio() const { return radio; }

    void setPosicion(double nx, double ny) { x = nx; y = ny; }
    void setVelocidad(double nvx, double nvy) { vx = nvx; vy = nvy; }
    void setMasa(double m) { masa = m; }
    void setRadio(double r) { radio = r; }

    void mover(double dt, double g = 9.8);
};

#endif // PARTICULA_H

