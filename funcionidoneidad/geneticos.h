#ifndef GENETICOS_H_INCLUDED
#define GENETICOS_H_INCLUDED
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<iterator>
#include<map>
using namespace std;

class Estado{
public:
  int tableroConReinasCadaFila[8][8];
  int cantidadFilasColumnas;
  map<int,int> posicionesReinasAtacandose;

  Estado(){
    cantidadFilasColumnas=8;
    for(int i=0;i<cantidadFilasColumnas;i++){
      for(int j=0;j<cantidadFilasColumnas;j++){
        if(i==0){
          tableroConReinasCadaFila[i][j]=1;
          continue;
        }
        tableroConReinasCadaFila[i][j]=0;
      }
    }
  };
  int verificarColumnasConReina(int columna){
    for(int i=0;i<cantidadFilasColumnas;i++){
      if(tableroConReinasCadaFila[i][columna]==1){
        return i;
      }
    }
    return -1;
  };
  void generarEstadoAleatorioParaTablero(){
    //genera aleatorio entre 0 y 7
    int aleatorio=0;
    srand((unsigned) time(0));
    for(int j=0;j<cantidadFilasColumnas;j++){
      aleatorio = rand()%8;
      if(verificarColumnasConReina(j)!=-1){
          tableroConReinasCadaFila[verificarColumnasConReina(j)][j]=0;
          tableroConReinasCadaFila[aleatorio][j]=1;
      }else{
        tableroConReinasCadaFila[aleatorio][j]=1;
      }
    }
  };
  void imprimpirMatriz(){
    for(int i=0;i<cantidadFilasColumnas;i++){
      for(int j=0;j<cantidadFilasColumnas;j++){
        cout<< tableroConReinasCadaFila[i][j]<<'\t';
      }
      cout<<endl;
    }
  };
  //FUNCIONES PRIMARIAS
  int verificarCantidadDeParesReinasAtacandoseMismaFila(int fila){
    int contador=0;
    for(int j=0;j<cantidadFilasColumnas;j++){
      if(tableroConReinasCadaFila[fila][j]==1){
        contador++;
      }
    }
    if(contador==0){
      return contador;
    }
    contador=contador-1;
    return contador;
  };
  int verificarCantidadDeReinasMismaDiagonal(int fila, int columna){
    int sumadorRestador=1;
    //se asume que se le pasa  fila y columna de posicion de reina
    int contadorReinasMismaDiagonal=1;
    int filaSumada=fila;
    int columnaSumada=columna;
    int filaRestada=fila;
    int columnaRestada=columna;
    while((filaSumada<cantidadFilasColumnas&&columnaSumada<cantidadFilasColumnas)||(filaRestada>=0&&columnaRestada>=0)){
      filaSumada = sumadorRestador+filaSumada;
      columnaSumada = sumadorRestador+columnaSumada;
      filaRestada = (sumadorRestador*-1)+filaRestada;
      columnaRestada = (sumadorRestador*-1)+columnaRestada;
      if(filaSumada<8&&filaSumada>=0&&columnaSumada>=0&&columnaSumada<8){
        if(tableroConReinasCadaFila[filaSumada][columnaSumada]==1 && !verificarPosicionYaVisitada(filaSumada,columnaSumada)){
          posicionesReinasAtacandose.insert(pair<int,int> (filaSumada,columnaSumada));
          posicionesReinasAtacandose.insert(pair<int,int> (fila,columna));
          contadorReinasMismaDiagonal++;
        }
      }
      if(columnaRestada<8&&columnaRestada>=0&&filaRestada<8&&filaRestada>=0){
        if(tableroConReinasCadaFila[filaRestada][columnaRestada]==1 && !verificarPosicionYaVisitada(filaRestada,columnaRestada)){
          posicionesReinasAtacandose.insert(pair<int,int> (filaRestada,columnaRestada));
          posicionesReinasAtacandose.insert(pair<int,int> (fila,columna));
          contadorReinasMismaDiagonal++;
        }
      }
    }
    if(contadorReinasMismaDiagonal==0){
      return contadorReinasMismaDiagonal;
    }
    contadorReinasMismaDiagonal--;
    return contadorReinasMismaDiagonal;
  };
  bool verificarPosicionYaVisitada(int fila, int columna){
    map<int,int>::iterator iterador;
    for(iterador=posicionesReinasAtacandose.begin();iterador!=posicionesReinasAtacandose.end();++iterador){
      if(iterador->first==fila && iterador->second==columna){
        return true;
      }
    }
    return false;
  };
  //FUNCION IDONEIDAD
  int funcionIdoneidad(){
    int sumadorCantidadReinasMismaFila=0;
    int sumadorMismaDiagonal=0;
    int sumador=0;
    for(int i=0;i<cantidadFilasColumnas;i++){
      sumadorCantidadReinasMismaFila+=verificarCantidadDeParesReinasAtacandoseMismaFila(i);
      for(int j=0;j<cantidadFilasColumnas;j++){
        if(tableroConReinasCadaFila[i][j]==1){
          sumadorMismaDiagonal+=verificarCantidadDeReinasMismaDiagonal(i,j);
        }
      }
    }
    sumador=8-sumadorCantidadReinasMismaFila-sumadorMismaDiagonal;
    return sumador;
  };
};

#endif // GENETICOS_H_INCLUDED
