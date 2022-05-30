#include <iostream>
#include "cabecera.h"
using namespace std;

int main()
{
    Estado estado;
    estado.printEstado();
    estado.funcionSucesor();
    estado.printEstado();
    return 0;
}
