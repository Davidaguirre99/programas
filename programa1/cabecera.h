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
//    void printAcciones(){
//      cout<<"Seleccione la accion que desea aplicar:"<<endl;
//      cout<<"1) Llevar(mm)\n 2)Llevar(cc) \n 3)Llevar(c) \n 4)Llevar(m) \n 5)Levar(mc)"<<endl;
//    }
//    void funcionSucesor() {
//        //mm,cc,c,m,mc
//        int accion=0;
//        cin>>accion;
//        int factor=1;
//        if(cmb[2]==1) {
//          factor=-1;
//        }
//        switch(accion) {
//          case 1:
//            if(cmb[1]>=2) {
//              cmb[1]=cmb[1]+2*factor;
//              cmb[2]+=factor;
//            }
//            break;
//          case 2:
//            if(cmb[0]>=2) {
//              cmb[0]=cmb[0]+2*factor;
//              cmb[2]+=factor;
//            }
//            break;
//          case 3:
//            if(cmb[0]>0) {
//              cmb[0]=cmb[0]+1*factor;
//              cmb[2]+=factor;
//            }
//            break;
//          case 4:
//            if(cmb[1]>0) {
//              cmb[1]=cmb[1]+1*factor;
//              cmb[2]+=factor;
//            }
//            break;
//          case 5:
//            if(cmb[0]>0&&cmb[1]>0) {
//              cmb[0]=cmb[0]+1*factor;
//              cmb[1]=cmb[1]+1*factor;
//              cmb[2]+=factor;
//            }
//            break;
//          default:
//            break;
//        }
//    };
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
    void funcionSucesor(){
      int cantidadHijos=5;
      int factor=-1;
      int accion[3][5];
      //accion cc
      accion[0][0]=2;
      accion[1][0]=0;
      accion[2][0]=1;
      //accion mm
      accion[0][1]=0;
      accion[1][1]=2;
      accion[2][1]=1;
      //accion mc
      accion[0][2]=1;
      accion[1][2]=1;
      accion[2][2]=1;
      //accion c
      accion[0][3]=1;
      accion[1][3]=0;
      accion[2][3]=1;
      //accion m
      accion[0][4]=0;
      accion[1][4]=1;
      accion[2][4]=1;
      cout<<"Nodo que estoy viendo:";
      estado.printEstado();
      int accionesValidas[5] = {1,1,1,1,1};
      for (int i=0;i<5;i++){
        Estado aux;
        if(estado.cmb[2]==1){
          factor=-1;
        }else{
          factor=1;
        }
        for(int j=0; j<3; j++){
          aux.cmb[j]=estado.cmb[j]+(factor*accion[j][i]);
        }
        int canibalesDerecha=3-aux.cmb[0];
        int misionerosDerecha=3-aux.cmb[1];
        if(aux.cmb[0]>aux.cmb[1]||aux.cmb[0]<0||aux.cmb[1]<0||aux.cmb[0]>3||aux.cmb[1]>3
        ||((canibalesDerecha>misionerosDerecha)&&aux.cmb[1]<3)){//&&aux.cmb[1]<3
          accionesValidas[i]=0;
          cantidadHijos--;
        }
      };
      //Se expanden los nodos hijos posibles de las acciones validadas anteriormente
      expandir(cantidadHijos);
      //Se setea los arreglos de los hijos en base a las acciones
      int contador=0;
      for(int i=0;i<5;i++){
        if(accionesValidas[i]==1){
          for(int j=0;j<3;j++){
            hijos[contador]->estado.cmb[j]=hijos[contador]->estado.cmb[j]+(factor*accion[j][i]);
          }
          contador++;
        }
      }

    };
  void expandir(int nhijos){
    factorRamificacion=nhijos;
    hijos = new Nodo*[factorRamificacion];
    for(int i=0;i<factorRamificacion;i++){
      hijos[i]=new Nodo;
      hijos[i]->padre=this;
      hijos[i]->nivelProfundidad=nivelProfundidad+1;
      hijos[i]->estado=estado;
    }
  };
  void eliminarArbol(Nodo *nodoApuntado){
    for(int a=0;a<nodoApuntado->factorRamificacion;a++){
      if(nodoApuntado->hijos[a]!=NULL){
        eliminarArbol(nodoApuntado->hijos[a]);
      }
    }
    delete nodoApuntado;
    nodoApuntado=NULL;
  };

  Nodo* hallarRaiz(Nodo *apuntandoANodo){
    Nodo *papa;
    if(apuntandoANodo->padre!=NULL){
      papa=hallarRaiz(apuntandoANodo->padre);
    }else{
      papa=apuntandoANodo;
    }
    apuntandoANodo->estado.printEstado();
    return papa;
  };

  bool esEstadoObjetivo(){
    if(estado.cmb[0]==0&&estado.cmb[1]==0&&estado.cmb[2]==0){
      return true;
    }else{
      return false;
    }
  };
  void printHijos(){
    cout<<"Padre"<<endl;
    estado.printEstado();
    if(factorRamificacion>0){
      for(int i=0;i<factorRamificacion;i++){
        cout<<"hijo"<<endl;
        hijos[i]->estado.printEstado();
        cout<<endl;
      }
    }
  };
};
class Frontera{
public:
  Nodo **elementosFrontera;
  int cantidadElementosFrontera;
  Frontera(){
    elementosFrontera=NULL;
    cantidadElementosFrontera=0;
  }
  ~Frontera(){
    for(int C=0;C<cantidadElementosFrontera;C++){
      elementosFrontera[C]=NULL;
    }
    delete[] elementosFrontera;
    elementosFrontera=NULL;
    cantidadElementosFrontera=0;
  }
  void nuevoElemento(Nodo *nodoApuntado){
    Nodo **auxiliar;
    auxiliar=new Nodo*[cantidadElementosFrontera+1];
    for(int i=0;i<cantidadElementosFrontera;i++){
      auxiliar[i]=elementosFrontera[i];
      elementosFrontera[i]=NULL;
    }
    auxiliar[cantidadElementosFrontera]=nodoApuntado;
    if(cantidadElementosFrontera>0){
      delete[] elementosFrontera;
    }
    elementosFrontera=NULL;
    elementosFrontera=auxiliar;
    cantidadElementosFrontera++;
  };
  bool eliminarElemento(Nodo *nodoAEliminar){
    bool resultado=false;
    Nodo **auxiliar;
    auxiliar= new Nodo*[cantidadElementosFrontera-1];
    int pos=-1;
    for(int i=0;i<cantidadElementosFrontera;i++){
      if(nodoAEliminar==elementosFrontera[i]){
        pos=i;
        resultado=true;
        break;
      }
    }
    if(pos!=-1){
      for(int i=0;i<pos;i++){
        auxiliar[i]=elementosFrontera[i];
        elementosFrontera[i]=NULL;
      }
      for(int i=pos;i<cantidadElementosFrontera-1;i++){
        auxiliar[i]=elementosFrontera[i+1];
        elementosFrontera[i+1]=NULL;
      }
      delete[] elementosFrontera;
      elementosFrontera=NULL;
      elementosFrontera=auxiliar;
      cantidadElementosFrontera--;
    }else{
      for(int i=0;i<cantidadElementosFrontera-1;i++){
        auxiliar[i]==NULL;
      }
      delete[] auxiliar;
      auxiliar=NULL;
    }
    return resultado;
  };
  bool existeNodoEnFrontera(Nodo *nodoAValidar){
    if(cantidadElementosFrontera>0){
      for(int i=0;i<cantidadElementosFrontera;i++){
        if(nodoAValidar==elementosFrontera[i]){
          return true;
        }
      }
      return false;
    }else{
      return false;
    }

  };
  void printFrontera(){
    cout<<"{\t";
    if(cantidadElementosFrontera>0){
      for(int i=0;i<cantidadElementosFrontera;i++){
        cout<<"[ ";
        elementosFrontera[i]->estado.printEstado();
        cout<<" ]";
      }
      cout<<endl;
    }
    cout<<"}\n";
  };
};
class Visitados{
public:
  int cantidadElementosVisitados;
  Nodo** nodosVisitados;
  Visitados(){
    cantidadElementosVisitados=0;
    nodosVisitados=NULL;
  }
   void nuevoElemento(Nodo *nodoApuntado){
    Nodo **auxiliar;
    auxiliar=new Nodo*[cantidadElementosVisitados+1];
    for(int i=0;i<cantidadElementosVisitados;i++){
      auxiliar[i]=nodosVisitados[i];
      nodosVisitados[i]=NULL;
    }
    auxiliar[cantidadElementosVisitados]=nodoApuntado;
    if(cantidadElementosVisitados>0){
      delete[] nodosVisitados;
    }
    nodosVisitados=NULL;
    nodosVisitados=auxiliar;
    cantidadElementosVisitados++;
  };
  bool eliminarElemento(Nodo *nodoAEliminar){
    bool resultado=false;
    Nodo **auxiliar;
    auxiliar= new Nodo*[cantidadElementosVisitados-1];
    int pos=-1;
    for(int i=0;i<cantidadElementosVisitados;i++){
      if(nodoAEliminar==nodosVisitados[i]){
        pos=i;
        resultado=true;
        break;
      }
    }
    if(pos!=-1){
      for(int i=0;i<pos;i++){
        auxiliar[i]=nodosVisitados[i];
        nodosVisitados[i]=NULL;
      }
      for(int i=pos;i<cantidadElementosVisitados-1;i++){
        auxiliar[i]=nodosVisitados[i+1];
        nodosVisitados[i+1]=NULL;
      }
      delete[] nodosVisitados;
      nodosVisitados=NULL;
      nodosVisitados=auxiliar;
      cantidadElementosVisitados--;
    }else{
      for(int i=0;i<cantidadElementosVisitados-1;i++){
        auxiliar[i]==NULL;
      }
      delete[] auxiliar;
      auxiliar=NULL;
    }
    return resultado;
  };
  bool existeNodoEnFrontera(Nodo *nodoAValidar){
    if(cantidadElementosVisitados>0){
      for(int i=0;i<cantidadElementosVisitados;i++){
        if(nodoAValidar->estado.cmb[0]==nodosVisitados[i]->estado.cmb[0]&&
           nodoAValidar->estado.cmb[1]==nodosVisitados[i]->estado.cmb[1]&&
            nodoAValidar->estado.cmb[2]==nodosVisitados[i]->estado.cmb[2]){
          return true;
        }
      }
      return false;
    }else{
      return false;
    }

  };
  void printFrontera(){
    cout<<"Visitadoos Elementos\n";
    cout<<"{\t";
    if(cantidadElementosVisitados>0){
      for(int i=0;i<cantidadElementosVisitados;i++){
        cout<<"[ ";
        nodosVisitados[i]->estado.printEstado();
        cout<<" ]";
      }
      cout<<endl;
    }
    cout<<"}\n";
  };
};

#endif // CABECERA_H_INCLUDED
