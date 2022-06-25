#ifndef CRIPTOARITMÈTICA_H_INCLUDED
#define CRIPTOARITMÈTICA_H_INCLUDED
#include<iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
class Estado{
public:
  int T,W,O,F,U,R,c1,c2,c3;
  Estado(){
    T=0;
    W=0;
    O=0;
    F=0;
    U=0;
    R=0;
    c1=0;
    c2=0;
    c3=0;
  }
  void todosDiferentes(){
    int arreglo[6]={-1,-1,-1,-1,-1,-1};
    bool seRepitio=false;
    srand(time(NULL));
    int aleatorio, posicionRepetido=0;
    while(posicionRepetido<6){
      seRepitio=false;
      aleatorio=rand()%10;
      for(int i=0;i<6;i++){
        if(arreglo[i]==aleatorio){
          seRepitio=true;
          break;
        }
      }
      if(!seRepitio){
        arreglo[posicionRepetido]=aleatorio;
        posicionRepetido++;
      }
    }
    T=arreglo[0];
    W=arreglo[1];
    O=arreglo[2];
    F=arreglo[3];
    U=arreglo[4];
    R=arreglo[5];
  };
  void printEstado(){
    cout<<"T = "<<T<<endl;
    cout<<"W = "<<W<<endl;
    cout<<"O = "<<O<<endl;
    cout<<"F = "<<F<<endl;
    cout<<"U = "<<U<<endl;
    cout<<"R = "<<R<<endl;

  }
};


#endif // CRIPTOARITMÈTICA_H_INCLUDED
