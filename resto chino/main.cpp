#include <iostream>
#include <vector>
#include "Funciones.h"
using namespace std;


int resto_chino(int num_ec, vector<int> a, vector<int>m)
{
 //x= a mod m
     for(int i=0; i<num_ec-1;i++){ //verificar que seas primos entre si
        if(m[i]%m[i+1]==0 || m[i+1]%m[i]==0){
            break;
        }
     }
     vector<int>M,q;
     int x=0;
     int P=1;
     for(int i=0;i<num_ec;i++) //hallando P
     {
        P*=m[i];
     }
    for(int i=0;i<num_ec;i++)
    {
        M.push_back(P/m[i]);
        q.push_back(modinv(M[i], m[i]));
        x += (a[i]*M[i]*q[i]);
    {
    x=modulo(x, P);
    return x;

}


int main()
{
    int num_ec=3;
    vector<int>a;
    a.push_back(2);
    a.push_back(3);
    a.push_back(2);
    vector<int>m;
    m.push_back(3);
    m.push_back(5);
    m.push_back(7);
    cout<<resto_chino(num_ec, a, m);
}
