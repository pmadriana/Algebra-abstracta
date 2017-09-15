#include <iostream>
#include <vector>
using namespace std;
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

vector<int> euclidesExtendido(int a, int b)
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
	/*if(x<0)
	{
		return modulo(x,alfabeto);
	}*/
	return x;
}
void congruencia(int a, int b, int m)
{
	cout<<a<<" x = "<<b<<" mod "<<m<<endl;
	int inversa= modinv(a,m);
	cout<<"inversa de : "<<a<<" mod "<<b<<" = "<<inversa<<endl;
	cout<<inversa<<" * "<<a<<"x = "<<inversa<<" * "<<b<<" mod "<<m<<endl;
	int x= inversa*a;
	int y= inversa*b;
	cout<<endl;
	cout<<"x = "<<"6"<<" mod "<<m<<endl;
	//cout<<x << " = "<<modulo(-6,7)<<" mod "<<m<<endl;
	int mod=modulo(y,7);
	cout<<"soluciones: "<<endl;
	cout<<"...";
	for(int i=-15; i<50;  i++)
	{
		if(modulo(i,m)==mod){
			cout<<i<<", ";
		}
	}
	cout<<"..."<<endl;
	
	
}
int main(int argc, char *argv[]) {
	cout<<"ingrese los numeros: "<<endl;
	int a,b,m;
	cin>>a;
	cin>>b;
	cin>>m;
	congruencia(a,b,m);	
	return 0;
}
