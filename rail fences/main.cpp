#include <iostream>

using namespace std;

string cifrar_diagonal(string mensaje, int clave)
{
    int dif= 2*clave - 2;
    int j=0;
    int sum=dif;
    int espacios_med=dif;
    string result;
    for(int i=0; i<clave; i++)
    {
        j=i;
        while(j<mensaje.size())
        {
            result += mensaje[j];
            if(espacios_med==0)
                espacios_med=sum;
            j += espacios_med;
            if(sum != espacios_med)
                espacios_med=sum-espacios_med;
        }
        dif= dif-2;
        espacios_med=dif;
    }
    return result;

}
string descifrar(string mensaje, int clave)
{
    int dif= 2*clave - 2;
    int j=0, w=0;
    int sum=dif;
    int espacios_med=dif;
    string result, result2;
    for(int i=0; i<clave; i++)
    {
        j=i;
        while(j < mensaje.size())
        {
            result[j]=mensaje[w];
            w++;
             if(espacios_med==0)
                espacios_med=sum;
            j += espacios_med;
            if(sum != espacios_med)
                espacios_med=sum-espacios_med;
        }
        dif -= 2;
        espacios_med=dif;
    }
    for(int x=0; x<mensaje.size(); x++)
    {
        result2+=result[x];
    }
    return result2;

}
int main()
{
   string a=cifrar_diagonal("hola como estas", 4);
   cout<<a<<endl;
   cout<<descifrar(a, 4);
}

