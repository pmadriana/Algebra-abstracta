#include "Funciones.h"

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
    resultados.push_back(r1);
    resultados.push_back(s1);
    resultados.push_back(t1);
    return resultados;
}
ZZ modinv(ZZ a, ZZ alfabeto)
{
    ZZ x = euclides_extendido(a,alfabeto)[1];
    if(x<0)
    {
        return modulo(x,alfabeto);
    }
    return x;
}

ZZ expo_modular(ZZ a,ZZ m,ZZ modu)
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
