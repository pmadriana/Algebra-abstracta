//#include <iostream>
//#include <vector>
//#include <NTL/ZZ.h>
//#include <stdlib.h>
#include "Generador_Aleatorio.h"
#include "Funciones.h"
#include "RSA.h"
using namespace NTL;
using namespace std;
//class RSA
//{
//    ZZ clave_publica, clave_privada, N;
//    string alfabeto = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.,; ";
//public:
//
//    void generacion_claves()
//    {
//        ZZ p, q;
//
//        while(ProbPrime(p,10)!=1)
//        {
//            p=generador(4,10,2,2);
//        }
//        while(ProbPrime(q,10)!=1)
//        {
//            q=generador(4,12,2,6);
//        }
//        cout<< "primos elegidos: "<<p<<" "<<q<<endl;
//        this->N= p*q;
//        cout<<"N: "<<N<<endl;
//        ZZ phi_N;
//        phi_N = (p-1)*(q-1);
//        cout<<"phi de n: "<<phi_N<<endl;
//        ZZ e;
//        while(e >= phi_N || euclides(e, phi_N)!=1)  //e tiene que ser menor a phi_n
//            e= generador(4,7,4,3);
//        this->clave_publica=e;
//        cout<<"clave publica: "<<clave_publica<<endl;
//        ZZ inv_e;
//        this->clave_privada = modinv(e, phi_N);
//        cout<<"clave priv: "<<clave_privada<<endl;
//
//    }
//    RSA() //receptor
//    {
//        generacion_claves();
//    }
//    RSA(ZZ clave_pub, ZZ N)
//    {
//        this->clave_publica = clave_pub;
//        this->N=N;
//    }
//    vector<ZZ> cifrado(string mensaje)
//    {
////        string alfabeto = "abcdefghijklmnopqrstuvwxyz ";
////        ZZ clave_publica = to_ZZ(7);
////        ZZ N= to_ZZ(527);
//        string cifrado;
//        int pos_nueva;
//        vector<ZZ>results;
//        ZZ pos, C, P;
//        for(int i=0; i<mensaje.size(); i++)
//       {
//            pos = alfabeto.find(mensaje[i]);
//            C  = expo_modular(pos,this->clave_publica,this-> N); //162 congruente con?
//            pos_nueva=to_int(modulo(C, to_ZZ(alfabeto.size())));
//            cifrado += alfabeto[pos_nueva];
//            results.push_back(C);
//       }
//       cout<<cifrado<<endl;
//       return results;
//
//    }
//
//    string descifrar(vector<ZZ>res)
//    {
////        string alfabeto = "abcdefghijklmnopqrstuvwxyz ";
////        ZZ clave_privada = to_ZZ(343);
////        ZZ N= to_ZZ(527);
//        string descifrado;
//        int pos_nueva;
//        ZZ pos, C;
//        for(int i=0; i<res.size(); i++)
//       {
//            pos = res.at(i);
////            cout<<"Pos: "<<pos<<endl;
//            C  = expo_modular(pos,this->clave_privada, this->N),to_ZZ(alfabeto.size());
////            cout<<"c: "<<C<<endl;
//            pos_nueva=to_int(C);
////            cout<<pos_nueva<<endl;
//            descifrado += alfabeto[pos_nueva];
//       }
//       return descifrado;
//
//    }
//};

int main()
{
//    cout<<generador(4,10,2,5);
//    RSA a;
//    string ci=a.Cifrar("si");
//    cout<<ci<<endl;
//    cout<<a.descifrar(ci);
    RSA a;

    vector<ZZ>cifr;
    cout<<"mensaje cifrado: ";
    cifr = a.cifrado("hola que tal ;v");
    cout<<"mensaje descifrado: "<<a.descifrar(cifr);

//    cout<<ci<<endl
//    cout<<descifrar(ci);
//    seed_aleatoria=20;
//    vector <bool> a;
//    for(int i = 0; i < 10; i++)
//    {
//        a.push_back(0);
//    }
//    int j=0;
//    for(int i = 5-1; i >=0; i--)
//    {
//        a[j] = bit(seed_aleatoria,i);
//        j++;
//    }
//     for(int i=0; i<a.size(); i++)
//        cout<<a[i];
//    vector<bool>a;
//    a.push_back(1);
//    a.push_back(0);
//    a.push_back(0);
//    a.push_back(1);
//    a.push_back(1);
//    a.push_back(0);
//    a.push_back(1);
//    a.push_back(0);
//    cout<<decimal(a, 8);
//    corre(a,2,1);
//    for(int i=0; i<a.size(); i++)
//        cout<<a[i];
//    corrimiento_izquierda(a,0,4,5);
}
