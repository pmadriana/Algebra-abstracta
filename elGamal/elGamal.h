#ifndef ELGAMAL_H
#define ELGAMAL_H
#include "Generador_aleatorio.h"
#include "Funciones.h";
class ElGamal
{
private:
    ZZ e1, e2, d, p, r, C1, Km;
    string alfabeto="abcdefghijklmnñopqrstuvwxyz ABCDEFGHIJKLMNÑOPQRSTUVWXYZ0123456789.;:-_()@{}+/";
public:
    void generacion_claves(int );
    ElGamal(int);
    ElGamal(ZZ e1, ZZ e2, ZZ p, int , string);
    string cifrado(string mensaje, string);
    void descifrado(string mensaje_cifrado, ZZ c1);
    void set_e1(ZZ e1);
    void set_e2(ZZ e2);
    void set_p(ZZ p);
    void set_d(ZZ d);
    ZZ get_C1();

};

#endif // ELGAMAL_H
