// fila o cola  fifo
// Rosero Torres Brayan Stiven - 22400233
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
    cout << "Agregar el nombre del producto: ";
    cin >> aux->nombre;

    // El nuevo producto apunta a NULL (fin de lista)
    aux->sig = NULL;

    // Si la lista está vacía, el nuevo producto será la cabeza
    if (cab == NULL)
    {
        cab = aux;
        aux->id = 1;
    }
    else
    {
        // Se recorre la lista hasta el último producto
        aux2 = cab;

        while (aux2->sig != NULL)
        {
            aux2 = aux2->sig;
        }
        aux->id = aux2->id + 1; // Asigno un id único
        aux2->sig = aux;        // Se enlaza el nuevo client al final
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
    producto *aux = cab; // Usar un puntero auxiliar para recorrer la lista
    while (aux != NULL)
    {
        if (aux->id == seed)
        {
            // Producto encontrado, mostrar información
            cout << "Producto encontrado\n ID: " << aux->id << ", Nombre: " << aux->nombre << endl;
            return 1; // id encontrado
        }
        aux = aux->sig; // Mover al siguiente producto
    }

    cout << "Producto no encontrado." << endl; // Mensaje si no se encuentra el producto
    return 0;                                  // id no encontrado
}

// Función para eliminar un producto en la lista
int deleteProducto()
{
    int dele;
    cout << "Digite el id a eliminar: ";
    cin >> dele;
    producto *aux = cab;       // Puntero para recorrer la lista
    producto *anterior = NULL; // Puntero para el producto anterior

    // Recorre la lista buscando el id
    while (aux != NULL)
    {
        if (aux->id == dele)
        {
            // Si el producto a eliminar es la cabeza
            if (anterior == NULL)
            {
                cab = aux->sig; // Actualiza la cabeza
            }
            else
            {
                anterior->sig = aux->sig; // Enlaza el producto anterior con el siguiente
            }
            delete aux; // Libera la memoria del producto
            return 1;   // id encontrado y eliminado
        }
        anterior = aux; // Mueve el puntero anterior al producto actual
        aux = aux->sig; // Mueve al siguiente producto
    }
    // Recorre la lista comparando el id

    return 0; // id no encontrado
}

// funcion para contar productos registrados
int countProducto()
{
    int idUnico = 0; // Lo inicializamos en 0
    // Recorre desde la cabeza hasta NULL
    for (aux = cab; aux != NULL; aux = aux->sig)
    {
        idUnico++; // Incrementa el contador para cada producto encontarado
    }

    if (idUnico > 0)
        cout << "\n Hay " << idUnico << " Productos" << endl;
    else
        cout << "\n No Hay Productos" << endl;
}

//
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
        cout << "\n======== MENU COLA========\n";
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
            searchProducto();
            break;
        case 4:
            band = deleteProducto();
            if (band)
                cout << "Producto eliminado.\n";
            else
                cout << "No encontrado.\n";
            break;
        case 5:
            countProducto();
            break;
        case 6:
            band = updateProducto();
            if (band)
                cout << "\nProducto actualizado correctamente.\n";
            else
                cout << "No encontrado.\n";
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
