#ifndef RSA_H
#define RSA_H
#include "Generador_Aleatorio.h"
#include "Funciones.h"
#include "string"

using namespace NTL;
using namespace std;

class RSA
{
    ZZ clave_publica, clave_privada, N;
    ZZ p, q;
    std::string alfabeto = "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
public:
    void generacion_claves();
    RSA();
    RSA(ZZ , ZZ , ZZ,string);
    ZZ getPrivada();
    ZZ get_publica();
    ZZ get_N();
    void setN(ZZ);
//    vector<ZZ> cifrado(string , string);
    vector<ZZ> cifrado(string,string);
    string descifrar(vector<ZZ>);
};

#endif // RSA_H
