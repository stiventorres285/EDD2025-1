#include <iostream>

using namespace std;

struct nodo
{
    int id;
    nodo *sig;
};

nodo *top, *aux, *aux2, *top2; // PILA AUXILIAR

int registrar()
{
    aux = (struct nodo *)malloc(sizeof(struct nodo));
    if (!top)
    {
        top = aux;
        top->sig = NULL;
        top->id = 1;
    }
    else
    {
        aux->id = top->id + 1;
        aux->sig = top;
        top = aux;
    }
    aux = NULL;
    free(aux);
    return 0;
}
int mostrar()
{
    aux = top;
    while (aux != NULL)
    {
        cout << "Nodo: " << aux->id << endl;
        aux = aux->sig;
    }
    return 0;
}
int eliminar()
{
    int buscar = 0;
    mostrar();
    cout << "Id del nodo a eliminar: ";
    cin >> buscar;
    while (top != NULL && buscar != top->id)
    {
        if (top2 != NULL)
        {
            aux = top2;
        }
        top2 = top;
        top = top->sig;
        if (aux != NULL)
        {
            top2->sig = aux;
            aux = NULL;
            free(aux);
        }
        else
        {
            top2->sig = NULL;
        }
    }
    if (top)
    {
        aux = top;
        top = top->sig;
        free(aux);
    }
    while (top2 != NULL)
    {
        aux = top2->sig;
        top2->sig = top;
        top = top2;
        top2 = aux;
        aux = NULL;
    }
}
int main()
{
    int opcion = 0;
    do
    {
        cout << "Menu Pila" << endl;
        cout << "1. Registrar Nodo" << endl;
        cout << "2. Mostrar Nodo" << endl;
        cout << "3. Eliminar Nodo" << endl;
        cout << "5. Salir" << endl;
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            registrar();
            break;
        case 2:
            mostrar();
            break;
        case 3:
            eliminar();
            break;
        }
    } while (opcion != 5);
    return 0;
}