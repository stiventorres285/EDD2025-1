#include <iostream>

using namespace std;

struct carro
{
    int placa;
    carro *sig;
};
carro *cab, *aux, *aux2;

int registrar()
{
    aux = (struct carro *)malloc(sizeof(struct carro));
    aux->sig = NULL;
    cout << "Registrar Auto ultimo numero placa: " << endl;
    cin >> aux->placa;
    if (!cab)
    {
        cab = aux;
    }
    else
    {
        aux2 = cab;
        while (aux2->sig != NULL)
        {
            aux2 = aux2->sig;
        }
        aux2->sig = aux;
    }
    aux = aux2 = NULL;
    free(aux);
    free(aux2);
}
int mostrar()
{
    aux2 = cab;
    while (aux2 != NULL)
    {
        cout << "Auto: " << aux2->placa << endl;
        aux2 = aux2->sig;
    }
}
int contarplacas()
{
    int cant = 0;
    int placa = 0;
    cout << "Digito placa a buscar: ";
    cin >> placa;
    aux2 = cab;
    while (aux2 != NULL)
    {
        if (placa == aux2->placa)
            cant++;
        aux2 = aux2->sig;
    }
    cout << "Al buscar la placa terminada en:" << placa << " encontramos: " << cant << endl;
}

int main()
{
    int opcion = 0;
    do
    {
        cout << "Menu" << endl;
        cout << "1. Registrar Autos" << endl;
        cout << "2. Mostrar Autos" << endl;
        cout << "3. Contar placas" << endl;
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
            contarplacas();
            break;

        default:
            break;
        }
    } while (opcion != 5);
    return 0;
}