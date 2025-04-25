// fila o cola  fifo
// Rosero Torres Brayan Stiven - 22400233
#include <iostream>
using namespace std;

// Estructura del client
struct client
{
    int id;             // id que almacena el cliente
    int edad;           // edad que almacena el cliente
    int genero;         // 1. Masculino 2. Femenino
    char nombre[30];    // nombre que almacena el cliente
    char motivo[50];    // Motivo de la llamada   char motivo[50];    // Motivo de la llamada (usando cin.getline())
    struct client *sig; // Puntero al siguiente client
};

// Punteros globales para manipular la lista
struct client *cab = NULL, *aux = NULL, *aux2 = NULL;

// Función para agregar un nuevo client al final de la lista
void addClient()
{
    // Se reserva memoria para un nuevo client
    aux = (struct client *)malloc(sizeof(struct client));

    // Se verifica si la memoria fue asignada correctamente
    if (aux == NULL)
    {
        cout << "Error: no se pudo asignar memoria." << endl;
        return;
    }

    cout << "Nombre completo: ";
    cin.ignore(); // Limpiar el buffer de entrada
    cin >> aux->nombre;

    cout << "Edad: ";
    cin >> aux->edad;

    cout << "Genero: 1. Masculino, 2. Femenino:" << endl;
    cin >> aux->genero;

    cout << "Motivo de la llamada:";
    cin.ignore(); // Limpiar el buffer de entrada
    cin.getline(aux->motivo, 50);

    aux->sig = NULL; // El nuevo client apunta a NULL (fin de lista)

    // Si la lista está vacía, el nuevo client será la cabeza
    if (cab == NULL)
    {
        cab = aux;
        aux->id = 1;
    }
    else
    {
        if (aux->genero == 1)
        {
            if (aux->genero < 4)
            {
                // Se recorre la lista hasta el último client
                aux2 = cab;
                while (aux2->sig != NULL)
                {
                    aux2 = aux2->sig;
                }

                aux->id = aux2->id + 1; // Asigno un id único
                aux2->sig = aux;        // Se enlaza el nuevo client al final
            }
        }
    }

    aux = aux2 = NULL; // Se limpian los punteros auxiliares
    free(aux);         // Se libera la memoria de aux
    free(aux2);        // Se libera la memoria de aux2
}

void showClient()
{
    // Recorre desde la cabeza hasta NULL
    cout << "========CLIENTES EN ESPERA========\n";
    for (aux = cab; aux != NULL; aux = aux->sig)
    {
        cout << "ID: " << aux->id
             << ", Nombre: " << aux->nombre
             << ", Edad: " << aux->edad
             << ", Genero: " << (aux->genero == 1 ? "Masculino" : "Femenino")
             << ", Motivo: " << aux->motivo << endl;
    }
}

// funcion para contar client registrados
int countClient()
{
    showClient();
    int cant = 0; // Lo inicializamos en 0
    // Recorre desde la cabeza hasta NULL
    for (aux = cab; aux != NULL; aux = aux->sig)
    {
        cant++; // Incrementa el contador para cada client encontarado
    }

    if (cant > 0)
        cout << "\n Hay " << cant << " Clientes en espera" << endl;
    else
        cout << "\n No Hay Cliente en espera" << endl;
}

void attendClient()
{
    aux = cab;
    // while (aux != NULL && aux->sig != NULL)
    while (aux != NULL)
    {
        if ((aux->edad < 17))
        {
            cout << "No se puede atender a" << aux->nombre << "es menor de edad" << endl;
        }
    }
}
// Función para liberar toda la memoria ocupada por la lista
void liberarMemoria()
{
    aux = cab;
    // Recorre la lista y libera client por client
    while (aux != NULL)
    {
        aux2 = aux->sig; // Guarda el siguiente client
        free(aux);       // Libera el client actual
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
        cout << "1. Agregar cliente a la cola\n";
        cout << "2. Mostrar  clientes en espera\n";
        cout << "3. Contar  clientes en espera\n";
        cout << "4. Atender siguiente cliente\n";
        cout << "5. Mostrar historial de atenciones\n";
        cout << "6. Deshacer ultima atencion\n";
        cout << "7. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opc;

        switch (opc)
        {
        case 1:
            addClient();
            break;
        case 2:
            showClient();
            break;
        case 3:
            countClient();
            break;
        case 4:
            attendClient();
            break;
        case 5:
            break;
        case 6:

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
