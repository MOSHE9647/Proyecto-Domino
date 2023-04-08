#ifndef FICHA_H
#define FICHA_H

/************************************************************
    ARCHIVO DE CABECERA DONDE SE ENCUENTRAN LA ESTRUCTURA,
    FUNCIONES O MÉTODOS RELACIONADOS A LAS FICHAS DEL DOMINO
*************************************************************/

#include <stdlib.h>         /* Librería para el Uso de Rand, Srand y System */
#include <stdio.h>          /* Librería para Operaciones de E/S */
#include <time.h>           /* Librería para el Uso como Semilla de Srand   */

#define MAX_COMER 10        /* Tamaño máximo de las Fichas para Comer */
#define MAX_TILES 9         /* Cantidad máxima de Fichas por Jugador  */
#define DOMINO 28           /* Cantidad de Fichas que posee el Juego  */

/* ESTRUCTURA PARA LAS FICHAS */
typedef struct {
    int valores[2];         /* Valores que tiene la Ficha [Izq|Der]         */
    int numFicha;           /* Variable para el ordenamiento de las fichas  */
    int salida;             /* Variable para obtener la 'punta' de la Ficha */
    int doble;
} Ficha;

/* VARIABLES GLOBALES */
Ficha listaFichasParaComer[MAX_COMER];  /* Lista de las Fichas para Comer      */
Ficha listaMazoTotal[DOMINO];           /* Lista de todas las Fichas del Juego */
int totalFichas = DOMINO;               /* Para Manejo de Vectores en el Juego */

/* FUNCIONES A UTILIZAR DENTRO DEL JUEGO */
// ** CTRL + Click para ir a la Funcion
void revolverFichas (Ficha f[], int size);  /* Función para Revolver una Lista de Fichas    */
void ordenarFichas (Ficha f[], int size);   /* Función para Ordenar una Lista de Fichas     */
void delElement (Ficha f[], int pos);       /* Funcion para Eliminar Elementos de un Vector */
void inicializarFichas ();                  /* Inicializa las Variables de 'listaMazoTotal' */

/****************************************** FUNCIONES ******************************************/
// Función para Inicializar las Fichas:
void inicializarFichas () {
    int numFicha = 0; /* Contador para asignar el Número de Ficha */
    for (int i = 0; i <= 6; i++) {
        for (int j = i; j <= 6 ; j++) {
            /***********************************************************
                Con estos 'for' le asignamos a cada fichalo siguiente:
                Número de Ficha: Que va desde 1 a 28
                Valores: De 0 a 6 ([i] = Izq, [j] = Der)
                Salida: Indica si la ficha tiene una 'punta' libre
            ************************************************************/
            listaMazoTotal[numFicha].numFicha = numFicha + 1;
            listaMazoTotal[numFicha].valores[0] = i;
            listaMazoTotal[numFicha].valores[1] = j;
            listaMazoTotal[numFicha].salida = 0;
            if (listaMazoTotal[numFicha].valores[0] == listaMazoTotal[numFicha].valores[1]) { 
                listaMazoTotal[numFicha].doble == 1; 
            }
            numFicha ++;
        }
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
        int aux = rand () % size; /* Auxiliar para obtener una posición aleatoria   */
        Ficha temp = f[i];        /* Auxiliar Temporal para Realizar el Intercambio */
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
        /*******************************************
            Corremos el Elemento una Posición a la
            Derecha y Decrementamos 'totalFichas'
        ********************************************/
        f[i] = f[i + 1];
    }
    totalFichas--;
}

#endif