// Rosero Torres Brayan Stiven - 22400233
#include <iostream>
#include <malloc.h> //gestión de memoria dinámica
using namespace std;

// Estructura del client
struct nodo
{
    char nombre[30];  // nombre que almacena la pel
    int anio;         // año de la realizacion
    int genero;       // 1. Masculino 2. Femenino
    float dineror;    // Dinero recaudado en millones
    struct nodo *izq; // Puntero al siguiente client
    struct nodo *der; // Puntero al siguiente client
};

// Punteros globales para manipular el arbol
struct nodo *raiz = NULL, *aux = NULL, *aux2 = NULL;

int posicionar()
{
    if (aux->anio < aux2->anio)
    {
        if (aux2->izq != NULL)
        {
            aux2 = aux2->izq;
            posicionar();
        }
        else
            aux2->izq = aux;
    }
    else if (aux->anio > aux2->anio)
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
    // Solicita al usuario el anio a guardar
    cout << "Nombre de la pelicula: ";
    cin >> aux->nombre;

    cout << "Anio de realizacion: ";
    cin >> aux->anio;

    cout << "Dinero recaudado en millones de dolares: ";
    cin >> aux->dineror;

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

int mostrar(struct nodo *recursive)
{
    cout << "Anio " << recursive->anio << endl;
    if (recursive->izq != NULL)
        mostrar(recursive->izq);
    if (recursive->der != NULL)
        mostrar(recursive->der);
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

    do
    {
        // Muestra menú al usuario
        cout << "\n======== MENU Pelicula========\n";
        cout << "1. Registrar pelicula\n";
        cout << "2. Recorrido Arbol\n";
        cout << "3. Buscar pelicula\n";
        cout << "4. Mostrar x Genero\n";
        cout << "5. Fracasos \n";
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opc;

        switch (opc)
        {
        case 1:
            addNodo();
            break;
        case 2:
            mostrar(raiz);
            break;
        case 6:
            Salir();
            break;
        default:
            cout << "Opcion no valida. Por favor, seleccione una opcion anioida.\n";
            break;
        }

    } while (opc != 6);

    // Al salir del programa, se libera la memoria
    // liberarMemoria();

    return 0;
}