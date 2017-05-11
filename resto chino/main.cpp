#include <iostream>
#include <vector>
using namespace std;

int modulo(int a, int n)
{
    int q, r;
	q = a / n;
	r = a - (q*n);
	if (r < 0)
		r+=n;
	return r;
}
int euclides(int a, int b)
{
    int r;
	while (b!=0){
		r = modulo(a, b);
		a = b;
		b = r;
	}
	return a;
}

vector <int> euclides_extendido(int a, int b)
{
    vector <int> resultados;
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
    int x = euclides_extendido(a,alfabeto)[1];
    if(x<0)
    {
        return modulo(x,alfabeto);
    }
    return x;
}

int resto_chino(int num_ec)
{
 //x= a mod m
 int a[num_ec],m[num_ec],M[num_ec],q[num_ec];
 int x=0;
 for(int i=0;i<num_ec;i++)
 {
   cout<<"a: ";
   cin>>a[i];
 }
 cout<<endl;
 int P=1;
 for(int i=0;i<num_ec;i++)
 {
    cout<<"m: ";
    cin>>m[i];
    P*=m[i];
 }
 for(int i=0; i<num_ec-1;i++){
    if(m[i]%m[i+1]==0 || m[i+1]%m[i]==0){
        cout<<"no son coprimos";
        break;
    }
 }
for(int i=0;i<num_ec;i++)
{
  M[i]=P/m[i];
//  cout<<M[i]<<endl;
  q[i]= modinv(M[i], m[i]);
  x += (a[i]*M[i]*q[i]);
//  cout<<"inverso: "<<q[i]<<endl;
}
cout<<endl;
//cout<<"x: "<<x;

x= x%P;
return x;

}


int main()
{
    int num_ec;
    cout<<" ingrese el numero de ecuaciones : ";
    cin>>num_ec;
    cout<<resto_chino(num_ec);
}

//esta desordenado xd
