#include <iostream>
using namespace std;

struct nodo {
    int value;
    struct nodo *sig;
};

void add(){
    /** 
     * Pedir memoria, llenar los datos, Determinar en donde va dentro del arreglo FIFO
     */
}
void view(){

}

void main () {
    int opc = 0;
    do {    
        cout<<"1. Adicionar Nodo"<<endl<<"2. Ver Nodos"<<"3. Salir";
        cin>>opc;
        switch (opc)
        {
        case 1: add(); break;
        case 2: view(); break;
        
        
        }

    }while(opc!=3);
}