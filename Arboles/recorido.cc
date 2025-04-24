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

int numeros[10] = {30, 15, 45, 33, 12, 22, 43, 2, 16, 44};

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
    for (int i = 0; i < 10; i++)
    {
        // Se reserva memoria para un nuevo nodo
        aux = (struct nodo *)malloc(sizeof(struct nodo));
        aux->val = numeros[i];
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
}

int inorden(struct nodo *aux3)

{
    if (aux3->izq != NULL)
    {
        inorden(aux3->izq);
    }
    cout << aux3->val << endl;
    if (aux3->der != NULL)
    {
        inorden(aux3->der);
    }
    return 0;
}

int preorden(struct nodo *aux3)
{
    cout << aux3->val << endl;
    if (aux3->izq != NULL)
        preorden(aux3->izq);
    if (aux3->der != NULL)
        preorden(aux3->der);
    return 0;
}
int postorden(struct nodo *aux3)
{
    if (aux3->izq != NULL)
    {
        postorden(aux3->izq);
    }
    if (aux3->der != NULL)
    {
        postorden(aux3->der);
    }
    cout << aux3->val << endl;
    return 0;
}

// Que nodo quiero eliminar
// Buscar dicho nodo
// Garantizar que el nodo padre apunte a NULL
// Liberar el nodo

int ubicar(nodo *aux3, int aguja)
{
    if (aux3 == NULL) // Caso base: nodo nulo
    {
        return 0;
    }

    if (aux3->val == aguja) // Valor encontrado
    {
        aux = aux3;
        return 1;
    }

    // Buscar en el subárbol izquierdo
    if (aux3->izq != NULL && ubicar(aux3->izq, aguja))
    {
        return 1;
    }

    // Buscar en el subárbol derecho
    if (aux3->der != NULL && ubicar(aux3->der, aguja))
    {
        return 1;
    }

    return 0;
}

int buscarNodo()
// int eliminarNodo()
{
    int buscar;
    cout << "Digitte el valor a buscar: " << endl;
    cin >> buscar;
    ubicar(raiz, buscar);

    if (ubicar(raiz, buscar))
    {
        // cout << "Valor encontrado: " << aux->val << ", Nombre: " << aux->nombre << endl;
        cout << "Valor encontrado: " << aux->val << ", Nombre: " << aux->val << endl;
        cout << "El valor " << buscar << " está en el árbol." << endl;
    }
    else
    {
        cout << "El valor " << buscar << " NO está en el árbol." << endl;
    }
    return 0;
}
int Salir()
{
    cout << "Adios!" << endl;
}
// Función principal con menú de opciones
int main()
{
    int opc;
    addNodo();

    do
    {
        // Muestra menú al usuario
        cout << "\n======== MENU Arbol========\n";
        cout << "1. Preorden\n";
        cout << "2. Inorden\n";
        cout << "3. Postorden\n";
        cout << "4. Eliminar\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opc;

        switch (opc)
        {
        case 1:
            preorden(raiz);
            break;
        case 2:
            inorden(raiz);
            break;
        case 3:
            postorden(raiz);
            break;
        case 4:
            buscarNodo();
            break;
        case 5:
            Salir();
            break;
        default:
            cout << "Opcion no valida. Por favor, seleccione una opcion valida.\n";
            break;
        }

    } while (opc != 5);

    // Al salir del programa, se libera la memoria
    // liberarMemoria();

    return 0;
}
