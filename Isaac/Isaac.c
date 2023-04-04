/* Archivo de Trabajo de Isaac */
#include <stdio.h>          /* Libreria Entrada y Salida Estándar */
#include <stdlib.h>         /* Libreria Estándar                  */ /*****/
#include <string.h>         /* Libreria para utilizar 'strcpy'    */
#include <time.h>           /* Para el uso de números aleatorios  */ /*****/

// Definimos algunas Variables:
#define MAX_CHAR 100        /* Cantidad maxima de caracteres a utilizar (nombres, lectura o escritura) */
#define MAX_TILES 9         /* Cantidad maxima de fichas que puede poseer un Jugador                   */
#define MAX_JUG 7           /* Cantidad maxima de jugadores que pueden haber por partida               */
#define DOMINO 28           /* Cantidad maxima de fichas que hay en el juego                           */
#define TRUE 1              /* Variable para utilizar e indicar el valor 1 como 'true'                 */
#define FALSE 0             /* Variable para utilizar e indicar el valor 0 como 'false'                */

// Estructura para las Fichas:
typedef struct {
    int valores[2];         /* Vector para representar los 2 valores que posee una ficha '[1|2]' */
    int numFicha;           /* Variable que se utilizara para el ordenamiento de las fichas      */
    int doble;              /* Variable para indicar si una ficha es doble o no                  */
} Ficha;

// Estructura para los Jugadores:
typedef struct {
    char nombre[MAX_CHAR];  /* Variable que almacena el nombre de cada Jugador                           */
    Ficha mazo[MAX_TILES];  /* Vector dinámico para almacenar la mano de fichas que posee el Jugador     */
    int totalGanados;       /* Variable que almacena la cantidad de juegos ganados que lleva Jugador     */
    int totalPuntos;        /* Variable para almacenar la cantidad total de puntos que tiene Jugador     */
    int puntos;             /* Variable que almacena la cantidad de puntos que lleva Jugador por partida */
    int turno;              /* Variable que va a almacenar en que turno le toca poner ficha al Jugador   */
} Jugador;

// Variables Globales:
Jugador jugadores[MAX_JUG]; /* Vector para almacenar cada uno de los Jugadores              */
Ficha *fichas = NULL;       /* Vector Dinámico para almacenar las Fichas                    */
int canJug = 0;             /* Variable para almacenar la cantidad de jugadores por partida */

// Declaracion de las Funciones a utilizar dentro del Juego:
void ordenarFichas (Ficha *f, int lenght);  /* Funcion para ordenar las fichas del juego y maso */
void revolverFichas (Ficha *f, int size);   /* Funcion para revolver las fichas del juego       */
void repartirFichas (void);                 /*  */
int crearFichas (void);                     /* Funcion para crear las fichas del Juego */
void systemPause(void);                     /* Funcion para hacer una pausa en consola */

// Función principal del programa:
int main () {
    // Agregar opción: '3. Continuar'
    if (crearFichas()) { printf ("Se crearon las Fichas.\n"); }
    else { printf ("No se pudieron crear las Fichas.\n"); }

    repartirFichas();

    return 0;
}

// Desarrollamos las Funciones que vamos a utilizar dentro del Código:
int crearFichas () {
    /* Creamos las fichas que se van a utilizar en el juego */
    Ficha *temp;        /* Variable temporal para crear las fichas del Juego */
    int contador = 0;   /* Contador para la cantidad de Fichas creadas       */

    for (int i = 0; i <= 6; i++) {
        for (int j = i; j <= 6; j++) {
            // Con esto nos aseguramos de que no se repitan fichas:
            //if (j >= i) { /**ISAAC PUEDES ELIMINAR ESTA CONDICIONAL HE INICIAR "j = i" en el for y se ahorra esto**/
                fichas = realloc(fichas, (contador + 1) * sizeof(Ficha));   /* Asignamos Memoria a Fichas    */
                temp = calloc(sizeof(Ficha), 1);                            /* Asignamos Memoria al auxiliar */
                temp->valores[0] = i;                                       /* Asignamos 'i' como valor izq  */
                temp->valores[1] = j;                                       /* Asignamos 'j' como valor der  */
                temp->numFicha = contador;                                  /* Le damos un Número a la Ficha */
                memcpy(&fichas[contador], temp, sizeof(Ficha));             /* La ponemos en el Vector       */
                free(temp);                                                 /* Liberamos la memoria          */
                contador++;                                                 /* Aumentamos el contador        */
            //}
        }
    }
    return fichas != NULL ? TRUE : FALSE;
}
void repartirFichas (void) {
    printf ("Digite el Número de Jugadores: ");     /* <- Solicitamos la Cantidad de Jugadores */
    scanf ("%d", &canJug);                          /* <- Se la asignamos a canJug             */
    revolverFichas (fichas, DOMINO);                /* <- Revolvemos las Fichas                */

    // Repartimos las Fichas a los Jugadores:
    int canFichasJugador = DOMINO / (canJug + 1);   /* <- Asignamos la cantidad de fichas que se van a utilizar */
    int contador = 0;
    for (int i = 0; i < canJug; i++) {

        for (int j = 0; j < canFichasJugador && contador < DOMINO; j++) {
            jugadores[i].mazo[j] = fichas[contador];
            contador ++;
        }
    }

    // Guardamos las fichas sobrantes:
    for (int i = contador + 1, j = 0; i <= DOMINO && j < (DOMINO - contador); i++, j++) {
        /* 
            Ejemplo de funcionamiento con 2 jugadores:

            -> canJug = 2;
            -> canFichasJugador =  9;
            -> contador = (2 * 9) = 18;

            for (i = 18 + 1, j = 0; i <= 28 && j < 28 - 18; i++, j++)
        */
        jugadores[canJug + 1].mazo[j] = fichas[i];
        strcpy(jugadores[canJug + 1].nombre, "Fichas para Comer");
    }

    // Ordenamos las fichas de cada mazo:
    for (int i = 0; i < canJug; i++) {
        ordenarFichas(jugadores[i].mazo, canFichasJugador);
    }
}
void revolverFichas (Ficha *f, int size) {
    /*
        Revolvemos las fichas intercambiandolas de lugar
        de forma aleatoria utilizando la funcion 'rand()'
    */
    srand(time(NULL));          /* Semilla para los números aleatorios */
    for (int i = 0; i < size; i++) {
        int j = rand() % size;  /* Variable con las posiciones a intercambiar  */
        Ficha temp = f[i];      /* Variable auxiliar para realizar el cambio   */
        f[i] = f[j];            /* Realizamos los Intercambios                 */
        f[j] = temp;
    }
}
void ordenarFichas (Ficha *f, int lenght) {
    /* Ordenamiento por Método de la Burbuja */
    for (int i = 0; i < lenght; i++) {
        for (int actual = 0; actual < lenght - 1; actual++) {
            int siguiente = actual + 1;
            /*
                Si el actual es mayor que el que le sigue a la derecha, intercambiamos. Es decir,
                movemos el actual a la derecha y el de la derecha al actual:
            */
            if (f[actual].numFicha > f[siguiente].numFicha) {
                Ficha temporal = f[actual];
                f[actual] = f[siguiente];
                f[siguiente] = temporal;
            }
        }
    }
}