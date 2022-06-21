#ifndef CABECERA_H_INCLUDED
#define CABECERA_H_INCLUDED
#include<iostream>

using namespace std;
class Estado {
public:
    int cmb[3];
    Estado() {
        for(int i=0; i<3; i++) {
            if(i<2) {
                cmb[i]=3;
            } else {
                cmb[i]=1;
            }
        }
    };
    //Funciones
    void printEstado() {
        cout<<"****************************************"<<endl;
        for(int i=0; i<3; i++) {
            cout<<"c[i]="<< cmb[i]<<'\t';
        }
        cout<<"________________________________________";
        for(int i=0;i<3;i++){
            if(i==2){
                if(cmb[i]==1){
                    cout<<"c[i]="<< 1-cmb[i]<<'\t';
                }else{
                  cout<<"c[i]="<< 1+cmb[i]<<'\t';
                }
            }else{
              cout<<"c[i]="<< 3-cmb[i]<<'\t';
            }
        }
        cout<<endl;
        cout<<"**************************************"<<endl;
    };
};
class Nodo {
public:
    Estado estado;
    Nodo *padre;
    Nodo **hijos;
    int factorRamificacion;
    int nivelProfundidad;
    Nodo(){
        padre=NULL;
        hijos=NULL;
        factorRamificacion=0;
        nivelProfundidad=0;
    };
    Nodo* autoApuntador(){
      return this;
    }
    void printAcciones(){
      cout<<"Seleccione la accion que desea aplicar:"<<endl;
      cout<<"1) Llevar(mm)\n 2)Llevar(cc) \n 3)Llevar(c) \n 4)Llevar(m) \n 5)Levar(mc)"<<endl;
    }

    void funcionSucesor() {
        //mm,cc,c,m,mc
        int accion=0;
        printAcciones();
        cin>>accion;
        int factor=1;
        if(estado.cmb[2]==1) {
          factor=-1;
        }
        switch(accion) {
          case 1:
            if(estado.cmb[1]>=2) {
              estado.cmb[1]=estado.cmb[1]+2*factor;
              estado.cmb[2]+=factor;
            }
            break;
          case 2:
            if(estado.cmb[0]>=2) {
              estado.cmb[0]=estado.cmb[0]+2*factor;
              estado.cmb[2]+=factor;
            }
            break;
          case 3:
            if(estado.cmb[0]>0) {
              estado.cmb[0]=estado.cmb[0]+1*factor;
              estado.cmb[2]+=factor;
            }
            break;
          case 4:
            if(estado.cmb[1]>0) {
              estado.cmb[1]=estado.cmb[1]+1*factor;
              estado.cmb[2]+=factor;
            }
            break;
          case 5:
            if(estado.cmb[0]>0&&estado.cmb[1]>0) {
              estado.cmb[0]=estado.cmb[0]+1*factor;
              estado.cmb[1]=estado.cmb[1]+1*factor;
              estado.cmb[2]+=factor;
            }
            break;
          default:
            break;
        }
    };
  void agregarHijo(Nodo* hijo){
    Nodo** resguardoHijos;

  }
  bool esEstadoObjetivo(){
    if(estado.cmb[0]==0&&estado.cmb[1]==0&&estado.cmb[2]==0){
      return true;
    }else{
      return false;
    }
  }

};
class Frontera{
public:
  Nodo **elementosFrontera;
  int cantidadElementosFrontera;

};
class Visitados{
public:
  int cantidadElementosVisitados;
  Nodo** nodosVisitados;
  Visitados(){
    cantidadElementosVisitados=0;
    nodosVisitados=NULL;
  }

};

#endif // CABECERA_H_INCLUDED
