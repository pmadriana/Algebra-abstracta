#include "ElGamal.h"
#include <fstream>

bool se_abrio_archivo=false;
void ElGamal::generacion_claves(int bits)
    {
        ZZ p, q;
//        while(ProbPrime(q,10)!=1)
//        {
            q=generador(bits/2,bits,2,1);
            q = NTL::NextPrime(q, 1);
//        }
//        while(ProbPrime(q,10)!=1)
//        {
//            q=generador(bits/2,bits,8,4);
    //        }
//        q = generador(bits/2, bits, 1, 1);
//        q = NextPrime(q, 1);
        p = (2*q) + 1;
        ZZ e1= find_gen(p); //raiz
        cout<<"p: "<<p<<endl;
        cout<<"e1: "<<e1<<endl;
        ZZ d;

        do
        {
            d=generador(bits/2,bits, 2,1);
        }while (d >= (p-2));

        ZZ e2=expo_modular(e1, d, p);
        cout<<"e2: "<<e2<<endl;
        cout<<"d: "<<d<<endl;
    }

    ElGamal::ElGamal(int bits) //receptor
    {
        generacion_claves(bits);
    }
    ElGamal::ElGamal(ZZ e1, ZZ e2, ZZ p, int bits, string nombre)//emisor
    {
        this->e1=e1;
        this->e2=e2;
        this->p=p;
        ZZ r, C1, Km;
        this->r=generador(bits/2,bits, 2,1);
        while(this->r > (p-2))
        {
            this->r=generador(bits/2, bits, 2,1);
        }
//        cout<<this->r;
        this->C1=expo_modular(this->e1, this->r, this->p);
        this->Km=expo_modular(this->e2, this->r, this->p);
//        cout<<this->C1<<endl;
//        cout<<this->Km<<endl;
        ofstream text  ; //static?
        if(se_abrio_archivo==false){
            text.open("claves.txt");
        }
        else
            text.open("claves.txt",ios::app);

        if(text.is_open())
        {
            text<<nombre<<' '<<this->C1<<' '<<this->Km<<' '<<this->p<<'\n';
        }
        se_abrio_archivo=true;
        text.close();
    }
    string ElGamal::cifrado(string mensaje, string nombre)
    {
        ZZ C1_otro, km_otro, p_otro;
        string buscador, C1_otro1, Km_otro1, p_otro1;
        ifstream text;
        text.open("claves.txt");
        if(!text.is_open())
            cout<<"no se encontro";
        do
        {
            text>>buscador>>C1_otro1>>Km_otro1>>p_otro1;

        }while(nombre != buscador);
        pasar_de(C1_otro,C1_otro1);
        pasar_de(km_otro, Km_otro1);
        pasar_de(p_otro, p_otro1);
        cout<<"cq: "<<C1_otro<<endl;
//        cout<<km_otro<<endl;
        string pos_s, originales;
        int pos;
        int digitos_alfabeto= (to_string(to_ZZ(alfabeto.size()))).size();
        ZZ digitos_len = to_ZZ(to_string(p_otro).size()-1);
        for(int i=0; i<mensaje.size(); i++)
        {
            pos = alfabeto.find(mensaje[i]);
            pos_s= to_string(to_ZZ(pos));
            if(pos<10)
            {
                pos_s = "0"+ pos_s; //completar digitos
            }
            originales += pos_s;
//            cout<< originales <<" ";
        }
//        cout<<originales<<endl;
////        cout<<endl;
        while(modulo(to_ZZ(originales.size()), digitos_len)!= 0)
        {
            originales += to_string(to_ZZ(alfabeto.find("w")));
        }
//        cout<<originales<<endl;
        string bloques, bloque_cifrado, resultado, C1_str;
        ZZ a, C;
        for(int i=0; i<originales.size(); i += to_int(digitos_len)){
            bloques = originales.substr(i, to_int(digitos_len) );

            pasar_de(a,bloques); //pasar bloques a ZZ

            C= modulo(a*km_otro, p_otro);

            bloque_cifrado = to_string(C);
            string ceros(to_int(digitos_len+1)-bloque_cifrado.size(), '0'); //constructor
            resultado += ceros.append(bloque_cifrado);

        }

//        C1_str= to_string(C1_otro);
//        cout<<C1_otro<<endl;
//
//        C1_str += resultado;
//        return C1_str;
            return resultado;
    }
    void ElGamal::descifrado(string mensaje_cifrado, ZZ c1)
    {
        this->C1=c1;
        this->Km = expo_modular(this->C1, this->d, this->p);
        ZZ km_inv= modinv(this->Km, this->p);
//        cout<<km_inv;
        ZZ size_C1= to_ZZ((to_string(this->C1)).size());
//        cout<<size_C1;
//        string C1_str= to_string(this->C1);
//        C1_str += mensaje_cifrado;
        int digitos_alfabeto= (to_string(to_ZZ(alfabeto.size()))).size();
        ZZ digitos_letra= to_ZZ(to_string(to_ZZ(alfabeto[alfabeto.size()-1])).size());
        ZZ digitos_len=to_ZZ(to_string(this->p).size());


        ZZ bloque_ZZ, P, res;
        string bloque, descifra,result, results;
//        for(int i= to_int(size_C1); i<C1_str.size(); i+=to_int(digitos_len))
//        {
//            bloque=C1_str.substr(i, to_int(digitos_len));
//            pasar_de(bloque_ZZ, bloque);
//            P= modulo(bloque_ZZ*km_inv, this->p);
////            cout<<bloque<<" ";
//            result=to_string(P);
//            string ceros(to_int(digitos_len-1)-result.size(), '0');
//            results += ceros.append(result);
//            results += result;
////            descifra+= alfabeto[to_int(P)];
//        }
            for(int i= 0; i<mensaje_cifrado.size(); i+=to_int(digitos_len))
        {
            bloque= mensaje_cifrado.substr(i, to_int(digitos_len));
            pasar_de(bloque_ZZ, bloque);
            P= modulo(bloque_ZZ*km_inv, this->p);
//            cout<<bloque<<" ";
            result=to_string(P);
            string ceros(to_int(digitos_len-1)-result.size(), '0');
            results += ceros.append(result);
            results += result;
//            descifra+= alfabeto[to_int(P)];
        }
        for(int i=0; i<results.size(); i+= to_int(digitos_letra))
        {
           pasar_de(res,results.substr(i, to_int(digitos_letra)) );
           descifra+= alfabeto[to_int(res)];
        }
        cout<< descifra;

    }
    void ElGamal::set_e1(ZZ e1)
    {
        this->e1=e1;
    }
    void ElGamal::set_e2(ZZ d)
    {
        this->e2=d;
    }
    void ElGamal::set_p(ZZ d)
    {
        this->p=d;
    }
    void ElGamal::set_d(ZZ d)
    {
        this->d=d;
    }
    ZZ ElGamal::get_C1()
    {
        return this->C1;
    }
