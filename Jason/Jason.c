/*
    Archivo de Trabajo de Jason. Compilar su archivo con el siguiente comando: 
    gcc -o Jason Jason.c --> Esto para tener un orden al momento de crear los ejecutables
    ./Jason --> Comando para ejecutar el programa
*/

//ejemplo de como se podria utilizar los semaforos

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex;

void *thread_func(void *arg)
{
    int id = *(int*)arg;
    
    sem_wait(&mutex); // Espera a que el semáforo esté libre
    printf("Hilo %d ejecutando...\n", id);
    sem_post(&mutex); // Libera el semáforo
    
    pthread_exit(NULL);
}

int main()
{
    int n = 5; // Cantidad de hilos a crear
    pthread_t threads[n];
    int ids[n];
    
    // Inicializar semáforo
    sem_init(&mutex, 0, 1);
    
    // Crear hilos
    for (int i = 0; i < n; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, thread_func, &ids[i]);
    }
    
    // Esperar a que terminen los hilos
    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Destruir semáforo
    sem_destroy(&mutex);
    
    return 0;
}
