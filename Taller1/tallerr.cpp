#include <iostream>
using namespace std;

// Estructura del Producto
struct producto
{
    int id;               // id que almacena el producto
    char nombre[30];      // nombre que almacena el producto
    struct producto *sig; // Puntero al siguiente producto
};

// Punteros globales para manipular la lista
struct producto *cab = NULL, *aux = NULL, *aux2 = NULL;
int contadorId = 1; // Contador para asignar IDs únicos

// Función para agregar un nuevo producto al final de la lista
void addProducto()
{
    // Se reserva memoria para un nuevo producto
    aux = (struct producto *)malloc(sizeof(struct producto));

    // Se verifica si la memoria fue asignada correctamente
    if (aux == NULL)
    {
        cout << "Error: no se pudo asignar memoria." << endl;
        return;
    }

    // Asigno un id único
    aux->id = contadorId++;

    cout << "Modifique el nombre del producto: ";
    cin >> aux->nombre;

    // El nuevo producto apunta a NULL (fin de lista)
    aux->sig = NULL;

    // Si la lista está vacía, el nuevo producto será la cabeza
    if (cab == NULL)
    {
        cab = aux;
    }
    else
    {
        // Se recorre la lista hasta el último producto
        aux2 = cab;
        while (aux2->sig != NULL)
        {
            aux2 = aux2->sig;
        }
        // Se enlaza el nuevo producto al final
        aux2->sig = aux;
    }
    aux = aux2 = NULL; // Se limpian los punteros auxiliares
    free(aux);         // Se libera la memoria de aux
    free(aux2);        // Se libera la memoria de aux2
}

// Función para mostrar todos los productos de la lista
void viewProducto()
{
    // Recorre desde la cabeza hasta NULL
    for (aux = cab; aux != NULL; aux = aux->sig)
    {
        cout << "id: " << aux->id << ", Nombre: " << aux->nombre << endl;
    }
}

// Función para buscar un producto en la lista
int searchProducto()
{
    int seed;
    cout << "Digite el id a buscar: ";
    cin >> seed;

    // Recorre la lista comparando el id
    for (aux = cab; aux != NULL; aux = aux->sig)
    {
        if (aux->id == seed)
        {
            aux = NULL; // Se limpian los punteros auxiliares
            free(aux);  // Se libera la memoria de aux
            return 1;   // id encontrado
        }
    }
    aux = NULL; // Se limpian los punteros auxiliares
    free(aux);  // Se libera la memoria de aux
    return 0;   // id no encontrado
}

// Función para eliminar un producto en la lista
int deleteProducto()
{
    int dele;
    cout << "Digite el id a eliminar: ";
    cin >> dele;
    producto *aux = cab;       // Puntero para recorrer la lista
    producto *anterior = NULL; // Puntero para el nodo anterior

    // Recorre la lista buscando el id
    while (aux != NULL)
    {
        if (aux->id == dele)
        {
            // Si el nodo a eliminar es la cabeza
            if (anterior == NULL)
            {
                cab = aux->sig; // Actualiza la cabeza
            }
            else
            {
                anterior->sig = aux->sig; // Enlaza el nodo anterior con el siguiente
            }
            delete aux; // Libera la memoria del nodo
            return 1;   // id encontrado y eliminado
        }
        anterior = aux; // Mueve el puntero anterior al nodo actual
        aux = aux->sig; // Mueve al siguiente nodo
    }
    // Recorre la lista comparando el id

    return 0; // id no encontrado
}

// Función para agregar un nuevo producto al final de la lista
int updateProducto()
{
    int modific;
    cout << "Digite el id a modificar: ";
    cin >> modific;

    // Recorre la lista comparando el valor
    for (aux = cab; aux != NULL; aux = aux->sig)
    {
        if (aux->id == modific)
        {
            cout << "Modifique el nombre del producto: ";
            cin >> aux->nombre;
            return 1; // Valor encontrado
        }
    }
    aux = NULL; // Se limpian los punteros auxiliares
    free(aux);  // Se libera la memoria de aux
    return 0;   // Valor no encontrado
}

// Función para liberar toda la memoria ocupada por la lista
void liberarMemoria()
{
    aux = cab;
    // Recorre la lista y libera producto por producto
    while (aux != NULL)
    {
        aux2 = aux->sig; // Guarda el siguiente producto
        free(aux);       // Libera el producto actual
        aux = aux2;      // Avanza al siguiente
    }
    cab = NULL; // Después de liberar, cabeza queda en NULL
    cout << "Memoria liberada correctamente." << endl;
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
        cout << "\n==== MENU ====\n";
        cout << "1. Agregar producto\n";
        cout << "2. Mostrar  productos\n";
        cout << "3. Buscar producto\n";
        cout << "4. Eliminar producto\n";
        cout << "5. Contar producto\n";
        cout << "6. Modificar producto\n";
        cout << "7. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opc;

        switch (opc)
        {
        case 1:
            addProducto();
            break;
        case 2:
            viewProducto();
            break;
        case 3:
            band = searchProducto();
            if (band)
                cout << "Producto encontrado.\n"
                     << "Nombre: " << aux->nombre << endl;
            else
                cout << "No encontrado.\n";
            break;
        case 4:
            band = deleteProducto();
            if (band)
                cout << "Producto eliminado.\n";
            else
                cout << "No encontrado.\n";
            break;
        case 6:
            updateProducto();
            break;
        case 7:
            Salir();
            break;
        default:
            cout << "Opcion no valida. Por favor, seleccione una opcion valida.\n";
            break;
        }

    } while (opc != 7);

    // Al salir del programa, se libera la memoria
    liberarMemoria();

    return 0;
}
