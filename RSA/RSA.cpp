#include "RSA.h"
#include <fstream>

void RSA::generacion_claves()
    {

        while(ProbPrime(p,10)!=1)
        {
            p=generador(500,1024,7,3);
        }
        while(ProbPrime(q,10)!=1)
        {
            q=generador(500,1024,9,4);
        }
        this->p=p;
        this->q=q;

        this->N= p*q;
        ZZ phi_N;
        phi_N = (p-1)*(q-1);
        ZZ e;
        while(e >= phi_N || euclides(e, phi_N)!=1)  //e tiene que ser menor a phi_n
            e= generador(700,1024,14,8);
        this->clave_publica=e;
//        cout<<"Clave publica: "<<clave_publica<<endl;
//        cout<<"N: "<<N<<endl;
        ZZ inv_e;
        this->clave_privada = modinv(e, phi_N);
//        cout<<"clave privada: "<<clave_privada<<endl;


    }
    RSA::RSA() //emisor
    {
        generacion_claves();
    }
    RSA::RSA(ZZ clave_pub, ZZ p, ZZ q, string nombre) //receptor
    {
        clave_publica = clave_pub;
        p=p;
        q=q;
        N= p*q;
        ZZ phi_N= (p-1)*(q-1);
        clave_privada= modinv(clave_pub,phi_N );

        ofstream text("claves.txt");
        if(text.is_open())
        {
            text<<nombre<<' '<<clave_pub<<' '<<N;
        }
        this->clave_privada = clave_privada;

    }
    ZZ RSA::get_publica()
    {
        return clave_publica;
    }
    ZZ RSA::get_N()
    {
        return N;
    }
    ZZ RSA::getPrivada()
    {
        return clave_privada;
    }
    void RSA:: setN(ZZ n)
    {
        this->N=n;
    }
    vector<ZZ> RSA::cifrado(string mensaje, string nombre)
    {
        string cifrado;
        string buscador; //elementos nombre etc
        int clave_publica_otro, N_otro;
        ifstream text;
        text.open("claves.txt");
        do
        {
            text>>buscador>>clave_publica_otro>>N_otro;
        }while(nombre != buscador);
        int pos_nueva;
        vector<ZZ>results;
        ZZ pos, C, P;
        for(int i=0; i<mensaje.size(); i++)
       {
            pos = alfabeto.find(mensaje[i]);
            C  = expo_modular(pos,to_ZZ(clave_publica_otro),to_ZZ(N_otro)); //162 congruente con?
            pos_nueva=to_int(modulo(C, to_ZZ(alfabeto.size())));
            cifrado += alfabeto[pos_nueva];
            results.push_back(C);
       }
//       cout<<cifrado<<endl;
       for(int i=0; i<results.size(); i++)
            cout<<results[i]<<" ";
       return results;

    }

    string RSA::descifrar(vector<ZZ>res)
    {
//        string alfabeto = "abcdefghijklmnopqrstuvwxyz ";
//        ZZ clave_privada = to_ZZ(343);
//        ZZ N= to_ZZ(527);
        string descifrado;
        int pos_nueva;
        ZZ pos, C;
        for(int i=0; i<res.size(); i++)
       {
            pos = res.at(i);
//            cout<<"Pos: "<<pos<<endl;
            C  = expo_modular(pos,this->clave_privada, this->N),to_ZZ(alfabeto.size());
//            cout<<"c: "<<C<<endl;
            pos_nueva=to_int(C);
//            cout<<pos_nueva<<endl;
            descifrado += alfabeto[pos_nueva];
       }
       cout<<descifrado;
       return descifrado;

    }
