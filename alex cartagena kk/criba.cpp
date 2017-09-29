#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>

	using namespace std;

//void criba(int n)
//{
//    vector<int>a;
//    for(int i=2; i<=n;i++)
//        a.push_back(1);
//    int raiz=sqrt(n);
//    for(int i=2; i<= raiz; i++){
//        if(a[i]==1)
//        {
//            for(int j=i; j<=n/i; j++)
//                a[i*j]=0;
//        }
//    }
//    for(int i=0; i<=n; i++)
//    {
//        while(a[i]==0)
//            cout<<i;
//    }
//}
void imprimir(int n)
{
	int c=1;
	for(int i=1;i<=n;i++)
	{
		c++;
		if(i>0 && i<11)
			cout<<i<<"  ";
		else cout<<i<<" ";
		if(c>1&& c%10==1)
			cout<<endl;
	}
}

vector<int> criba(int n){
	vector<bool>m(n, true);
	m[0] = false;
	m[1] = false;
	imprimir(n);
	for(int i = 2; i*i <= n; ++i) {
		if(m[i]) { //if (numbers.at(i) == true)
			for(int j = 2; i*j <= n; ++j){
				m[i*j] = false; // numbers.at(j*i) = false;
			}
		}
	}
	char celda=92;
	int c=1;
	cout<<endl;
	///para imprimir
	for(int i=1; i<=m.size(); i++)
	{
		c++;
		if(m[i]==false)
			cout<<celda<<"  ";
		else if(i>0 && i<11)
		   cout<<i<<"  ";
		else cout<<i<<" ";
		
		if(c>1&& c%10==1)
			cout<<endl;
	}
	///
	vector<int>results;
	for(int i=2; i<=n; i++){
		if(m[i]==true)
			results.push_back(i);
	}
	return results;
}

int main()
{
	//    vector<ZZ>crib= criba(10000000); //no funka
	/*  srand(time(NULL));
	vector<ZZ>crib=criba(100000000);
	cout<<crib[rand()%crib.size()];*/
	//    for(int i=0; i<crib.size(); i++)
	//        cout<<crib[i]<<endl;
	//    cout<<modinv(to_ZZ(7),to_ZZ(14));
	cout<<"-----CRIBA DE ERATOSTENES-----"<<endl;
	cout<<endl;
	vector<int>a=criba(100);
	cout<<endl;
	cout<<"Primos: "<<a.size()<<endl;
	for(int i=0; i<a.size();i++)
		cout<<a[i]<<" ";
}
