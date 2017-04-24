#include <iostream>
#include <vector>
#include  <fstream>
#include "Funciones_Matematicas.h"
#include "Afin.h"
using namespace std;


int main()
{
    ifstream file("text.txt");
    ofstream out("out.txt");
//    int clave_a, clave_b;
//    cout<< "Clave a: ";
//    cin>>clave_a;
//    cout<<"Clave b: ";
//    cin>>clave_b;
    Afin a(12473, 12606);
//    string cifrado;
//    if(file.is_open())
//    {
//        while(getline(file,cifrado))
//        {
//            string c= a.descifrar(cifrado);
//            out<<c<<endl;
//        }
//    }
    cout<<a.descifrar("Oe.uN e±eNFqtuqlNgAsQNGS,NPQslNkwFNOu FqifNQCnRubuNauxRe.uNdwtRFnnFKNvebteHuN")<<endl;
    Afin b;
    string c=a.cifrar("hola");
    cout<<c<<endl;
    cout<<a.descifrar(c);




}
