#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

/******************************************************************************
    Este archivo es un ejemplo que podemos utilizar para el uso de semáforos
    en el juego. A mi parecer se ve bastante sencillo y lo podemos usar para
    controlar todas las acciones que vayan a realizar los jugadores dentro
    del juego.
********************************************************************************/

sem_t game_table; // semáforo para la mesa de juego
sem_t chip_basket; // semáforo para la canasta de fichas

void *player(void *arg) {
   int id = *(int*)arg;

   while (1) {
      // El jugador espera a que haya suficientes fichas en la canasta
      sem_wait(&chip_basket);

      // El jugador toma una ficha de la canasta
      printf("Jugador %d tomó una ficha de la canasta.\n", id);

      // El jugador coloca su ficha en la mesa de juego
      sem_wait(&game_table);
      printf("Jugador %d colocó su ficha en la mesa de juego.\n", id);
      sem_post(&game_table);

      // El jugador coloca otra ficha en la mesa de juego
      sem_wait(&game_table);
      printf("Jugador %d colocó otra ficha en la mesa de juego.\n", id);
      sem_post(&game_table);

      // El jugador notifica que ha terminado su turno y libera una ficha en la canasta
      printf("Jugador %d terminó su turno y liberó una ficha en la canasta.\n", id);
      sem_post(&chip_basket);
      pthread_exit(NULL);
   }
}

int main()
{
   sem_init(&game_table, 0, 1); // Hay una mesa de juego disponible
   sem_init(&chip_basket, 0, 28); // Hay 28 fichas en la canasta

   pthread_t players[4];
   int ids[] = {1, 2, 3, 4};

   for (int i = 0; i < 4; i++) {
      pthread_create(&players[i], NULL, player, &ids[i]);
   }

   for (int i = 0; i < 4; i++) {
      pthread_join(players[i], NULL);
   }

   sem_destroy(&game_table);
   sem_destroy(&chip_basket);

   return 0;
}