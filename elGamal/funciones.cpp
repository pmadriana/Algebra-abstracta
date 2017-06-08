#include "Funciones.h"

using namespace std;
using namespace NTL;
ZZ modulo(ZZ a, ZZ n)
{
    ZZ q, r;
	q = a / n;
	r = a - (q*n);
	if (r < 0)
		r+=n;
	return r;
}
ZZ euclides(ZZ a, ZZ b)
{
    ZZ r;
	while (b!=0){
		r = modulo(a, b);
		a = b;
		b = r;
	}
	return a;
}

std::vector <ZZ> euclides_extendido(ZZ a, ZZ b)
{
    std::vector <ZZ> resultados;
    ZZ r1,s1,t1,r2,s2,t2,q,r;
    r1 = a;
    r2 = b;
    s1 = 1;
    s2 = 0;
    t1 = 0;
    t2 = 1;
    while(r2>0)
    {
        q = r1/r2;

        ZZ r = r1 - q * r2;
        r1 = r2;
        r2 = r;

        ZZ s = s1 - q * s2;
        s1 = s2;
        s2 = s;

        ZZ t = t1 - q * t2;
        t1 = t2;
        t2 = t;

    }
    resultados.push_back(r1);//mcd
    resultados.push_back(s1);//x
    resultados.push_back(t1);//y
    return resultados;
}
vector<ZZ> criba(int n){
    vector<bool>m(n, true);
    m[0] = false;
    m[1] = false;

    for(int i = 2; i*i <= n; ++i) {
        if(m[i]) { //if (numbers.at(i) == true)
            for(int j = 2; i*j <= n; ++j)
                m[i*j] = false; // numbers.at(j*i) = false;
        }
    }
    vector<ZZ>results;
    for(int i=2; i<=n; i++){
        if(m[i]==true)
            results.push_back(to_ZZ(i));
    }
    return results;
}
ZZ modinv(ZZ e, ZZ n)
{
    while(euclides_extendido(e,n)[0]==1){
        ZZ x = euclides_extendido(e,n)[1];
        if(x<0)
        {
            return modulo(x,n);
        }
        return x;
    }
//     srand(time(NULL));
//     vector<ZZ>crib=criba(10000000);
//    return modinv(e, crib[rand()%crib.size()]);
}
vector <bool> ZZtoBinary(ZZ num)
{
    vector <bool> binario;
    while(num>0)
    {
        binario.push_back(to_int(modulo(num,to_ZZ(2))));
        num = num >> 1;
    }
    return binario;
}

ZZ expo_modular(ZZ a,ZZ m,ZZ modu) //mejorar
{
        ZZ exp;
        exp=1;
        ZZ x=modulo(a,modu);
        while(m>0)
        {
            if((modulo(m, to_ZZ(2)))==1)
            {
                exp=modulo((exp*x),modu);
            }
            x=modulo((x*x),modu);
            m=m/2;
        }
        return exp;
}
//ZZ expo_modular(ZZ a, ZZ b, ZZ n)
//{
//    ZZ d;
//    d = 1;
//    vector <bool> bin = ZZtoBinary(b);
//    for(int i = bin.size(); i > 0; i--)
//    {
//        d = modulo((d * d), n);
//        if(bin[i - 1] == 1)
//        {
//            d = modulo((d * a),n);
//        }
//    }
//    return d;
//
//}

string to_string(ZZ n)
{
    string result;
    stringstream convert;
    convert << n;
    result = convert.str();
    return result;
}

bool verificar_primos(vector<ZZ>a)
{
    for(int i=0; i<a.size(); i++){
        if(a[i]==1) return false;
        for(int j=1+i; j<a.size(); j++)
        {
            if(euclides(a[i],a[j])!=1)
                return false;
        }
    }
    return true;
}

ZZ trc(ZZ p, ZZ q, ZZ d, ZZ C)
{
    ZZ dp, dq, P, a[2], x;
    P = p * q;
    dp= modulo(d, p-1);
    dq= modulo(d, q-1);
    a[0]= expo_modular(C, dp, p);
    a[1]= expo_modular(C, dq, q);
    return x = modulo(modulo((a[0] * q * modinv(q, p)), P) + modulo((a[1] * p * modinv(p, q)), P), P);
}

//void pasar_a(ZZ num,string &S)
//{
//    string nums,d;
//    ZZ temp = num;
//    int x;
//    if(temp == 0){
//        nums.append("0");
//    }
//    while(temp!= 0){
//        x = temp % 10;
//        d = x+'0';
//        nums.insert(0,d);
//        temp = temp/10;
//    }
//    S.append(nums);
//}
void pasar_de(ZZ &num,string S)
{
//    ZZ temp,dig;
//    conv(temp,0);
//    int x;
//    for(unsigned long long int i = 0;i < S.length();i++){
//        temp*=10;
//        x = (S[i]-'0');
//        temp += x;
//    }
//    num = temp;
    ZZ x(INIT_VAL, S.c_str());
    num=x;
}

ZZ find_gen(ZZ p){
	ZZ q, found, g, i;
	q = (p-to_ZZ(1))/2;

//	found=to_ZZ(0);
//	while(found != 1){
	for (i = 1; i < p-1; i++){
		g = p - i;
		if ((modulo(g*g, p) != 1) && (expo_modular(g, q, p) != 1)){
//			found=to_ZZ(1);
        break;
		}
	}
//	}
	return g;

}
