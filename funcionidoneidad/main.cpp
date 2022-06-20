#include <iostream>
#include "geneticos.h"
using namespace std;

int main()
{
    Estado estado;
    estado.generarEstadoAleatorioParaTablero();
    estado.imprimpirMatriz();
    int cantidadAtaques=estado.funcionIdoneidad();
    cout<<cantidadAtaques<<endl;
    //estado.imprimpirMatriz();
    return 0;
}
