#include <iostream>
#include "cabecera.h"
using namespace std;

int main()
{

    Nodo nodoRaiz;
    nodoRaiz.funcionSucesor();
    cout<<"Nodo = ";
    nodoRaiz.estado.printEstado();
    cout<<endl;
    return 0;
}
