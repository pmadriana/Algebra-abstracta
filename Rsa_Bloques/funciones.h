#include "Generador_Aleatorio.h"
#include <vector>
#include <string>
#include <sstream>
#include <NTL/ZZ.h>
using namespace NTL;

ZZ modulo(ZZ a, ZZ n);
ZZ euclides(ZZ a, ZZ b);
std::vector <ZZ> euclides_extendido(ZZ a, ZZ b);
std::vector<ZZ> criba(int);
ZZ modinv(ZZ a, ZZ alfabeto);
ZZ expo_modular(ZZ a, ZZ b, ZZ modu);

ZZ euler(ZZ n);
vector <bool> ZZtoBinary(ZZ num);
string to_string(ZZ n);
bool verificar_primos(std::vector<ZZ>);
ZZ trc(ZZ p, ZZ q, ZZ d, ZZ C);
//void pasar_a(ZZ num,string &S);
void pasar_de(ZZ &num,string S);

#endif // FUNCIONES_H
