// fila o cola  fifo
// Rosero Torres Brayan Stiven - 22400233
#include <iostream>
#include <malloc.h>
#include <string.h>
#include <stdio.h>
using namespace std;

// Estructura del client
struct client
{
    int id;             // id que almacena el cliente
    int edad;           // edad que almacena el cliente
    int genero;         // 1. Masculino 2. Femenino
    char nombre[30];    // nombre que almacena el cliente
    char motivo[50];    // Motivo de la llamada (usando cin.getline())
    struct client *sig; // Puntero al siguiente client
};

// Punteros globales para manipular la lista
struct client *cabClient = NULL, *auxClient = NULL, *aux2Client = NULL;

// Estructura del historial
struct historial
{
    int id;          // id que almacena el cliente
    int edad;        // edad que almacena el cliente
    int genero;      // 1. Masculino 2. Femenino
    char nombre[30]; // nombre que almacena el cliente
    char motivo[50];
    struct historial *sig; // Puntero al siguiente client
};

// Punteros globales para manipular la pila lifo
struct historial *top = NULL, *auxHistorial = NULL, *aux2Historial = NULL, *top2 = NULL;

// Función Validación por género
void countClients(int &CountM, int &CountF)
{
    CountM = 0;
    CountF = 0;
    aux2Client = cabClient;

    while (aux2Client != NULL)
    {
        if (aux2Client->genero == 1)
        {
            CountM++;
        }
        else if (aux2Client->genero == 2)
        {
            CountF++;
        }
        aux2Client = aux2Client->sig;
    }
}

// Función para agregar un nuevo client al final de la lista
void addClient()
{
    // Contar clientes masculinos y femeninos
    int CountM = 0, CountF = 0;
    countClients(CountM, CountF);

    // Validar la diferencia de género
    // abs+ u7na funcion El valor absoluto de un número
    if (abs(CountM - CountF) > 4)
    {
        cout << "\n No se puede agregar un nuevo cliente. La diferencia entre generos es mayor a 4." << endl;
        return;
    }

    // Se reserva memoria para un nuevo client
    auxClient = (struct client *)malloc(sizeof(struct client));

    // Se verifica si la memoria fue asignada correctamente
    if (auxClient == NULL)
    {
        cout << "Error: no se pudo asignar memoria." << endl;
        return;
    }

    cout << "Nombre completo: ";
    cin.ignore(); // Limpiar el buffer de entrada
    cin >> auxClient->nombre;

    cout << "Edad: ";
    cin >> auxClient->edad;

    cout << "Genero: 1. Masculino, 2. Femenino:" << endl;
    cin >> auxClient->genero;

    cout << "Motivo de la llamada:";
    cin.ignore(); // Limpiar el buffer de entrada
    cin.getline(auxClient->motivo, 50);

    auxClient->sig = NULL; // El nuevo client apunta a NULL (fin de lista)

    // Si la lista está vacía, el nuevo client será la cabClienteza
    if (cabClient == NULL)
    {
        cabClient = auxClient;
        auxClient->id = 1;
    }
    else
    {
        // Se recorre la lista hasta el último client
        aux2Client = cabClient;
        while (aux2Client->sig != NULL)
        {
            aux2Client = aux2Client->sig;
        }

        auxClient->id = aux2Client->id + 1; // Asigno un id único
        aux2Client->sig = auxClient;        // Se enlaza el nuevo client al final
    }

    auxClient = aux2Client = NULL; // Se limpian los punteros auxClientiliares
    free(auxClient);               // Se libera la memoria de auxClient
    free(aux2Client);              // Se libera la memoria de aux2Client
}

// funcion pra registrar historial de cliente utilizando pila(lifo)
int registerHist()
{
    if (cabClient)
    {
        // Se reserva memoria para un nuevo historial
        // strcpy copia elmento string de un lado a otro
        auxHistorial = (struct historial *)malloc(sizeof(struct historial));
        auxHistorial->edad = cabClient->edad;
        auxHistorial->genero = cabClient->genero; // cojo el genero del cliente y se lo paso a historial
        strcpy(auxHistorial->nombre, cabClient->nombre);
        strcpy(auxHistorial->motivo, cabClient->motivo);
        auxHistorial->sig = NULL;

        auxClient = cabClient;
        cabClient = cabClient->sig;
        free(auxClient);

        if (!top)
        {
            top = auxHistorial;
            top->sig = NULL;
            top->id = 1;
        }
        else
        {
            auxHistorial->id = top->id + 1;
            auxHistorial->sig = top;
            top = auxHistorial;
        }
        auxHistorial = NULL;
        free(auxHistorial);
        cout << "\n Historial agregado.." << endl;
    }
    else
    {
        cout << "No hay historial" << endl;
    }
    return 0;
}

