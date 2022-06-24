#include <iostream>
#include "Recursos.h"

using namespace std;


Nodo* busquedaSolucion(Nodo* nodo, int movimientos) {
    //nodo->estado.imprimir();
    //cout<<endl;
    Nodo *aux = NULL;
    Nodo** visitados;
    visitados = new Nodo*[1];
    int numeroVisitados = 0;
    ColaPrioridad cola;
    bool esObjetivo;
    cola.nuevoElemento(nodo);
    visitados[0] = nodo;
    numeroVisitados++;
    while(cola.numeroElementos > 0) {
        //cout<<"Empiezo"<<endl;
        esObjetivo = false;
        aux = cola.eliminarElemento();
        esObjetivo = aux->estado.esObjetivo();
        cout<<endl;
        aux->estado.imprimir();
        //cout<<"Es objetivo"<<esObjetivo<<endl;
        if(esObjetivo) {
            cout<<"Es objetivo"<<endl;
            aux->estado.imprimir();
            break;
        } else {
            //cout<<"Ingreso a else"<<endl;
            aux->funcionSucesor();
            //cout<<"Despues funcion sucesor"<<endl;
            //cout<<"FActor Ramificacion"<<aux->factorRamificacion<<endl;
            for(int i = 0; i < aux->factorRamificacion; i++) {
                bool fueVisitado = false;
                aux->hijos[i]->estado.distanciaManhattan(aux->hijos[i]->movimientos);
                //cout<<"Hijo numero"<<i<<endl;
               // aux->hijos[i]->estado.imprimir();
                for(int j = 0; j < numeroVisitados; j++) {
                    //Verificar si es estado ya fue visitado
                    //cout<<"Verifico si fue visitado: "<<numeroVisitados<<endl;
                    if(visitados[j]->estado == aux->hijos[i]->estado) {
                        //cout<<"Entro a visitados"<<endl;
                        fueVisitado =  true;
                        break;
                    }
                }
                //cout<<"Fue visitado: "<<fueVisitado<<endl;
                //aux->hijos[i]->estado.imprimir();
                if(!fueVisitado) {
                    //cout<<"Dentro de no visitados"<<endl;
                    //aux->hijos[i]->estado.imprimir();
                    aux->hijos[i]->movimientos = movimientos + 1;

                    cola.nuevoElemento(aux->hijos[i]);
                    Nodo** visitadosAuxiliar = new Nodo*[numeroVisitados + 1];
                    for(int j = 0; j < numeroVisitados; j++) {
                        visitadosAuxiliar[j] = visitados[j];
                        visitados[j] = NULL;
                    }
                    visitadosAuxiliar[numeroVisitados] = aux->hijos[i];
                    delete[] visitados;
                    visitados = visitadosAuxiliar;
                    numeroVisitados++;
                }
                //cout<<endl;
            }
        }
    }
    return aux;
}


int main() {
    Nodo raiz;

    Nodo *raizAuxiliar = NULL;

    raizAuxiliar = &raiz;

    //raiz.estado.imprimir();
    //raiz.funcionSucesor();
    //cout<<endl;
    Nodo* resultado = busquedaSolucion(raizAuxiliar, 0);

    //resultado->estado.imprimir();

    return 0;
}
