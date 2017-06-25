#include "RSA.h"
#include <fstream>

bool se_abrio_archivo=false;

void RSA::generacion_claves(int bits)
    {

        while(ProbPrime(p,10)!=1)
        {
            p=generador(bits/2,bits,8,3);
        }
        while(ProbPrime(q,10)!=1)
        {
            q=generador(bits/2,bits,8,4);
        }
        this->p=p;
        this->q=q;
        cout<<"p: "<<p<<endl;
        cout<<"q: "<<q<<endl;
        this->N= p*q;
        ZZ phi_N;
        phi_N = (p-1)*(q-1);
        ZZ e;
        while(e >= phi_N || euclides(e, phi_N)!=1)  //e tiene que ser menor a phi_n
            e= generador(bits/2,bits,8,4);
        this->clave_publica=e;
        cout<<"N: "<<N<<endl;
        cout<<"Clave publica: "<<clave_publica<<endl;
        ZZ inv_e;
        this->clave_privada = modinv(e, phi_N);
        cout<<"clave privada: "<<clave_privada<<endl;
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

    string RSA::firma(string cifrado, string firma ) //usa otras claves que tengo que enviar, N Y d
    {
        /////////////////////
        ZZ RMF, R, len_n_receptor,a; //rubrica mensaje firmado
        ZZ pos;  //pos_aux ->w;
        string pos_s, originales, bloques, resultado1, bloque_cifrado;
        ZZ digitos_len=to_ZZ(to_string(N).size()-1);
        len_n_receptor= to_ZZ(to_string(N_2).size()-1);
            for(int i=0; i<firma.size() ;i++)
            {
                pos = alfabeto.find(firma[i]);
//                R=expo_modular(to_ZZ(pos), this->clave_privada, this->N);
                pos_s=to_string(pos);
                if(pos<10)//pos < to_ZZ(alfabeto.size()-1) - pos_s.size()) //arreglar
                {
                    pos_s = "0"+ pos_s; //completar digitos
                }
                originales += pos_s;
            }
            cout<<"letras "<<originales<<endl;
            while(modulo(to_ZZ(originales.size()), digitos_len)!= 0)
            {
                originales = "0" + originales;
            }
            cout<<"letras con 0: "<<originales<<endl;
//            cout<<len_n_receptor<<endl;
            for(int i=0; i<originales.size(); i += to_int(digitos_len)){
//                bloques = originales.substr(i, to_int(digitos_len));
                pasar_de(a,originales.substr(i, to_int(digitos_len) )); //pasar bloques a ZZ
//                cout<<"bloques orig: "<<a<<endl;
                R=expo_modular((a), this->clave_privada, this->N);
                cout<<"bloques cifrados: "<<R<<endl;
                bloque_cifrado = to_string(R);
                string ceros(to_int(digitos_len+1)-bloque_cifrado.size(), '0'); //constructor
                resultado1 += ceros.append(bloque_cifrado);

            }
            cout<<"primer cifrado: "<<resultado1<<endl;
            while(modulo(to_ZZ(resultado1.size()), len_n_receptor)!=0)
            {
                resultado1 = "0" + resultado1;
            }
            cout<<"con 0 del receptor: "<<resultado1<<endl;
            ZZ bloque,str;
            string cif, res;
            for(int i=0; i<resultado1.size() ; i+= to_int(len_n_receptor))
            {
                pasar_de(str,resultado1.substr(i, to_int(len_n_receptor)));
                bloque=expo_modular(str, publica2, N_2);
                cif=to_string(bloque);
                while(modulo(to_ZZ(cif.size()), len_n_receptor+1)!=0)
                {
                    cif = "0" + cif;
                }
//                cout<<"block "<<cif<<endl;
                res+=cif;
            }
            res+=cifrado;
            return res;

            ////descifrado
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
            if(pos<10)//pos < to_ZZ(alfabeto.size()-1) - pos_s.size()) //arreglar
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

    string RSA::descifrar(string mensaje_c, int digitos_firma)
    {

        ZZ digitos_len=to_ZZ(to_string(this->N).size());
        ZZ digitos_letra= to_ZZ(to_string(to_ZZ(alfabeto[alfabeto.size()-1])).size());
        ZZ bloque, r, res;
        string result, results, descifra, results_firma, resultado_final;
//
        for(int i=0; i<digitos_firma; i+= to_int(digitos_len))
        {
            pasar_de(bloque,mensaje_c.substr(i, to_int(digitos_len)));
//            r=trc(this->p,this->q,this->clave_privada,bloque);
            cout<<bloque<<endl;
            r=expo_modular(bloque, this->clave_privada, this->N);
            cout<<r<<endl;
            result = to_string(r);
            string ceros(to_int(digitos_len-1)-result.size(), '0');
            results_firma += ceros.append(result);
        }
        cout<<results_firma<<endl; //descif normal
        int firma_= results_firma.size();
        for(int i=digitos_firma; i<mensaje_c.size(); i+= to_int(digitos_len))
        {
            pasar_de(bloque,mensaje_c.substr(i, to_int(digitos_len)));
//            r=trc(this->p,this->q,this->clave_privada,bloque);
//            cout<<bloque<<endl;
            r=expo_modular(bloque, this->clave_privada, this->N);
//            cout<<r<<endl;
            result = to_string(r);
            string ceros(to_int(digitos_len-1)-result.size(), '0');
            results += ceros.append(result);
        }
//        cout<<"sin firma oe: "<<results<<endl;
        for(int i=0; i<results.size(); i+= to_int(digitos_letra))
        {
           pasar_de(res,results.substr(i, to_int(digitos_letra)) );
           descifra+= alfabeto[to_int(res)];
        }
        cout<<"texto sin firma: "<<descifra<<endl;
        ZZ dos, D;
        ZZ len_n_2= to_ZZ(to_string(N_2).size());
        string descifrado;
        for(int i=results_firma.size(); i>0; i-= to_int(len_n_2)){
//                cout<<"i: "<<i<<endl;
//                cout<<i-to_int(len_n_2)<<endl;
                if(i-to_int(len_n_2)<0)
                {
                     pasar_de(dos,results_firma.substr(0,i));
                }
                else pasar_de(dos,results_firma.substr(i-to_int(len_n_2),to_int(len_n_2)));
                cout<<"bloques cifrados: "<<dos<<endl;
            D=expo_modular(dos,publica2, N_2);
            cout<<"expo mod: "<<D<<endl;
            string ceros(to_int(digitos_len)-to_string(D).size(), '0');
            descifrado = ceros.append(to_string(D)) + descifrado;
            cout<<"palabra descif en nums "<<descifrado<<endl;
        }
        for(int i=0; i<descifrado.size(); i+= to_int(digitos_letra))
        {
           pasar_de(res,descifrado.substr(i, to_int(digitos_letra)) );
           cout<<"bloques de abcd: "<<res<<endl;
           resultado_final+= alfabeto[to_int(res)];
        }
        return resultado_final+descifra;
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
    void RSA::set_E(ZZ e)
    {
        this->clave_publica=e;
    }
    void RSA::set_N2(ZZ n)
    {
        this->N_2=n;
    }
    void RSA::set_E2(ZZ e)
    {
        this->publica2=e;
    }
