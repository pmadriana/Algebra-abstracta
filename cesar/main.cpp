#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//class CifradoCesar
//{
//     private:
//        int clave;
//        string mensaje;
//    public:
//        Cifrado(){
//            clave = 0;
//            mensaje = " ";
//        }
//        void setClave(int n)
//        {
//            clave=n;
//        }
//        void setMensaje(string n)
//        {
//            mensaje=n;
//        }
//        int getClave()
//        {
//            return clave;
//        }
//        string getMensaje()
//        {
//            return mensaje;
//        }
        int modulo(int a, int n)
        {
            int q=a/n;
            int r= a-(q*n);
            if(r<0)
                return r+n;
            return r;

        }
        void cifrado()
        {
            for(int i=0; i<mensaje.size(); i++)
            {
                if(islower(mensaje[i]) && isalpha(mensaje[i]))
                    mensaje[i]=modulo((mensaje[i] - 'a' + clave), 26)+ 97;
                else if(isupper(mensaje[i]) && isalpha(mensaje[i]))
                    mensaje[i]=modulo((mensaje[i] - 'A' + clave),26)+ 65;
            }
        }
        void descifrado()
        {
            for (int i = 0; i < mensaje.size(); i++)
            {
                if (islower(mensaje[i]) && isalpha(mensaje[i]))
                    mensaje[i] = modulo((mensaje[i] - 'a' - clave), 26) + 97;

                else if (isupper(mensaje[i]) && isalpha(mensaje[i]))
                    mensaje[i] = modulo((mensaje[i] - 'A' - clave), 26)+ 65;
            }
        }
};


int main()
{
//    ofstream file_;
//    file_.open("mytext.txt");
//    if(file_.is_open())
//    {
//        file_<<"gu"<<endl;
//        file_.close();
//    }
//    CifradoCesar obj;
//    int cla;
//    string mnsj;
//    ifstream file_("mytext.txt");
//    if(file_.is_open() )
//    {
//
//        cout << " clave: ";
//        cin >> cla;
//        obj.setClave(cla);
//        while(getline(file_, mnsj)){
//            obj.setMensaje(mnsj);
//            obj.cifrado();
//            cout << obj.getMensaje() << endl;
//        }
//    }
//    file_.close();



    cout<< cifrar("ab");

}

