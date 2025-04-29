// Rosero Torres Brayan Stiven - 22400233
#include <iostream>
#include <malloc.h> //gestión de memoria dinámica
#include <string.h> //para utilizar strcmp
#include <vector>
#include <algorithm> // Para std::sort

using namespace std;

// Estructura del client
struct nodo
{

    char nombre[30];  // nombre que almacena la pel
    int anio;         // año de la realizacion
    int genero;       // 1.Accion 2.Drama 3.Comedia
    double dinero;    // Dinero recaudado en millones
    struct nodo *izq; // Puntero al siguiente client
    struct nodo *der; // Puntero al siguiente client
};

// Punteros globales para manipular el arbol
struct nodo *raiz = NULL, *aux = NULL, *aux2 = NULL;

int posicionar()
{
    if (aux->anio <= aux2->anio)
    {
        if (aux2->izq != NULL) // no esta vacio
        {
            aux2 = aux2->izq; // si la izq esta ocupada lo mandamos a la izq para q evalue lo mismo posicionar
            posicionar();     // llamamos a mi mismos
        }
        else
            aux2->izq = aux; // de lo contarrio lo igualamos a izq
    }
    else if (aux->anio > aux2->anio)
    {
        if (aux2->der != NULL)
        {
            aux2 = aux2->der; // si la der esta ocupada lo mandamos a la izq para q evalue lo mismo posicionar
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

    cout << "Genero: \n 1. Accion \n 2. Drama  \n 3.Comedia" << endl;
    cin >> aux->genero;

    cout << "Dinero recaudado en millones de dolares: ";
    cin >> aux->dinero;

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

// Función para obtener el género como texto
const char *obtenerGeneroTexto(int genero)
{
    switch (genero)
    {
    case 1:
        return "Accion";
    case 2:
        return "Drama";
    case 3:
        return "Comedia";
    default:
        return "Desconocido"; // En caso de un valor no válido
    }
}

int mostrarP(struct nodo *aux3)
{
    cout << "--------------------- " << endl;
    cout << "Nombre: " << aux3->nombre << endl;
    cout << "Anio: " << aux3->anio << endl;
    cout << "Genero: " << obtenerGeneroTexto(aux3->genero) << endl;
    cout << "Dinero Recaudado: " << aux3->dinero << " millones de dolares " << endl;
}

// mandamos parametro para decirle donde inicia
//  cual es el primer nodo q va q es la raiz
int inorden(struct nodo *aux3)
{
    if (aux3->izq != NULL)
        inorden(aux3->izq);
    cout << "\n======== INORDEN ========\n";
    mostrarP(aux3);
    if (aux3->der != NULL)
        inorden(aux3->der);
    return 0;
}
int preorden(struct nodo *aux3)
{
    cout << "\n======== PREORDEN ========\n";
    mostrarP(aux3);

    if (aux3->izq != NULL)
        // si tiene hijo se llama asi mismo y se va a la izquierda
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
    cout << "\n======== POSTORDEN ========\n";
    mostrarP(aux3);
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
    cout << "buscar una pelicula por su nombre : " << endl;
    cin >> buscar;

    // si pelicula se encuentra
    if (ubicar(raiz, buscar))
    {
        mostrarP(aux); // llamamos la funcion y mostramos los datos
    }
    else
    {
        cout << "no hay pelicula con ese nombre: " << buscar << endl;
    }
    return 0;
}
int ubicarG(nodo *aux3, int gener)
{
    if (aux3 == NULL) // Caso base: nodo nulo
    {
        return 0;
    }

    // Si el género coincide, mostrar el nodo
    if (aux3->genero == gener)
    {
        mostrarP(aux3);
    }
    // Recorrer el subárbol izquierdo y derecho
    ubicarG(aux3->izq, gener);
    ubicarG(aux3->der, gener);
}
int mostrarxG(struct nodo *raiz)
{
    int buscar;
    cout << "buscar pelicula por Genero: \n1. Accion \n 2. Drama \n 3.Comedia " << endl;
    cin >> buscar;

    if (buscar < 1 || buscar > 3)
    {
        cout << "ERROR: GENERO NO VALIDO" << endl;
    }

    // Mostrar título según el género seleccionado
    if (buscar == 1)
    {
        cout << "\n======== Accion ========\n";
    }
    else if (buscar == 2)
    {
        cout << "\n======== Drama ========\n";
    }
    else if (buscar == 3)
    {
        cout << "\n======== Comedia ========\n";
    }

    // Llamar a la función recursiva para buscar y mostrar películas
    ubicarG(raiz, buscar);
}
// Función auxiliar para recolectar todos los nodos del árbol (inorden)
void recolectarPeliculas(nodo *raiz, vector<nodo *> &peliculas)
{
    if (!raiz)
        return;

    recolectarPeliculas(raiz->izq, peliculas); // Recorrer izquierda
    peliculas.push_back(raiz);                 // Guardar nodo actual
    recolectarPeliculas(raiz->der, peliculas); // Recorrer derecha
}

// Comparador para ordenar por dinero (menor a mayor)
bool compararPorDineroMenor(nodo *a, nodo *b)
{
    return a->dinero < b->dinero;
}

// Función principal para mostrar los 3 fracasos taquilleros
void mostrarFracasosTaquilleros(nodo *raiz)
{
    vector<nodo *> peliculas;
    recolectarPeliculas(raiz, peliculas);

    // Ordenar por menor recaudación
    sort(peliculas.begin(), peliculas.end(), compararPorDineroMenor);

    cout << "\n=== Los 3 fracasos taquilleros ===\n";
    int total = min(3, static_cast<int>(peliculas.size()));

    if (total == 0)
    {
        cout << "No hay películas registradas.\n";
    }
    else
    {
        for (int i = 0; i < total; ++i)
        {
            cout << i + 1 << ". " << peliculas[i]->nombre
                 << " ($" << peliculas[i]->dinero << " millones)\n";
        }
    }
}
int Salir()
{
    cout << "Adios!" << endl;
}

// Función principal con menú de opciones
int main()
{
    int opc, opc2;

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
            cout << "\n======== MENU Recorrido Arbol========\n";
            cout << "1. INORDEN\n";
            cout << "2. PREORDEN\n";
            cout << "3. POSTORDEN\n";
            cout << "Seleccione una opcion: ";
            cin >> opc2;
            switch (opc2)
            {
            case 1:
                inorden(raiz);
                break;
            case 2:
                preorden(raiz);
                break;
            case 3:
                postorden(raiz);
                break;
            default:
                cout << "Opcion no valida. Por favor, seleccione una opcion anioida.\n";
                break;
            }
            break;

        case 3:
            buscarPelicula();
            break;
        case 4:
            mostrarxG(raiz);
            break;
        case 5:
            mostrarFracasosTaquilleros(raiz); // Llamada a la nueva función
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
