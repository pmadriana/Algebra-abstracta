#include "Generador_Aleatorio.h"

void swap(int i, int j, vector<bool>a)
{
    int temp= a[i];
    a[i] = a[j];
    a[j] =temp;
}
void corrimiento_derecha(vector <bool> bin, int indice, int e_partes, int vueltas)
{
    for(int j = vueltas; j > 0; j--)
    {
        for(int i = e_partes + indice - 1; i > indice; i--)
        {
            swap(i, i-1, bin);
        }
    }
//    for(int i=0; i<bin.size(); i++)
//        cout<<bin[i];
}

void corrimiento_izquierda(vector <bool> vec, int indice, int elementos, int vueltas)
{
    for(int j = vueltas; j > 0; j--)
    {
        for(int i = indice; i < indice + elementos - 1; i++)
        {
            swap(i, i+1, vec);
        }
    }
//     for(int i=0; i<vec.size(); i++)
//        cout<<vec[i];
}

ZZ decimal(vector <bool> b, int bits_num)
{
    ZZ num;
    num = 0;
    int e = 0;
    for(int i = bits_num - 1; i >= 0; i--)
    {
        if(b[i]==1)
            (num += power2_ZZ(e));
        else
            (num += to_ZZ(0));
        e += 1;
    }
    return num;
}

ZZ generador(int t_seed, int t_bits, int particiones, int vueltas)
{
    ZZ seed_aleatoria;
    seed_aleatoria=RandomLen_ZZ(t_seed);
//    cout<<seed_aleatoria<<endl;
    vector <bool>binario;
    for(int i = 0; i < t_bits; i++)
    {
        binario.push_back(0); //llenamos el vector
    }
    int j=0, s=0;   //j pos vector ,s recorre
    for(int i = t_seed-1; i >=0; i--) //i, long bit
    {
        binario[j] = bit(seed_aleatoria,i); // extraer bit
        j++;
    }
    for(int i = t_seed; i < t_bits; i++)
    {
        binario[i] = binario[s] ^ binario[s+1]; //concatenar xor
        s++;
    }

    int partes=t_bits/particiones; //cuantos bits tiene cada part
    int residuo_partes= t_bits%particiones; //por si no es exacto

    int indice=0;
    while(indice < t_bits)
    {
        if((indice + partes*2) > t_bits)
        {
            if(particiones%2!=0)
            {
                corrimiento_izquierda(binario, indice, residuo_partes, vueltas);
                indice += partes;
            }
            else{
                corrimiento_derecha(binario, indice, residuo_partes, vueltas);
                indice += partes;
            }
        }
        corrimiento_izquierda(binario, indice,partes, vueltas);
        indice += partes;
        corrimiento_derecha(binario, indice, partes, vueltas);
        indice += partes;
    }
//     for(int i=0; i<binario.size(); i++)
//    {
//        cout<<binario[i];
//    }
//    cout<<endl;
    ZZ num;
    num = decimal(binario, t_bits);
    return num;

}


