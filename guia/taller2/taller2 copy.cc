// Rosero Torres Brayan Stiven - 22400233
#include <iostream>
#include <malloc.h> //gestión de memoria dinámica
#include <string.h> //para utilizar strcmp
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
    if (aux->anio <= aux2->anio)
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

int inorden(struct nodo *aux3)
{
    if (aux3->izq != NULL)
        inorden(aux3->izq);
    cout << aux3->anio << endl;
    if (aux3->der != NULL)
        inorden(aux3->der);
    return 0;
}
int preorden(struct nodo *aux3)
{
    cout << aux3->anio << endl;
    if (aux3->izq != NULL)
        preorden(aux3->izq);
    if (aux3->der != NULL)
        preorden(aux3->der);
    return 0;
}
int postorden(struct nodo *aux3)
{
    if (aux3->izq != NULL)
        postorden(aux3->izq);
    if (aux3->der != NULL)
        postorden(aux3->der);
    cout << aux3->anio << endl;
    return 0;
}

int mostrar()
{
    // Mostrar recorridos
    cout << "\n======== INORDEN ========\n";
    inorden(raiz);

    cout << "\n======== PREORDEN ========\n";
    preorden(raiz);

    cout << "\n======== POSTORDEN ========\n";
    postorden(raiz);

    return 0;
}

int ubicar(nodo *aux3, const char *aguja)
{
    if (aux3 == NULL) // Caso base: nodo nulo
    {
        return 0;
    }

    // if (aux3->nombre == aguja) // Valor encontrado
    if (strcmp(aux3->nombre, aguja) == 0) // vemos sin son iguales
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

int buscarPelicula()
// int eliminarNodo()
{
    char buscar[50];
    cout << "buscar una película por su nombre : " << endl;
    cin >> buscar;

    if (ubicar(raiz, buscar))
    {
        cout << "Anio: " << aux->anio << "\n Nombre: " << aux->nombre << "\n DineroRecaudo: " << aux->dineror << endl;
    }
    else
    {
        cout << "no hay pelicula con ese nombre: " << buscar << endl;
    }
    return 0;
}

int Salir()
{
    cout << "Adios!" << endl;
}

int ubicarG(nodo *aux3, int gener)
{
    if (aux3 == NULL) // Caso base: nodo nulo
    {
        return 0;
    }

    if (aux3->genero == gener) // Valor encontrado
    {
        aux = aux3;
        return 1;
    }

    // Buscar en el subárbol izquierdo
    if (aux3->izq != NULL && ubicarG(aux3->izq, gener))
    {
        return 1;
    }

    // Buscar en el subárbol derecho
    if (aux3->der != NULL && ubicarG(aux3->der, gener))
    {
        return 1;
    }

    return 0;
}

int mostrarxG()
// int eliminarNodo()
{
    int buscar;
    cout << "buscar una película por su nombre : " << endl;
    cin >> buscar;

    if (ubicarG(raiz, buscar) == 1) // Masculino
    {
        cout << "\n======== MASCULINO ========\n";
        cout << "Anio: " << aux->anio << "\n Nombre: " << aux->nombre << "\n DineroRecaudo: " << aux->dineror << endl;
    }
    else
    {
        cout << "\n======== FEMENINO ========\n";
        cout << "Anio: " << aux->anio << "\n Nombre: " << aux->nombre << "\n DineroRecaudo: " << aux->dineror << endl;
    }
    return 0;
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
            mostrar();
            break;
        case 3:
            buscarPelicula();
            break;
        case 4:
            mostrarxG();
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