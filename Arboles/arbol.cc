// Rosero Torres Brayan Stiven - 22400233
#include <iostream>
#include <malloc.h> //gestión de memoria dinámica
#include <string.h> //para poder utilizar strcpy
using namespace std;

// Estructura del client
struct nodo
{
    int val = 0;      // id que almacena el cliente
    struct nodo *izq; // Puntero al siguiente client
    struct nodo *der; // Puntero al siguiente client
};

// Punteros globales para manipular la lista
struct nodo *raiz = NULL, *aux = NULL, *aux2 = NULL;

int posicionar()
{
    if (aux->val < aux2->val)
    {
        if (aux2->izq != NULL)
        {
            aux2 = aux2->izq;
            posicionar();
        }
        else
            aux2->izq = aux;
    }
    else if (aux->val > aux2->val)
    {
        if (aux2->der != NULL)
        {
            aux2 = aux2->der;
            posicionar();
        }
        else
            aux2->der = aux;
    }
    return 0;
}

int addNodo()
{
    // Se reserva memoria para un nuevo nodo
    aux = (struct nodo *)malloc(sizeof(struct nodo));
    // Solicita al usuario el val a guardar
    cout << "val: ";
    cin >> aux->val;
    aux->izq = aux->der = NULL;
    if (raiz == NULL)
    {
        raiz = aux;
        aux = NULL;
        free(aux);
    }
    else
    {
        aux2 = raiz;
        posicionar();
    }
}

int preorden(struct nodo *recursive)
{
    cout << "Valor " << recursive->val << endl;
    if (recursive->izq != NULL)
        preorden(recursive->izq);
    if (recursive->der != NULL)
        preorden(recursive->der);
    return 0;
}

int recorrer()
{
    aux = raiz;
    if (aux != NULL)
        preorden(aux);
    return 0;
}

int Salir()
{
    cout << "Adios!" << endl;
}
// Función principal con menú de opciones
int main()
{
    int band, opc;

    do
    {
        // Muestra menú al usuario
        cout << "\n======== MENU Arbol========\n";
        cout << "1. Agregar nodo\n";
        cout << "2. Recorree Arbol\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opc;

        switch (opc)
        {
        case 1:
            addNodo();
            break;
        case 2:
            recorrer();
            break;
        case 3:
            Salir();
            break;
        default:
            cout << "Opcion no valida. Por favor, seleccione una opcion valida.\n";
            break;
        }

    } while (opc != 3);

    // Al salir del programa, se libera la memoria
    // liberarMemoria();

    return 0;
}
