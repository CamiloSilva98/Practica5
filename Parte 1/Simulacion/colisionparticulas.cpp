#include "colisionparticulas.h"
#include <cmath>

bool colisionparticulas::Hay(const particula &A, const particula &B){
    double Dx = B.getX() - A.getX(); //diferencia de posiciones
    double Dy = B.getY() - A.getY(); //diferencia de posiciones
    double SumaRadios = A.getRadio() + B.getRadio(); //distancia minima necesaria entre los centros que no se crucen los bordes
    //se compara el cuadrado para no calcular la raiz
    return Dx * Dx + Dy * Dy <= SumaRadios * SumaRadios;
}

particula colisionparticulas::Fusionar(const particula &A, const particula &B){
    double m1 = A.getMasa(), m2 = B.getMasa();
    double M = m1 +m2;

    //conservacion del momento lineal: m1*v1 + m2*v2 = (m1+m2)*v'

    double Vx = (m1 * A.getVx() + m2 * B.getVx()) /M;
    double Vy = (m1 * A.getVy() + m2 * B.getVy()) /M;

    //centro de masa
    double X = (m1 * A.getX() + m2 * B.getX()) /M;
    double Y = (m1 * A.getY() + m2 * B.getY()) /M;

    //pi*R^2 = pi*r1^2 + pi*r2^2
    double R = std::sqrt(A.getRadio() * A.getRadio() + B.getRadio() * B.getRadio());
    int Id = (m1 >= m2) ? A.getId() : B.getId();
    return particula(Id, X, Y, Vx, Vy, M, R);
}

std::vector<Fusion>
colisionparticulas::ResolverFusiones(std::vector<particula>&Particulas){
    std:: vector<Fusion>Registro;
    //Al fufusionar cambia el tamaño del vector, asi que se reinicia la busqueda hasta que no haya ningun par chocado
    //La particula nueva es mas grande y puede tocar una tercera

    bool Hubo = true;
    while (Hubo) {
        Hubo = false;
        for (size_t i=0; i < Particulas.size() && !Hubo; i++){
            for (size_t j=i+1; j < Particulas.size() && !Hubo; j++){
                if (!Hay(Particulas[i], Particulas[j]))continue;
                particula Nueva= Fusionar(Particulas[i], Particulas[j]);
                Registro.push_back({Particulas[i].getId(), Particulas[j].getId(), Nueva.getX(), Nueva.getY()});
                Particulas[i] = Nueva; //la nueva ocupa el lugar i
                Particulas.erase(Particulas.begin()+j); //la otra desaparece
                Hubo = true;


             }
        }
    }
    return Registro;
}

double colisionparticulas::EnergiaPerdida(const particula &A, const particula &B){
    //calculamos la energia cinetica 1/2 m v^2
    auto Ec = [](const particula &P){
        return 0.5 * P.getMasa() * (P.getVx()* P.getVx() + P.getVy() * P.getVy());
    };
    return Ec(A) + Ec(B) - Ec(Fusionar(A, B));
}


