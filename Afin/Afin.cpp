#include "Afin.h"


Afin::Afin()
{
    srand(time(NULL));
    alfabeto="abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ.;,ñÑ";
    while(euclides(clave_a, alfabeto.size()) != 1)
        clave_a=rand()%100;
    this->clave_a=modulo(clave_a, alfabeto.size());
    this->clave_b = modulo(rand()%100, alfabeto.size());
    this->clave_privada=modinv(clave_a, alfabeto.size());

};

Afin::Afin(int clave_a, int clave_b)
{
    alfabeto="abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ.;,ñÑ";
    this->clave_a= modulo(clave_a, alfabeto.size());
    this->clave_b=modulo(clave_b, alfabeto.size());
    this->clave_privada=modinv(clave_a, alfabeto.size());
}

string Afin::cifrar(string mensaje)
{
    string mensaje_cifrado;
    int pos_nueva_letra;
    for(int i=0;i<mensaje.size();i++)
    {

            int pos= alfabeto.find(mensaje[i]);
            pos_nueva_letra = modulo(modulo((pos*clave_a),alfabeto.size())+clave_b, alfabeto.size());
            mensaje_cifrado += alfabeto[pos_nueva_letra];

    }
    return mensaje_cifrado;
}

string Afin::descifrar(string mensaje_c)
{
    string mensaje_descifrado;
    int pos_nueva_letra;
    for(int i=0;i<mensaje_c.size();i++)
    {
            int pos= alfabeto.find(mensaje_c[i]);
            pos_nueva_letra = modulo(clave_privada*modulo((pos-clave_b),alfabeto.size()), alfabeto.size());
            mensaje_descifrado += alfabeto[pos_nueva_letra];

    }
    return mensaje_descifrado;
}
