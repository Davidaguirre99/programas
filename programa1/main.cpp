#include <iostream>
#include "cabecera.h"
using namespace std;
Nodo* busquedaSolucion(Nodo* n){
  Nodo *temporal;
  temporal=n;
  Frontera frontera;
  Visitados visitados;
  bool fronteraVacia=false;
  int hijosMismoNivel=0;
  frontera.nuevoElemento(n);
  visitados.nuevoElemento(n);
  //Implementacion de la busqueda
  cout<<"frontera inicial = ";
  frontera.elementosFrontera[0]->estado.printEstado();
  while(!fronteraVacia){
      frontera.printFrontera();
      for(int i=0;i<frontera.cantidadElementosFrontera;i++){
        temporal=frontera.elementosFrontera[i];
        if(frontera.elementosFrontera[i]->esEstadoObjetivo()){
          return temporal;
        }else{
          visitados.nuevoElemento(temporal);
          frontera.elementosFrontera[i]->funcionSucesor();
          cout<<"numeor ramificacion";
          cout<<frontera.elementosFrontera[i]->factorRamificacion;
          for(int j=0;j<frontera.elementosFrontera[i]->factorRamificacion;j++){
              bool existe = visitados.existeNodoEnFrontera(temporal->hijos[j]);
              if(!existe){
                  frontera.nuevoElemento(temporal->hijos[j]);
              }
          }
          frontera.eliminarElemento(temporal);

        }
      }
  }
  return temporal;
}
int main()
{

    Nodo *nodoActual=NULL;
    Nodo nodoRaiz;
    nodoActual=nodoRaiz.autoApuntador();
    Nodo* respuesta;
    nodoRaiz.estado.printEstado();
    respuesta = busquedaSolucion(nodoActual)->autoApuntador();
    //respueta=nodoRaiz.funcionSucesor();

    return 0;
}
