#include "Generador_Aleatorio.h"

void swap(int i, int j, vector<bool>a)
{
    int temp= a[i];
    a[i] = a[j];
    a[j] =temp;
}
void corrimiento_derecha(vector <bool> vec, int indice, int elementos, int vueltas)
{
    srand(time(NULL));
    int pos_aleatoria = rand()% elementos;
    bool bit_ultimo= vec[(elementos*2)-1];
    for(int j =vueltas; j > 0; j--)
    {
        for(int i=(elementos*2)-1-indice ; i>= elementos; i--)
        {
            swap(i, i+1, vec);
        }
    }
    bool x = vec[pos_aleatoria+elementos]^bit_ultimo; //pasar a aleatorio pe
    vec[elementos]= x;
//    for(int i=elementos; i<(elementos*2);i++)
//        cout<<vec[i];
}

void corrimiento_izquierda(vector <bool> vec, int indice, int elementos, int vueltas)
{
    srand(time(NULL));
    int pos_aleatoria = rand()% (elementos-1);
    bool primero = vec[0];
    for(int j = vueltas; j > 0; j--)
    {
        for(int i = 0; i<elementos-1-indice; i++)
        {
            swap(i, i+1, vec);
        }
    }
    bool x= primero^vec[pos_aleatoria];
    vec[elementos-1]=x;
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
int rdtsc() //rand de ciclos utilizados por procesador desde el inicio
{
    __asm__ __volatile__("rdtsc");
}
ZZ generador(int t_seed, int t_bits, int particiones, int vueltas)
{
    vector <bool>binario;
    bool aleatorio_bit_seed= 0;
    for(int i = 0; i < t_bits; i++)
    {
        binario.push_back(0); //llenamos el vector
    }
    int s=0;   //j pos vector ,s recorre
    for(int i = 0 ; i<t_seed; i++)
    {
        srand(rdtsc());
        aleatorio_bit_seed= rand()%2;
        binario[i]= aleatorio_bit_seed;
        if(binario[0]==0)
            binario[0]=1;
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


