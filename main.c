#include <string.h>         /* Para uso de la función 'strcpy' */
#include <stdlib.h>         /* Para uso de Memoria Dinámica    */
#include <unistd.h>         /* Para funciones propias de Linux */
#include <stdio.h>          /* Entrada y Salida Estándar de C  */
#include <time.h>           /* Para uso de Números Aleatorios  */

#define ARCHIVO "log.txt"   /* Ubicación del Registro del Programa    */
#define CHAR_LIMIT 1024     /* Límite de carácteres para nombres      */
#define MAX_PLAYERS 7       /* Número Máximo de Jugadores por partida */
#define MAX_COMER 10        /* Tamaño máximo de las Fichas para Comer */
#define MAX_TILES 9         /* Cantidad máxima de Fichas por Jugador  */
#define DOMINO 28           /* Cantidad de Fichas que posee el Juego  */
#define FALSE 0             /* Creamos el tipo Booleano False = 0     */
#define TRUE 1              /* Creamos el tipo Booleano True = 1      */ 

/* ESTRUCTURA DE FICHA */
typedef struct {
    int valores[2];         /* Valores que tiene la Ficha ( [Izq|Der] )     */
    int salida;             /* Variable para obtener la 'punta' de la Ficha */
    int numFicha;           /* Variable para el ordenamiento de las fichas  */
} Ficha;

/* ESTRUCTURA DE JUGADOR */
typedef struct {
    char nom[CHAR_LIMIT];   /* Variable que guarda el Nombre del Jugador           */
    Ficha mazo[MAX_TILES];  /* Vector del Mazo para las Fichas del Jugador         */
    int totalGanados;       /* Cantidad de Juegos Ganados que lleva cada Jugador   */
    int totalPuntos;        /* Cantidad total de puntos que posee cada Jugador     */
    int puntos;             /* Cantidad de puntos que lleva el Jugador por partida */
} Jugador;

/* VARIABLES GLOBALES */
Ficha listaFichasParaComer[MAX_COMER];  /* Lista de las Fichas para Comer           */
Jugador jugadores[MAX_PLAYERS];         /* Lista de Jugadores por partida           */
Ficha listaMazoTotal[DOMINO];           /* Lista de todas las Fichas del Juego      */
int totalFichas = DOMINO;               /* Para Manejo de Vectores en el Juego      */
int canFichasJug = 0;                   /* Cantidad de Fichas que hay por Jugador   */
int canMazoJug = 0;                     /* Cantidad de Fichas para cada Jugador     */
int canJug = 0;                         /* Cantidad de Jugadores por partida        */

/* LISTA DE FUNCIONES A UTILIZAR DENTRO DEL JUEGO */
void revolverFichas (Ficha f[], int size);
void ordenarFichas (Ficha f[], int size);
void delElement (Ficha f[], int pos);
void inicializarFichas ();
void repartirFichas ();
void crearJugadores ();
int verificarDobles ();
/* FUNCION DE PRUEBA */
void imprimir();

/* FUNCIÓN MAIN */
int main () {

    repartirFichas ();
    imprimir ();

    // for (int i = 0; i < DOMINO; i++) {
    //     printf ("#%i:\t[%i|%i]\n", i + 1, listaMazoTotal[i].valores[0], listaMazoTotal[i].valores[1]);
    // }
    return 0;
}

/* DESARROLLO DE FUNCIONES */
// Función para Repartir Fichas:
void repartirFichas () {
    /* PEDIMOS CANTIDAD DE JUGADORES Y LOS CREAMOS */
    // ** CTRL + Click para ir a la función ** //
    crearJugadores ();
    
    /* DIVIDIMOS LA CANTIDAD DE FICHAS */
    canFichasJug = DOMINO / (canJug + 1);           /* Cantidad de Fichas a Repartir */

    /* REVOLVEMOS LAS FICHAS Y LAS REPARTIMOS */
    do {
        inicializarFichas ();
        revolverFichas (listaMazoTotal, DOMINO);
        for (int i = 0; i < canJug; i++) {
            for (int j = 0; j < canFichasJug; j++) {
                jugadores[i].mazo[j] = listaMazoTotal[0];
                delElement(listaMazoTotal, 0);
            }
            ordenarFichas (jugadores[i].mazo, canFichasJug);
        }
    } while (verificarDobles () == TRUE);

    printf ("Valor verificarDobles:\t%i\n\n", verificarDobles ());

    /* ASIGNAMOS EL RESTO DE FICHAS A LA LISTA 'listaFichasParaComer' */
    for (int i = 0; i < totalFichas; i++) { listaFichasParaComer[i] = listaMazoTotal[i]; }
    ordenarFichas (listaFichasParaComer, totalFichas);
}

