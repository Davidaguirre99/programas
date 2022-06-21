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
  //visitados.nuevoElemento(n);
  //Creo variables para debug
  int c=0;
  int m=0;
  int b=1;
  int chijo=0;
  int mhijo=0;
  int bhijo=0;
  int cantidadNodosFrontera=0;
  //Lleno cuantos nodos hay en frontera
  cantidadNodosFrontera=frontera.cantidadElementosFrontera;
  //Mientras que haya un elemento en la frontera
  while(cantidadNodosFrontera>0){
    Nodo* nodoActual;
    nodoActual=frontera.elementosFrontera[0];
    //Se asginan estos elementos para debug
    c=nodoActual->estado.cmb[0];
    m=nodoActual->estado.cmb[1];
    b=nodoActual->estado.cmb[2];
    if(nodoActual->esEstadoObjetivo()){
      return nodoActual;
    }
    frontera.eliminarElemento(nodoActual);
    cantidadNodosFrontera=frontera.cantidadElementosFrontera;
    nodoActual->funcionSucesor();
    nodoActual->printHijos();
    for(int i=0;i<nodoActual->factorRamificacion;i++){
      chijo=nodoActual->hijos[i]->estado.cmb[0];
      mhijo=nodoActual->hijos[i]->estado.cmb[1];
      bhijo=nodoActual->hijos[i]->estado.cmb[2];
      if(visitados.existeNodoEnFrontera(nodoActual->hijos[i])){
        continue;
      }
      frontera.nuevoElemento(nodoActual->hijos[i]);
      frontera.printFrontera();
      cantidadNodosFrontera=frontera.cantidadElementosFrontera;
    }
    if(visitados.existeNodoEnFrontera(nodoActual)){
      continue;
    }
    if(nodoActual->esEstadoObjetivo()){
      return nodoActual;
    }

    visitados.nuevoElemento(nodoActual);
    visitados.printFrontera();
  }
}
int main()
{
    Nodo *nodoActual=NULL;
    Nodo nodoRaiz;
    nodoActual=nodoRaiz.autoApuntador();
    Nodo* respuesta;
    nodoRaiz.estado.printEstado();
    busquedaSolucion(nodoActual)->autoApuntador();
    return 0;
}
