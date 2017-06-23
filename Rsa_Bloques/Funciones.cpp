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
vector<ZZ> modulo_vec(ZZ a, ZZ n){ //a mod n
	ZZ q, r;
	vector<ZZ> result;
	q = a/n;
	r = a - (q*n);
	if (r<0)
		r += n;
	result.push_back(q);
	result.push_back(r);
	return result; //.first = cociente, .second = remainder
}
vector<ZZ> euclidesex_vec(ZZ a, ZZ b){
	vector<ZZ> result;
	ZZ u = to_ZZ(1), g = a, x = to_ZZ(0), y = b, s, t, q, v;

	if (b == 0){
		result.push_back(a);
		result.push_back(to_ZZ(1));
		result.push_back(to_ZZ(0));
		return result;
	}
	vector<ZZ> division;
	while (y != 0){
		division = modulo_vec(g, y);
		q = division[0];
		t = division[1];
		s = u - q*x;
		u = x;
		g = y;
		x = s;
		y = t;
	}
	v = (g - a*u)/b; //0/0
	if (u < 0)
		u += b;
	result.push_back(g);
	result.push_back(u);
	result.push_back(v);
	return result;
}

ZZ inversa_vec(ZZ a, ZZ n){
	ZZ x;
	vector<ZZ> euclides = euclidesex_vec(a, n);
	x = euclides.at(1);
	if (x < 0)
		x = modulo(x, n);
	return x;
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

    ZZ x(INIT_VAL, S.c_str());
    num=x;
}
int getModInt(int d, int a)
{
    int q = d/a;
    int r = d-(q*a);
    if(r<0){
        r+=a;
    }
    return r;
}
NTL::ZZ potenciacion(NTL::ZZ a, NTL::ZZ b){
	ZZ m, temp;
	ZZ res;
	res = to_ZZ(1);
	m = b;
	while(m != 0){
		if (m == b) temp = a;
		else temp *= temp;
		if (modulo(m, NTL::to_ZZ(2)) == 1)
			res *= temp;
		m/=2;
	}
	return res;
}

ZZ getBase10(vector<bool> binary){
	NTL::ZZ ret;
	int pot = binary.size() - 1;
	for(int i = 0; i < binary.size(); i++, pot--){
		if (binary.at(i))
			ret += potenciacion(NTL::to_ZZ(2), NTL::to_ZZ(pot));
	}
	return ret;
}

vector<bool>DES(){ //le mando un num de 1024 bits, lo partes en 64;
    int pc1[]={57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4};
    int pc2[]={14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32};
    int vueltas[] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

	vector<bool> binary, perm1, perm2, c0, d0, c1d1, res;
	long seed;
	int i;
	ZZ result;
	bool aleatorio_bit_seed= 0;

    seed = time(NULL);
    for (i = 0; i < 64; i++)
    {
        if ((seed & 1) == 1){
            binary.push_back(1);
        } else binary.push_back(0);
        seed >>= 1;
    }
    for(i = 0; i < 56; i++){
        perm1.push_back(binary.at(pc1[i]-1));
    }
    for(i=0; i<28; i++){
        c0.push_back(perm1[i]);
        d0.push_back(perm1[i+28]);
    }

    int first;
    vector<ZZ>results;
    for(int j =0 ;j<16;j++){
            first = c0[0];
            izquierda(c0,28,vueltas[j]);
            c0[27]=first;
            first = d0[0];
            derecha(d0,28,vueltas[j]);
            d0[27]=first;
            for(i=0; i<28 ;i++)
                c1d1.push_back(c0[i]);
            for(i=0; i<28; i++)
                c1d1.push_back(d0[i]);
            for(i=0; i<48; i++){
                perm2.push_back(c1d1.at(pc2[i]-1));
//                res.push_back(perm2.at(i)); //dividir de 48 en 48
            }
//            cout<<c1d1.size()<<endl;
//            cout<<perm2.size()<<endl;
            res=perm2;
            c1d1.clear();
            perm2.clear();
//            cout<<res.size()<<endl;
//            cout<<perm2.size()<<endl;

    }
        return res;

}



