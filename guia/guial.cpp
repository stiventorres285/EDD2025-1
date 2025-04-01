#include <iostream>

using namespace std;

struct nodo
{
    int id;
    int placa;
    int genero; // 1. Masculi 2. Femenino 3. Binario
    int nacimiento;
    nodo *sig;
};
nodo *cab, *aux, *aux2, *cab_jub, *auxjub;

int registrar()
{
    aux = (struct nodo *)malloc(sizeof(struct nodo));
    cout << "Año de Nacimiento" << endl;
    cin >> aux->nacimiento;
    cout << "Genero del Paciente: 1. Masculino, 2. Femenino, 3. No binario" << endl;
    cin >> aux->genero;
    if (!cab)
    {
        cab = aux;
        cab->sig = NULL;
        cab->id = 1;
    }
    else
    {
        aux->id = cab->id + 1;
        aux->sig = cab;
        cab = aux;
    }
    aux = NULL;
    free(aux);
    return 0;
}
int mostrar()
{
    aux = cab;
    while (aux != NULL)
    {
        cout << "Nodo: " << aux->id << endl;
        cout << "Año Nacimiento: " << aux->nacimiento << endl;
        cout << "Genero: " << aux->genero << endl;
        aux = aux->sig;
    }
    return 0;
}
int eliminar()
{
    aux = cab;
    while (aux != NULL)
    {
        if ((aux->genero == 1 && aux->nacimiento < 1960) || (aux->genero == 2 && aux->nacimiento < 1963))
        {
            if (cab == aux)
            {
                cab = cab->sig;
                if (cab_jub == NULL)
                {
                    cab_jub = aux;
                }
                else
                {
                    auxjub = cab_jub;
                    while (auxjub->sig != NULL)
                        auxjub = auxjub->sig;
                    auxjub->sig = aux;
                    aux->sig = NULL;
                }
            }
            else
            {
                aux2 = cab;
                while (aux2->sig != aux)
                {
                    aux2 = aux2->sig;
                }
                aux2->sig = aux->sig;
                if (cab_jub == NULL)
                {
                    cab_jub = aux;
                }
                else
                {
                    auxjub = cab_jub;
                    while (auxjub->sig != NULL)
                        auxjub = auxjub->sig;
                    auxjub->sig = aux;
                    aux->sig = NULL;
                }
            }
        }
    }
}

int main()
{
    int opcion = 0;
    do
    {
        cout << "Menu" << endl;
        cout << "1. Registrar Nodo" << endl;
        cout << "2. Mostrar Nodo" << endl;
        cout << "3. Eliminar Nodo" << endl;
        cout << "5. Salir" << endl;
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
            eliminar();
            break;
        }
    } while (opcion != 5);
    return 0;
}