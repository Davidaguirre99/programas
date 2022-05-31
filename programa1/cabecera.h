#ifndef CABECERA_H_INCLUDED
#define CABECERA_H_INCLUDED
#include<iostream>

using namespace std;
class Estado {
public:
    int e[3];
    Estado() {
        for(int i=0; i<3; i++) {
            if(i<2) {
                e[i]=3;
            } else {
                e[i]=1;
            }
        }
    };
    //Funciones
    void printEstado() {
        for(int i=0; i<3; i++) {
            cout<<"c[i]="<< e[i]<<'\t';
        }
        cout<<endl;
    };
    void funcionSucesor() {
        //mm,cc,c,m,mc
        cout<<"Seleccione la acción que desea aplicar:"<<endl;
        cout<<"1) Llevar(mm)\n 2)Llevar(cc) \n 3)Llevar(c) \n 4)Llevar(m) \n 5)Levar(mc)"<<endl;
        int accion=0;
        cin>>accion;
        if(e[2]==1) {
            switch(accion) {
            case 1:
                if(e[1]>=2) {
                    e[1]=e[1]-2;
                    e[2]--;
                }
                break;
            case 2:
                if(e[0]>=2) {
                    e[0]=e[0]-2;
                    e[2]--;
                }
                break;
            case 3:
                if(e[0]>0) {
                    e[0]=e[0]-1;
                    e[2]--;
                }
                break;
            case 4:
                if(e[1]>0) {
                    e[1]=e[1]-1;
                    e[2]--;
                }
                break;
            case 5:
                if(e[0]>0&&e[1]>0) {
                    e[0]=e[0]-1;
                    e[1]=e[1]-1;
                    e[2]--;
                }
                break;
            default:
                break;
            }
        } else {
            switch(accion) {
            case 1:
                if(e[1]<2) {
                    e[1]=e[1]+2;
                    e[2]++;
                }
                break;
            case 2:
                if(e[0]<2) {
                    e[0]=e[0]+2;
                    e[2]++;
                }
                break;
            case 3:
                if(e[0]<3) {
                    e[0]=e[0]+1;
                    e[2]++;
                }
                break;
            case 4:
                if(e[1]<3) {
                    e[1]=e[1]+1;
                    e[2]++;
                }
                break;
            case 5:
                if(e[0]<3&&e[1]<3) {
                    e[0]=e[0]+1;
                    e[1]=e[1]+1;
                    e[2]++;
                }
                break;
            default:
                break;
            }
        }
    };
};
class Nodo {
public:
    Estado estado;
};

#endif // CABECERA_H_INCLUDED