// funcion para mostrar CLIENT en espera
void showClient()
{
    auxClient = cabClient;
    // vemos si hay cliente para enteder
    if (auxClient == NULL)
    {
        cout << "\n No hay nada que mostrar." << endl;
        return;
    }
    // Recorre desde la cabCliente hasta NULL
    cout << "\n========CLIENTES EN ESPERA========\n";
    for (auxClient = cabClient; auxClient != NULL; auxClient = auxClient->sig)
    {
        cout << "ID: " << auxClient->id
             << ", Nombre: " << auxClient->nombre
             << ", Edad: " << auxClient->edad
             << ", Genero: " << (auxClient->genero == 1 ? "Masculino" : "Femenino")
             << ", Motivo: " << auxClient->motivo << endl;
    }
}

// funcion para mostrar HISTORIAL
void showHistory()
{

    // Recorre desde la cabClienteza hasta NULL
    cout << "\n======== Mostrar historial de atenciones========\n";

    auxHistorial = top;
    // vemos si hay cliente para enteder
    if (auxHistorial == NULL)
    {
        cout << "\n No hay nada que mostrar." << endl;
        return;
    }

    for (auxHistorial = top; auxHistorial != NULL; auxHistorial = auxHistorial->sig)
    {
        cout << "ID: " << auxHistorial->id
             << ", Nombre: " << auxHistorial->nombre
             << ", Edad: " << auxHistorial->edad
             << ", Genero: " << (auxHistorial->genero == 1 ? "Masculino" : "Femenino")
             << ", Motivo: " << auxHistorial->motivo << endl;
    }
}

// funcion para contar client registrados
int countClient()
{
    showClient();
    int cant = 0; // Lo inicializamos en 0
    // Recorre desde la cabClienteza hasta NULL
    for (auxClient = cabClient; auxClient != NULL; auxClient = auxClient->sig)
    {
        cant++; // Incrementa el contador para cada client encontarado
    }

    if (cant > 0)
        cout << "\n Hay " << cant << " Clientes en espera" << endl;
    else
        cout << "\n No Hay Cliente en espera" << endl;
}

// funcion para atender cliente
void attendClient()
{
    auxClient = cabClient;
    // vemos si hay cliente para enteder
    if (auxClient == NULL)
    {
        cout << "\n No hay cliente para atender." << endl;
        return;
    }
    // while (auxClient != NULL && auxClient->sig != NULL)
    while (auxClient != NULL)
    {
        if (auxClient->edad < 17)
        {
            cout << "\n No se puede atender a " << auxClient->nombre << " es menor de edad." << endl;
        }
        else
        {
            cout << "\n======== ATENDIENDO========\n";
            cout << "Atendiendo a " << auxClient->nombre << endl;
            registerHist();
            // Aquí puedes agregar la lógica para atender al cliente
        }
        auxClient = auxClient->sig; // Avanzar al siguiente cliente
    }
    free(auxClient); // Se libera la memoria de auxClient
}

// funcion para deshacer la última atención
void deshacer()
{

    if (top)
    {
        // Se reserva memoria para un nuevo client
        auxClient = (struct client *)malloc(sizeof(struct client));

        auxClient->edad = top->edad;
        auxClient->genero = top->genero; // cojo el genero del cliente y se lo paso a historial
        strcpy(auxClient->nombre, top->nombre);
        strcpy(auxClient->motivo, top->motivo);
        auxClient->sig = NULL; // El nuevo client apunta a NULL (fin de lista)

        auxHistorial = top;
        top = top->sig;
        free(auxHistorial);

        // Si la lista está vacía, el nuevo client será la cabClienteza
        if (cabClient == NULL)
        {
            cabClient = auxClient;
            auxClient->id = 1;
        }
        else
        {
            // Se recorre la lista hasta el último client
            aux2Client = cabClient;
            while (aux2Client->sig != NULL)
            {
                aux2Client = aux2Client->sig;
            }

            auxClient->id = aux2Client->id + 1; // Asigno un id único
            aux2Client->sig = auxClient;        // Se enlaza el nuevo client al final
        }

        auxClient = aux2Client = NULL; // Se limpian los punteros auxClientiliares
        free(auxClient);               // Se libera la memoria de auxClient
        free(aux2Client);              // Se libera la memoria de aux2Client
        cout << "\n Se realizo exitosamente" << endl;
    }
    else
    {
        cout << "\n No hay nada que deshacer" << endl;
    }
}
// Función para liberar toda la memoria ocupada por la lista
void liberarMemoria()
{
    auxClient = cabClient;
    // Recorre la lista y libera client por client
    while (auxClient != NULL)
    {
        aux2Client = auxClient->sig; // Guarda el siguiente client
        free(auxClient);             // Libera el client actual
        auxClient = aux2Client;      // Avanza al siguiente
    }
    cabClient = NULL; // Después de liberar, cabClienteza queda en NULL
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
            showHistory();
            break;
        case 6:
            deshacer();
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
