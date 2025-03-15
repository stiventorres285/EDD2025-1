#include <iostream>
using namespace std;

int x = 0;
int array[5] = {0, 1, 2, 3, 4};
int *apuntador;
int main(){
    cout<<"El valor de x es: "<<x<<endl;
    cout<<"El valor de array en su posición 1 es: "<<array[1]<<endl;
   /* cout<<&x<<endl;
    cout<<&array[0]<<endl;
    cout<<&array[1]<<endl;*/
    array[1] = array[1] + 10;
    cout<<"El valor de array en su posición 1 es: "<<array[1]<<endl;
    apuntador = &array[1];
    cout<<apuntador<<endl;
    apuntador = apuntador + 1;
    cout<<apuntador<<endl;
    
    //apuntador = &array[1];
    
}