#include "RSA.h"
#include <fstream>

bool se_abrio_archivo=false;

void RSA::generacion_claves(int bits)
    {

        while(ProbPrime(p,10)!=1)
        {
            p=generador(500,bits,8,3);
        }
        while(ProbPrime(q,10)!=1)
        {
            q=generador(500,bits,8,4);
        }
        this->p=p;
        this->q=q;
//        cout<<"p: "<<p<<endl;
//        cout<<"q: "<<q<<endl;
        this->N= p*q;
        ZZ phi_N;
        phi_N = (p-1)*(q-1);
        ZZ e;
        while(e >= phi_N || euclides(e, phi_N)!=1)  //e tiene que ser menor a phi_n
            e= generador(500,bits,8,4);
        this->clave_publica=e;
//        cout<<"N: "<<N<<endl;
//        cout<<"Clave publica: "<<clave_publica<<endl;
        ZZ inv_e;
        this->clave_privada = modinv(e, phi_N);
//        cout<<"clave privada: "<<clave_privada<<endl;
    }

    RSA::RSA(int bits) //emisor
    {
        generacion_claves(bits);
    }
    RSA::RSA(ZZ clave_pub, ZZ N, string nombre) //receptor
    {
        clave_publica = clave_pub;
        this->N=N;
        ofstream text  ; //static?
        if(se_abrio_archivo==false){
            text.open("claves.txt");
        }
        else
            text.open("claves.txt",ios::app);

        if(text.is_open())
        {
            text<<nombre<<' '<<clave_pub<<' '<<N<<'\n';
        }
        se_abrio_archivo=true;
        text.close();
    }

     string RSA::cifrado(string mensaje, string nombre)
     {
        ZZ clave_publica_otro, N_otro;
        string buscador, clave_publica_otro1, N_otro1;
        ifstream text;
        text.open("claves.txt");
        if(!text.is_open())
            cout<<"no se encontro";
        do
        {
            text>>buscador>>clave_publica_otro1>>N_otro1;

        }while(nombre != buscador);
        pasar_de(clave_publica_otro,clave_publica_otro1);
        pasar_de(N_otro, N_otro1);

        int pos;  //pos_aux ->w;
        string pos_s, originales;
        ZZ digitos_len = to_ZZ(to_string(N_otro).size()-1);

        for(int i=0; i<mensaje.size(); i++)
        {
            pos = alfabeto.find(mensaje[i]);
            pos_s= to_string(to_ZZ(pos));
            if(pos<10)
            {
                pos_s = "0"+ pos_s; //completar digitos
            }
            originales += pos_s;
        }

        while(modulo(to_ZZ(originales.size()), digitos_len)!= 0)
        {
            originales += to_string(to_ZZ(alfabeto.find("w")));
        }

        string bloques, bloque_cifrado, resultado;
        ZZ a, C;
        for(int i=0; i<originales.size(); i += to_int(digitos_len)){
            bloques = originales.substr(i, to_int(digitos_len) );

            pasar_de(a,bloques); //pasar bloques a ZZ

            C= expo_modular(a,clave_publica_otro,N_otro);

            bloque_cifrado = to_string(C);
            string ceros(to_int(digitos_len+1)-bloque_cifrado.size(), '0'); //constructor
            resultado += ceros.append(bloque_cifrado);

        }

        return resultado;


    }

    string RSA::descifrar(string mensaje_c)
    {

        ZZ digitos_len=to_ZZ(to_string(this->N).size());

        ZZ digitos_letra= to_ZZ(to_string(to_ZZ(alfabeto[alfabeto.size()-1])).size());
        ZZ bloque, r, res;
        string result, results, descifra;

        for(int i=0; i<mensaje_c.size(); i+= to_int(digitos_len))
        {
            pasar_de(bloque,mensaje_c.substr(i, to_int(digitos_len)));
            r=trc(this->p,this->q,this->clave_privada,bloque);
            result = to_string(r);
            string ceros(to_int(digitos_len-1)-result.size(), '0');
            results += ceros.append(result);
        }

        for(int i=0; i<results.size(); i+= to_int(digitos_letra))
        {
           pasar_de(res,results.substr(i, to_int(digitos_letra)) );
           descifra+= alfabeto[to_int(res)];
        }
        return descifra;

    }

     void RSA::set_p(ZZ p)
    {
        this->p=p;
    }
    void RSA::set_q(ZZ q)
    {
        this->q=q;
    }
    void RSA::set_d(ZZ d)
    {
        this->clave_privada=d;
    }
    void RSA::set_N(ZZ n)
    {
        this->N=n;
    }

