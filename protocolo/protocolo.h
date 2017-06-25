#ifndef PROTOCOLO_H
#define PROTOCOLO_H
#include "Funciones.h"
#include "Generador_Aleatorio.h"
#include <iostream>
#include <string>

class Protocolo{
private:

    ZZ clave_publica, clave_privada, N, p1, p2, q,gen,a; //n_2 del otro
	std::string alfabeto = "abcdefghijklmnñopqrstuvwxyz ABCDEFGHIJKLMNÑOPQRSTUVWXYZ0123456789.,;:-_()@{}+/";
	public:
	Protocolo(int bits);
	Protocolo(ZZ e, ZZ N, ZZ gen, ZZ q, ZZ a);
	string cifrado(string mensaje);
	void descifrado(string mensaje_c);
	void setE(ZZ);
	void setN(ZZ); //set N del receptor
	void setQ(ZZ); //set Q del receptor
	void setG(ZZ); //g del receptor
	void setA(ZZ); //a
	void setD(ZZ);

};
