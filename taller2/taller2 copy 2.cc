#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura para almacenar información de películas
typedef struct Pelicula
{
    char nombre[100];
    int anio;
    char genero[50];
    float recaudacion; // en millones de dólares
} Pelicula;

// Estructura para nodos del árbol
typedef struct Nodo
{
    Pelicula pelicula;
    struct Nodo *izquierda;
    struct Nodo *derecha;

} Nodo;

// Función para crear un nuevo nodo
Nodo *crearNodo(Pelicula pelicula)
{
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    if (nuevoNodo == NULL)
    {
        printf("Error al asignar memoria\n");
        exit(1);
    }

    nuevoNodo->pelicula = pelicula;
    nuevoNodo->izquierda = NULL;
    nuevoNodo->derecha = NULL;

    return nuevoNodo;
}

// Función para insertar una película en el árbol
Nodo *insertarPelicula(Nodo *raiz, Pelicula pelicula)
{
    // Si el árbol está vacío, crear un nuevo nodo
    if (raiz == NULL)
    {
        return crearNodo(pelicula);
    }

    // Ordenar primero por año
    if (pelicula.anio < raiz->pelicula.anio)
    {
        raiz->izquierda = insertarPelicula(raiz->izquierda, pelicula);
    }
    else if (pelicula.anio > raiz->pelicula.anio)
    {
        raiz->derecha = insertarPelicula(raiz->derecha, pelicula);
    }
    else
    {
        // Si tienen el mismo año, la nueva película va a la izquierda
        raiz->izquierda = insertarPelicula(raiz->izquierda, pelicula);
    }

    return raiz;
}

// Función para mostrar los datos de una película
void mostrarPelicula(Pelicula pelicula)
{
    printf("Nombre: %s\n", pelicula.nombre);
    printf("Anio: %d\n", pelicula.anio);
    printf("Genero: %s\n", pelicula.genero);
    printf("Recaudacion: %.1f millones de dolares\n", pelicula.recaudacion);
    printf("----------------------------\n");
}

// Recorrido inorden: izquierda, raíz, derecha
void recorridoInorden(Nodo *raiz)
{
    if (raiz != NULL)
    {
        recorridoInorden(raiz->izquierda);
        mostrarPelicula(raiz->pelicula);
        recorridoInorden(raiz->derecha);
    }
}

// Recorrido preorden: raíz, izquierda, derecha
void recorridoPreorden(Nodo *raiz)
{
    if (raiz != NULL)
    {
        mostrarPelicula(raiz->pelicula);
        recorridoPreorden(raiz->izquierda);
        recorridoPreorden(raiz->derecha);
    }
}

// Recorrido posorden: izquierda, derecha, raíz
void recorridoPosorden(Nodo *raiz)
{
    if (raiz != NULL)
    {
        recorridoPosorden(raiz->izquierda);
        recorridoPosorden(raiz->derecha);
        mostrarPelicula(raiz->pelicula);
    }
}

// Buscar una película por nombre
void buscarPorNombre(Nodo *raiz, const char *nombre)
{
    if (raiz == NULL)
    {
        return;
    }

    // Buscar en el nodo actual
    if (strcmp(raiz->pelicula.nombre, nombre) == 0)
    {
        printf("Pelicula encontrada\n");
        mostrarPelicula(raiz->pelicula);
    }

    // Buscar en los subárboles
    buscarPorNombre(raiz->izquierda, nombre);
    buscarPorNombre(raiz->derecha, nombre);
}

// Mostrar películas por género
void mostrarPorGenero(Nodo *raiz, const char *genero)
{
    if (raiz == NULL)
    {
        return;
    }

    // Verificar el nodo actual
    if (strcmp(raiz->pelicula.genero, genero) == 0)
    {
        mostrarPelicula(raiz->pelicula);
    }

    // Buscar en los subárboles
    mostrarPorGenero(raiz->izquierda, genero);
    mostrarPorGenero(raiz->derecha, genero);
}

// Estructura auxiliar para encontrar las películas con menor recaudación
typedef struct
{
    Pelicula peliculas[3];
    int contador;
} FracasosTaquilleros;

// Función para inicializar la estructura de fracasos
void inicializarFracasos(FracasosTaquilleros *fracasos)
{
    fracasos->contador = 0;
    for (int i = 0; i < 3; i++)
    {
        fracasos->peliculas[i].recaudacion = 999999.9; // Un valor muy alto
    }
}

// Función para insertar una película en los fracasos si corresponde
void actualizarFracasos(FracasosTaquilleros *fracasos, Pelicula pelicula)
{
    // Encontrar la posición donde insertarla (si es que corresponde)
    int pos = -1;

    for (int i = 0; i < 3; i++)
    {
        if (pelicula.recaudacion < fracasos->peliculas[i].recaudacion)
        {
            pos = i;
            break;
        }
    }

    // Si encontramos una posición, desplazar las demás e insertar
    if (pos != -1)
    {
        for (int i = 2; i > pos; i--)
        {
            fracasos->peliculas[i] = fracasos->peliculas[i - 1];
        }
        fracasos->peliculas[pos] = pelicula;
        if (fracasos->contador < 3)
        {
            fracasos->contador++;
        }
    }
}

// Encontrar las 3 películas con menor recaudación
void encontrarFracasos(Nodo *raiz, FracasosTaquilleros *fracasos)
{
    if (raiz == NULL)
    {
        return;
    }

    // Verificar el nodo actual
    actualizarFracasos(fracasos, raiz->pelicula);

    // Buscar en los subárboles
    encontrarFracasos(raiz->izquierda, fracasos);
    encontrarFracasos(raiz->derecha, fracasos);
}

