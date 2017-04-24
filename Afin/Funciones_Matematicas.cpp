#include "Funciones_Matematicas.h"

int modulo(int a, int n)
    {
        int q=a/n;
        int r= a-(q*n);
        if(r<0)
            return r+n;
        return r;
    }

int euclides(int a, int b)
{
    int r;
    while(b!= 0)
    {
        r= modulo(a,b);
        a=b;
        b=r;
    }
    return a;
}

std::vector<int> euclidesExtendido(int a, int b)
{
    std::vector <int> resultados;
    int r1,s1,t1,r2,s2,t2,q,r;
    r1 = a;
    r2 = b;
    s1 = 1;
    s2 = 0;
    t1 = 0;
    t2 = 1;
    while(r2>0)
    {
        q = r1/r2;

        int r = r1 - q * r2;
        r1 = r2;
        r2 = r;

        int s = s1 - q * s2;
        s1 = s2;
        s2 = s;

        int t = t1 - q * t2;
        t1 = t2;
        t2 = t;

    }
    resultados.push_back(r1);
    resultados.push_back(s1);
    resultados.push_back(t1);
    return resultados;
}

int modinv(int a, int alfabeto)
{
    int x = euclidesExtendido(a,alfabeto)[1];
    if(x<0)
    {
        return modulo(x,alfabeto);
    }
    return x;
}
