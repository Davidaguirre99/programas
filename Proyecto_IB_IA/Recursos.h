#ifndef RECURSOS_H_INCLUDED
#define RECURSOS_H_INCLUDED
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <cstdlib>

using namespace std;

class Estado {
public:
    int puzzle[3][3];
    int heuristica;

    Estado() {
        //generarEstadoInicial();
        generarPuzzleInicial();
        distanciaManhattan(0);
    }

    bool Verifica(int matriz[3][3], int i, int j, int num) {
        for(i=0; i<3; i++) {
            for(j=0; j<3; j++) {
                if(num == matriz[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    void generarPuzzleInicial() {
        int i, j,num;
        srand(time(0));
        int matriz[3][3];
        for(i=0; i<3; i++) {
            for(j=0; j<3; j++) {
                num = rand()%9;
                while(Verifica(matriz,3,3,num)==false) {
                    num = rand()%9;
                }
                matriz[i][j]=num;
            }
        }




        for(i=0; i<3; i++) {
            for(j=0; j<3; j++) {
                puzzle[i][j] = matriz[i][j];
            }
        }
    }

    void generarEstadoInicial() {
        //puzzle = {{0,1,2},{3,4,5},{6,7,8}};
        puzzle[0][0] = 7;
        puzzle[0][1] = 2;
        puzzle[0][2] = 4;
        puzzle[1][0] = 5;
        puzzle[1][1] = 0;
        puzzle[1][2] = 6;
        puzzle[2][0] = 8;
        puzzle[2][1] = 3;
        puzzle[2][2] = 1;
        /*for(int i = 0; i < 3; i++) {
            for(int i = 0; i < 3; i++) {
              puzzle[i][j] =
            }
        }*/
    }

    void operator=(Estado estado) {
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                puzzle[i][j] = estado.puzzle[i][j];
            }
        }
    }

    void operator=(int numero) {
        //Inicializo todo el estado con un numero
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                puzzle[i][j] = numero;
            }
        }
    }

    bool operator==(Estado estado) {
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(puzzle[i][j] != estado.puzzle[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(Estado estado) {
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(puzzle[i][j] != estado.puzzle[i][j]) {
                    return true;
                }
            }
        }
        return false;
    }

    bool esObjetivo() {
        int estadoObjetivo[3][3] = {{0,1,2},{3,4,5},{6,7,8}};
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(puzzle[i][j] != estadoObjetivo[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    void imprimir() {
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                cout<<puzzle[i][j]<<"  ";
            }
            cout<<endl;
        }
    }
    void distanciaManhattan(int movimientos) {
        int estadoObjetivo[3][3] = {{0,1,2},{3,4,5},{6,7,8}};
        int distancia = movimientos;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(puzzle[i][j] != 0) {//Si en la casilla actual no esta un espacio vacio
                    for(int a = 0; a < 3; a++) {
                        for(int b = 0; b < 3; b ++) {
                            //Busco en el estado objetivo el verdadero lugar de la casilla actual (i,j)
                            if(puzzle[i][j] == estadoObjetivo[a][b]) {
                                //Encuentro el verdadero lugar, resto:
                                //i - a (fila en el estado actual - fila en el estado objetivo)
                                //j - b (columna en el estado actual - columna en el estado objetivo)
                                // Y sumo los valores absolutos
                                distancia = distancia + abs(i - a) + abs(j - b); //se calcula la heuristica
                            }
                        }
                    }
                }
            }
        }
        heuristica = distancia;
    }
};

class Nodo {
public:
    Nodo *padre;
    Nodo **hijos; //Puntero de punteros para los hijos
    int factorRamificacion;
    Estado estado; //Almacena el puzzle
    int movimientos;

    Nodo() {
        padre = NULL;
        hijos = NULL;
        factorRamificacion = 0;
        movimientos = 0;
    }

    Nodo* autoApuntador() {//Retorna un puntero a si mismo
        return this;
    };



    void funcionSucesor() {
        int fila = 0;
        int columna = 0;
        // Busco donde esta el 0 (espacio en blanco)
        for(int i=0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(estado.puzzle[i][j] == 0) {
                    fila = i;
                    columna = j;
                }
            }
        }
        /*Movimientos*/
        int dx[] = {-1,1,0,0};
        int dy[] = {0,0,-1,1};

        int numeroHijos = 0;

