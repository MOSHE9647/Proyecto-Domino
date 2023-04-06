#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

/******************************************************************************
   Este archivo es un ejemplo que podemos utilizar para el uso de semáforos
   en el juego. A mi parecer se ve bastante sencillo y lo podemos usar para
   controlar todas las acciones que vayan a realizar los jugadores dentro
   del juego.
*******************************************************************************/

#define DOMINO 28

/* ESTRUCTURA DE FICHA */
typedef struct {
    int valores[2];         /* Valores que tiene la Ficha ( [Izq|Der] )     */
    int salida;             /* Variable para obtener la 'punta' de la Ficha */
    int numFicha;           /* Variable para el ordenamiento de las fichas  */
} Ficha;

Ficha listaMazoTotal[DOMINO];
sem_t turno;

void *jugar(void *arg);
void inicializarFichas ();

int main() {
    sem_init(&turno, 0, 1);

    inicializarFichas();

    pthread_t players[4];
    int ids[] = {1, 2, 3, 4};

    for (int i = 0; i < 4; i++) {
        pthread_create(&players[i], NULL, jugar, &ids[i]);
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(players[i], NULL);
    }
    
    sem_destroy(&turno);

    return 0;
}

void *jugar(void *arg) {
    int ID = *(int *)arg;
    while (1) {
        sem_wait (&turno);
        srand(time(NULL));
        int j = rand() % DOMINO;
        printf("Turno del Jugador %i:\n", ID);
        printf("Jugador %d tomó una ficha de la canasta.\n", ID);
        printf("Jugador %d colocó la ficha [%i|%i] en la mesa de juego.\n", ID, listaMazoTotal[j].valores[0], listaMazoTotal[j].valores[1]);
        printf("Jugador %d terminó su turno.\n\n", ID);
        sem_post(&turno);
        pthread_exit(NULL);
    }
}
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