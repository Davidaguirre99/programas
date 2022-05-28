#ifndef CABECERA_H_INCLUDED
#define CABECERA_H_INCLUDED
#include<iostream>

using namespace std;
class Estado{
    public:
        int e[3];
        Estado(){
            for(int i=0;i<3;i++){
                e[i]=0;
            }
        };
        //Funciones
        void printEstado(){
            for(int i=0;i<3;i++){
                cout<<"c[i]="<< e[i]<<'\t';
            }
            cout<<endl;
        };
};
class Nodo{
public:
    Estado estado;
};

#endif // CABECERA_H_INCLUDED