        for(int i = 0; i < 4; i++) {
            //Calculo el factor de ramificacion de ese nodo
            if(esMovimientoSeguro(fila + dx[i], columna + dy[i])) {
                numeroHijos++;
            }
        }
        expandirHijos(numeroHijos);
        //Realizar los movimientos en cada hijo
        int contador = 0;
        for(int i = 0; i < 4; i++) {
            //Calculo el factor de ramificacion de ese nodo
            if(esMovimientoSeguro(fila + dx[i], columna + dy[i])) {
                int valorTemporal = hijos[contador]->estado.puzzle[fila][columna];
                hijos[contador]->estado.puzzle[fila][columna] = hijos[contador]->estado.puzzle[fila + dx[i]][columna + dy[i]];
                hijos[contador]->estado.puzzle[fila + dx[i]][columna + dy[i]] = valorTemporal;
                contador++;
            }
        }

    }
private:
    void expandirHijos(int numeroHijos) {
        factorRamificacion = numeroHijos;
        hijos = new Nodo*[factorRamificacion];
        for(int i = 0; i < factorRamificacion; i++) {
            hijos[i] = new Nodo();
            hijos[i]->padre = this;
            hijos[i]->estado = estado;
        }
    }

    bool esMovimientoSeguro (int fila, int columna) {
        if(fila >= 0 && fila <= 2 && columna>=0 && columna<=2) {
            //Verifico si al hacer uno de los 4 movimientos sigo dentro de la matriz 3x3
            return true;
        }
        return false;
    }
};

class ColaPrioridad {
public:
    Nodo **elementos;//Arreglo dinamico (puntero de punteros)
    int numeroElementos;

    ColaPrioridad() {
        elementos = NULL;
        numeroElementos = 0;
    }
    ~ColaPrioridad() {
        //Destructor de la clase
        for(int c = 0; c < numeroElementos; c++) {
            elementos[c]=NULL;
        }
        delete[] elementos;
        elementos=NULL;
        numeroElementos=0;
    };

    void nuevoElemento(Nodo *nodo) {
        Nodo **aux; //Arreglo temporal de punteros a nodos (ATPN);
        //cout<<"elemento a añadir"<<endl;
        //nodo->estado.imprimir();
        if(numeroElementos == 0) {
            //cout<<"nuevo elemento"<<endl;
            aux = new Nodo*[numeroElementos + 1];
            aux[0] = nodo;
            elementos = aux;
            //elementos[0]->estado.imprimir();
            numeroElementos ++;
        } else {
            //cout<<"Mas de un elemento"<<endl;
            int indice = 0;
            aux = new Nodo*[numeroElementos + 1];
            for(int i = 0; i < numeroElementos; i++) {
                if(elementos[i]->estado.heuristica >= nodo->estado.heuristica) {
                    indice = i;//Encuentro la posicion correcta en la cola de prioridad en base a la distancia manhattan
                    //cout<<elementos[i]->estado.heuristica<<" >= "<<nodo->estado.heuristica<<endl;
                    //cout<<"Nuevo indice"<<indice<<endl;
                    break;
                }
            }
            int contador = 0;
            //cout<<"Numero de elementos: "<<numeroElementos + 1<<endl;
            for(int i = 0; i < numeroElementos + 1; i++) {
                if(indice != i) {
                    //Copio los elementos que ya existen, dentro del aux
                    aux[i] = elementos[contador];
                    //cout<<"numero: "<<i<<endl;
                    //aux[i]->estado.imprimir();
                    elementos[contador] = NULL;
                    contador++;
                } else {
                    //Añado el nodo en la posicion correcta
                    aux[i] = nodo;
                    //cout<<"numero: "<<i<<endl;
                    //aux[i]->estado.imprimir();
                }
            }
            //elementos[0]->estado.imprimir();
            if(numeroElementos > 0) {
                delete[] elementos;
            }
            elementos = NULL;//Apunto el puntero f a NULL
            elementos = aux; //Copio el contenido de ATPN a APN
            numeroElementos ++;//Actualizo el numero de elementos en la frontera
        }
    }

    Nodo* eliminarElemento() {
        Nodo **aux;  //Arreglo temporal de punteros a nodos (ATPN)
        aux = new Nodo*[numeroElementos - 1];//Asigno dinamicamente nEf-1 elementos en ATPN
        Nodo* eliminado;
        if(numeroElementos != 0) {
            eliminado = elementos[0];
            elementos[0] = NULL;
            for(int i = 0; i < numeroElementos - 1; i ++) {
                aux[i] = elementos[i + 1];
                elementos[i + 1] = NULL;
            }
            delete[] elementos;
            elementos = aux;
            numeroElementos--;
        } else {
            for(int i = 0; i < numeroElementos; i++) {
                aux[i] = NULL;
            }
        }
        return eliminado;
    }

};

#endif // RECURSOS_H_INCLUDED