// Mostrar los 3 fracasos taquilleros
void mostrarFracasosTaquilleros(Nodo *raiz)
{
    FracasosTaquilleros fracasos;
    inicializarFracasos(&fracasos);

    encontrarFracasos(raiz, &fracasos);

    printf("Los 3 mayores fracasos taquilleros son:\n");
    for (int i = 0; i < fracasos.contador; i++)
    {
        printf("%d. ", i + 1);
        mostrarPelicula(fracasos.peliculas[i]);
    }
}

// Función para liberar la memoria del árbol
void liberarArbol(Nodo *raiz)
{
    if (raiz != NULL)
    {
        liberarArbol(raiz->izquierda);
        liberarArbol(raiz->derecha);
        free(raiz);
    }
}

// Crear una película con los datos proporcionados
Pelicula crearPelicula(const char *nombre, int anio, const char *genero, float recaudacion)
{
    Pelicula p;
    strcpy(p.nombre, nombre);
    p.anio = anio;
    strcpy(p.genero, genero);
    p.recaudacion = recaudacion;
    return p;
}

int main()
{
    Nodo *raiz = NULL;
    int opcion;
    char nombreBusqueda[100];
    char generoBusqueda[50];

    // Agregar algunas películas de ejemplo
    raiz = insertarPelicula(raiz, crearPelicula("El Padrino", 1972, "Drama", 246.1));
    raiz = insertarPelicula(raiz, crearPelicula("Titanic", 1997, "Romance", 2195.0));
    raiz = insertarPelicula(raiz, crearPelicula("Star Wars: Una nueva esperanza", 1977, "Ciencia Ficcion", 775.4));
    raiz = insertarPelicula(raiz, crearPelicula("Avatar", 2009, "Ciencia Ficcion", 2847.2));
    raiz = insertarPelicula(raiz, crearPelicula("El Rey Leon", 1994, "Animacion", 968.5));
    raiz = insertarPelicula(raiz, crearPelicula("Joker", 2019, "Drama", 1074.3));
    raiz = insertarPelicula(raiz, crearPelicula("Parasitos", 2019, "Drama", 258.7));
    raiz = insertarPelicula(raiz, crearPelicula("The Room", 2003, "Drama", 0.2));
    raiz = insertarPelicula(raiz, crearPelicula("Cats", 2019, "Musical", 75.5));
    raiz = insertarPelicula(raiz, crearPelicula("Battlefield Earth", 2000, "Ciencia Ficcion", 29.7));

    do
    {
        printf("\n--- GESTOR DE PELiCULAS ---\n");
        printf("1. Mostrar recorrido Inorden\n");
        printf("2. Mostrar recorrido Preorden\n");
        printf("3. Mostrar recorrido Posorden\n");
        printf("4. Buscar película por nombre\n");
        printf("5. Mostrar películas por género\n");
        printf("6. Mostrar los 3 fracasos taquilleros\n");
        printf("7. Agregar nueva película\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar(); // Limpiar el buffer

        switch (opcion)
        {
        case 1:
            printf("\nRecorrido Inorden (ordenado por año):\n");
            recorridoInorden(raiz);
            break;
        case 2:
            printf("\nRecorrido Preorden:\n");
            recorridoPreorden(raiz);
            break;
        case 3:
            printf("\nRecorrido Posorden:\n");
            recorridoPosorden(raiz);
            break;
        case 4:
            printf("\nIngrese el nombre de la pelicula a buscar: ");
            fgets(nombreBusqueda, sizeof(nombreBusqueda), stdin);
            nombreBusqueda[strcspn(nombreBusqueda, "\n")] = 0; // Eliminar el salto de línea

            printf("\nResultados de la busqueda para '%s':\n", nombreBusqueda);
            buscarPorNombre(raiz, nombreBusqueda);
            break;
        case 5:
            printf("\nIngrese el genero a buscar: ");
            fgets(generoBusqueda, sizeof(generoBusqueda), stdin);
            generoBusqueda[strcspn(generoBusqueda, "\n")] = 0; // Eliminar el salto de línea

            printf("\nPelículas del genero '%s':\n", generoBusqueda);
            mostrarPorGenero(raiz, generoBusqueda);
            break;
        case 6:
            mostrarFracasosTaquilleros(raiz);
            break;
        case 7:
        {
            Pelicula nuevaPelicula;
            printf("\n--- AGREGAR NUEVA PELÍCULA ---\n");
            printf("Nombre: ");
            fgets(nuevaPelicula.nombre, sizeof(nuevaPelicula.nombre), stdin);
            nuevaPelicula.nombre[strcspn(nuevaPelicula.nombre, "\n")] = 0;

            printf("Anio: ");
            scanf("%d", &nuevaPelicula.anio);
            getchar(); // Limpiar buffer

            printf("Genero: ");
            fgets(nuevaPelicula.genero, sizeof(nuevaPelicula.genero), stdin);
            nuevaPelicula.genero[strcspn(nuevaPelicula.genero, "\n")] = 0;

            printf("Recaudacion (millones de dólares): ");
            scanf("%f", &nuevaPelicula.recaudacion);
            getchar(); // Limpiar buffer

            raiz = insertarPelicula(raiz, nuevaPelicula);
            printf("\nPelicula agregada con exito!\n");
            break;
        }
        case 0:
            printf("\nSaliendo del programa...\n");
            break;
        default:
            printf("\nOpcion no válida. Intente de nuevo.\n");
        }

    } while (opcion != 0);

    // Liberar memoria
    liberarArbol(raiz);

    return 0;
}