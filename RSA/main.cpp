
#include "Generador_Aleatorio.h"
#include "Funciones.h"
#include "RSA.h"
using namespace NTL;
using namespace std;


int main()
{
    RSA bob;
    RSA alicia(to_ZZ(7), to_ZZ(17),to_ZZ(31), "alicia");

    vector<ZZ>cif = bob.cifrado("Hola Como estas", "alicia");
    
    alicia.descifrar(cif);
    
}

