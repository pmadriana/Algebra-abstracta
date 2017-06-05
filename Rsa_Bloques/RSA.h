#ifndef RSA_H
#define RSA_H
#include "Generador_Aleatorio.h"
#include "Funciones.h"
#include "string"

using namespace NTL;
using namespace std;



class RSA
{
    ZZ clave_publica, clave_privada, N, p, q;
    std::string alfabeto = "abcdefghijklmnñopqrstuvwxyz ABCDEFGHIJKLMNÑOPQRSTUVWXYZ0123456789.;:-_()@{}+/";
//    string alfabeto= "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
public:
    void generacion_claves(int bits);
    RSA(int bits);
    RSA(ZZ clave_pub ,ZZ N,string);
    void set_p(ZZ p);
    void set_q(ZZ q);
    void set_d(ZZ d);
    void set_N(ZZ n);
    string cifrado(string , string);
    string descifrar(string);
};