// Función para Inicializar las Fichas:
void inicializarFichas () {
    int numFicha = 0;
    for (int i = 0; i <= 6; i++) {
        for (int j = i; j <= 6 ; j++) {
            listaMazoTotal[numFicha].numFicha = numFicha + 1;
            listaMazoTotal[numFicha].valores[0] = i;
            listaMazoTotal[numFicha].valores[1] = j;
            listaMazoTotal[numFicha].salida = 0;
            numFicha ++;
        }
    }
}

// Función para Crear a los Jugadores:
void crearJugadores () {
    //AQUÍ HAY QUE VERIFICAR 'log.txt'
    
    /* SOLICITAMOS LA CANTIDAD DE JUGADORES */
    printf ("Digite la Cantidad de Jugadores\n-> ");
    scanf ("%i", &canJug);

    /* CREAMOS A LOS JUGADORES */
    for (int i = 0; i < canJug; i++) {
        system ("clear");           /* Limpiamos la Pantalla del Terminal  */

        /* SOLICITAMOS EL NOMBRE DE CADA JUGADOR */
        printf ("Digite el nombre del Jugador %i\n-> ", i + 1);
        scanf ("%s", jugadores[i].nom);
    }
}

// Función para Revolver las Fichas:
void revolverFichas (Ficha f[], int size) {
    /*******************************************************
        Revolvemos las fichas intercambiandolas de lugar
        de forma aleatoria utilizando la funcion 'rand()'
    ********************************************************/
    srand(time(NULL)); // <- SEMILLA
    for (int i = 0; i < size; i++) {
        int aux = rand () % size;       /* Auxiliar para tener una posición aleatoria     */
        Ficha temp = f[i];              /* Auxiliar Temporal para Realizar el Intercambio */
        // INTERCAMBIAMOS POSICIONES:
        f[i] = f[aux];
        f[aux] = temp;
    }
}

// Función para Ordenar las Fichas:
void ordenarFichas (Ficha f[], int size) {
    /* ORDENAMOS CON EL MÉTODO DE LA BURBUJA */
    for (int i = 0; i < size; i++) {
        for (int actual = 0; actual < size - 1; actual++) {
            int sig = actual + 1;
            /************************************************************************
                Si el 'actual' es mayor que 'siguiente', intercambiamos. Es decir,
                movemos el actual a la derecha y el de la derecha al actual:
            *************************************************************************/
            if (f[actual].numFicha > f[sig].numFicha) {
                // INTERCAMBIAMOS POSICIONES:
                Ficha temp = f[actual];
                f[actual] = f[sig];
                f[sig] = temp;
            }
        }
    }
}

// Función para Eliminar Elementos de un Vector:
void delElement (Ficha f[], int pos) {
    for (int i = pos; i < totalFichas; i++) {
        f[i] = f[i + 1];
    }
    totalFichas--;
    // printf ("totalFichas = \t%i\n", totalFichas);
}

// Función para Verficiar que no Existan Dobles:
int verificarDobles () {
    for (int i = 0; i < canJug; i++) {
        int dobles = 0;
        for (int j = 0; j < canFichasJug; j++) {
            if (jugadores[i].mazo[j].valores[0] == jugadores[i].mazo[j].valores[1]) {
                dobles++;
            }
        }
        if (dobles >= 4) { return TRUE; }
    }
    return FALSE;
}

/* FUNCIONES PARA PROBAR EL PROGRAMA */
void imprimir() {
    // Mostramos los datos del Jugador correpondiente:
    for (int i = 0; i < canJug; i++) {
        printf ("Datos del Jugador %d:\n", i+1);
        printf ("Nombre:\t%s\n", jugadores[i].nom);
        printf ("Fichas:\n");
        for (int j = 0; j < canFichasJug; j++) {
            printf ("\t#%i =\t[%i|%i]\n", j + 1, jugadores[i].mazo[j].valores[0], jugadores[i].mazo[j].valores[1]);
        }
        printf ("\n\n");
    }
}