#ifndef GENERADOR_ALEATORIO_H
#define GENERADOR_ALEATORIO_H
#include <iostream>
#include <vector>
#include <NTL/ZZ.h>
#include <stdlib.h>
#include <time.h>

using namespace NTL;
using namespace std;

void swap(int , int , vector<bool> );
void corrimiento_derecha(vector <bool>, int , int, int );
void corrimiento_izquierda(vector <bool> , int , int , int );
ZZ decimal(vector <bool> , int );
int rdtsc();
ZZ generador(int , int , int , int );

#endif // GENERADOR_ALEATORIO_H

