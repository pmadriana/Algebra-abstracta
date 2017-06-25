#include "Protocolo.h"

Protocolo::Protocolo(int bits){
    ZZ phi_N;
    while(ProbPrime(this->q,10)!=1)
    {
        this->q=generador(bits/2,bits,2,1);
    }
    cout<<"q: "<<q<<endl;
//	p = (2*q) + 1;
//    ZZ e1= find_gen(p);
    do{
		this->gen = generador(bits/2, bits, 2, 1);
	}while(this->gen > this->q);
	cout<<"gen: "<<gen<<endl;

	while(ProbPrime(this->p1,10)!=1)
    {
        this->p1=generador(bits/2,bits,2,1);
    }
    cout<<"p1: "<<p1<<endl;
    while(ProbPrime(this->p2,10)!=1)
    {
        this->p2=generador(bits/2,bits,2,1);
    }
    cout<<"p2: "<<p2<<endl;
	this->N = this->p1 * this->p2;
	phi_N = (this->p1 - 1) * (this->p2 - 1);
	ZZ e;
    while(e >= phi_N || euclides(e, phi_N)!=1)  //e tiene que ser menor a phi_n
        e= generador(bits/2,bits,8,4);
    this->clave_publica=e;
    cout<<"clave publica: "<<clave_publica<<endl;
	this->clave_privada = modinv(e, phi_N);
	cout<<"clave privada: "<<clave_privada<<endl;
	do{
		this->a = generador(bits/2, bits, 2, 1); //aleatorio para cifrar
//		cout << "a temp: " << a << endl;
	}while(this->a > this->q);

}
Protocolo::Protocolo(ZZ e, ZZ N, ZZ gen, ZZ q, ZZ a)
{
    this->clave_publica=e;
    this->N=N;
    this->q=q;
    this->gen=gen;
    this->a=a;
}
string Protocolo::cifrado(string mensaje){ //bloques tamaño q:
    ZZ k, Cm, Ca, bloque_ZZ, block;
    string bloque, pos_s, originales, bloque_cifrado, resultado,Ca_str;
    int pos;

	cout<<"a: "<<a<<endl;
	ZZ digitos_q = to_ZZ(to_string(this->q).size());
	cout<<"digitos q: "<<digitos_q<<endl;
	k= expo_modular(this->gen, a, this->q);
	cout<<"K: "<<k<<endl;
	Ca = expo_modular(a, this->clave_publica, this->N);
	cout<<"Ca: "<<Ca<<endl;
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
    cout<<"palabra con 0 alf: "<<originales<<endl;
     while(modulo(to_ZZ(originales.size()), digitos_q)!= 0)
    {
        originales += to_string(to_ZZ(alfabeto.find("w")));
    }
    cout<<"palabra con w: "<<originales<<endl;
    for(int i=0; i<originales.size(); i += to_int(digitos_q)){
        pasar_de(block,originales.substr(i, to_int(digitos_q))); //pasar bloques a ZZ
        cout<<"bloque antes de cifrar: "<<block<<endl;
        Cm = modulo(block*k,q);
        cout<<"bloque cifrado: "<<Cm<<endl;
        bloque_cifrado = to_string(Cm);
        string ceros(to_int(digitos_q)-bloque_cifrado.size(), '0'); //constructor
        resultado += ceros.append(bloque_cifrado);
    }
    cout<<"cifrado: "<<resultado<<endl;
    Ca_str = to_string(Ca);
    int len_Ca= Ca_str.size();
    string c0;
	ZZ digitos_n= to_ZZ(to_string(this->N).size());
	while(len_Ca < digitos_n){
		c0 += "0";
		len_Ca++;
	}
	c0 += Ca_str;
	resultado += c0;
	cout<<"tamanio de Ca: "<<Ca_str.size()<<" "<<digitos_n<<endl;
	cout<<"concatenado: "<< resultado;
	return resultado;

}

    void Protocolo::descifrado(string mensaje_cifrado){
        ZZ digitos_n= to_ZZ(to_string(this->N).size());
        ZZ digitos_q= to_ZZ(to_string(this->q).size());
        ZZ Ca,a,k, k_inv, bloque;
        string Ca_str= mensaje_cifrado.substr(mensaje_cifrado.size()-to_int(digitos_n), to_int(digitos_n));
        pasar_de(Ca, Ca_str);
        a= expo_modular(Ca, this->clave_privada, this->N);
        cout<<"Ca: "<<Ca<<endl;
        cout<<"a: "<<a<<endl;
        k= expo_modular(this->gen, a, this->q);
        cout<<"k: "<<k<<endl;
        k_inv= modinv(k, this->q);
        cout<<"k_inv: "<<k_inv<<endl;
        ZZ r, res;
        string result, results, descifra;
        for(int i=0; i<mensaje_cifrado.size()- to_int(digitos_n); i+= to_int(digitos_q))
        {
            pasar_de(bloque,mensaje_cifrado.substr(i, to_int(digitos_q)));
//            r=trc(this->p,this->q,this->clave_privada,bloque);
//            cout<<bloque<<endl;
            cout<<"bloque sin des: "<<bloque<<endl;
            r=modulo(bloque*k_inv,this->q);
//            cout<<r<<endl;
            result = to_string(r);
            cout<<"bloques: "<<result<<endl;
            string ceros(to_int(digitos_q)-result.size(), '0');
            results += ceros.append(result);
        }
        ZZ digitos_letra= to_ZZ(to_string(to_ZZ(alfabeto[alfabeto.size()-1])).size());
        for(int i=0; i<results.size(); i+= to_int(digitos_letra))
        {
           pasar_de(res,results.substr(i, to_int(digitos_letra)) );
           descifra+= alfabeto[to_int(res)];
        }
        cout<<descifra<<endl;
    }
//

void Protocolo::setN( ZZ n){this->N = n;}
void Protocolo::setQ( ZZ q){this->q = q;}
void Protocolo::setE(ZZ e) {this->clave_publica= e;}
void Protocolo::setG( ZZ g){this->gen = g;}
void Protocolo::setA(ZZ a){this->a= a;}
void Protocolo::setD(ZZ d){this->clave_privada= d;}
