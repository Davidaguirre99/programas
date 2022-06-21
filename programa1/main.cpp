#include <iostream>
#include "cabecera.h"
using namespace std;

int main()
{

    Nodo nodoRaiz;
    nodoRaiz.funcionSucesor();
    cout<<"Nodo = ";
    for(int i=0;i<3;i++){
      cout<<nodoRaiz.estado.cmb[i]<<"\t";
    }
    cout<<endl;
    return 0;
}
