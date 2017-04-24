#ifndef AFIN_H
#define AFIN_H
#include <iostream>
#include <vector>
#include "Funciones_Matematicas.h"
#include <stdlib.h>
#include <time.h>

using namespace std;
class Afin
{
    int clave_a, clave_b, clave_privada;
    string alfabeto;
public:
    Afin();
    Afin(int clave_a, int clave_b);
    string cifrar(string mensaje);
    string descifrar(string mensaje_c);

};

#endif // AFIN_H
