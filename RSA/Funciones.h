#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector>
#include <NTL/ZZ.h>
using namespace NTL;

ZZ modulo(ZZ a, ZZ n);
ZZ euclides(ZZ a, ZZ b);
std::vector <ZZ> euclides_extendido(ZZ a, ZZ b);
ZZ modinv(ZZ a, ZZ alfabeto);
ZZ expo_modular(ZZ a, ZZ b, ZZ modu);
ZZ euler(ZZ n);


#endif // FUNCIONES_H
