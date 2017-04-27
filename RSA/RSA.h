#ifndef RSA_H
#define RSA_H
#include "Generador_Aleatorio.h"
#include "Funciones.h"

using namespace NTL;
using namespace std;

class RSA
{
    ZZ clave_publica, clave_privada, N;
    string alfabeto = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.,; ";
public:
    void generacion_claves();
    RSA();
    RSA(ZZ , ZZ );
    vector<ZZ> cifrado(string );
    string descifrar(vector<ZZ>);
};

#endif // RSA_H
