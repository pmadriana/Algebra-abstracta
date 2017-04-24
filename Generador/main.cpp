#include <iostream>
#include <vector>
#include <NTL/ZZ.h>
#include <stdlib.h>

using namespace NTL;
using namespace std;

void corrimiento_derecha(vector <int> &vec, int indice, int elementos, int vueltas)
{
    for(int j = vueltas; j > 0; j--)
    {
        for(int i = elementos + indice - 1; i > indice; i--)
        {
            int temp = vec[i];
            vec[i] = vec[i - 1];
            vec[i - 1] = temp;
        }
    }
}
void corrimiento_izquierda(vector <int> &vec, int indice, int elementos, int vueltas)
{
    for(int j = vueltas; j > 0; j--)
    {
        for(int i = indice; i < indice + elementos - 1; i++)
        {
            int temp = vec[i];
            vec[i] = vec[i + 1];
            vec[i + 1] = temp;
        }
    }
}
ZZ convertir_decimal(vector <int> a, int bits_num)
{
    ZZ num;
    num = 0;
    int e = 0;
    for(int i = bits_num - 1; i >= 0; i--)
    {
        if(a[i]==1)
        {
            num += power2_ZZ(e);
        }
        else
            num += to_ZZ(0);
        e += 1;
    }
    return num;
}
ZZ generador(long int t_seed, int t_bits, int particiones, int vueltas)
{
    ZZ seed_aleatoria;
    seed_aleatoria=RandomLen_ZZ(t_seed);
//    cout<<seed_aleatoria<<endl;
    vector <int>binario;
    for(int i=t_seed-1; i>=0; i--){
        binario.push_back(bit(seed_aleatoria, i));
    }
    int s=0;
    for(int i = t_seed; i < t_bits; i++)
    {
        binario[i] = binario[s] ^ binario[s+1];
        s++;
    }
    int bin;
//    for(int i=0; i<t_bits; i++)
//        cout<<binario[i];

    int partes=t_bits/particiones;
    int residuo_partes= t_bits%particiones;
    if(residuo_partes!=0)
    {
        partes += 1;
    }
    int indice = 0;
    while(indice < t_bits)
    {
        if((indice + partes) > t_bits)
        {
            if(particiones%2!=0)
            {
                corrimiento_izquierda(binario, indice, residuo_partes, vueltas);
                indice += partes;
            }
            else
                corrimiento_derecha(binario, indice, residuo_partes, vueltas);
                indice += partes;
        }
        corrimiento_izquierda(binario, indice,partes, vueltas);
        indice += partes;
        corrimiento_derecha(binario, indice, partes, vueltas);
        indice += partes;
    }
    ZZ num;
    num = convertir_decimal(binario, t_bits);
    return num;

}

int main()
{
        cout<<generador(4,10,2,2);
}
