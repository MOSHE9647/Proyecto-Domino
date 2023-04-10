#ifndef PARTIDA_H
#define PARTIDA_H

/***************************************************************
    ARCHIVO DE CABECERA DONDE SE ENCUENTRAN LAS VARIABLES,
    FUNCIONES O METODOS REALCIONADOS AL JUEGO QUE SE VAN A
    UTILIZAR DURANTE LA PARTIDA. ESTE ARCHIVO INCLUYE LO
    RELACIONADO A SEMAFOROS, ARCHIVOS, MENUS Y DEMÁS COSAS
    RELACIONADAS A UNA PARTIDA.
****************************************************************/

#include <semaphore.h>           /* Para uso de Semáforos en el Juego   */
#include <pthread.h>             /* Para el uso de Hilos en el Juego    */
#include <unistd.h>              /* Para uso de Sleep */
#include "jugador.h"             /* Archivo de Cabecera de Jugador      */
#include "lista.h"
#include "mesa.h"

/* VARIABLES GLOBALES */
pthread_t players[MAX_PLAYERS];
sem_t turno;
Mesa *mesa;

/* FUNCIONES A UTILIZAR DENTRO DEL JUEGO */
// ** CTRL + Click para ir a la Funcion
void iniciarPartida(int type, int Jugs); /* Funcion para Iniciar la Partida con 'n' Jugadores */
void aciertaPuntos(Jugador *j);          /* Función para Manejar el Puntaje del Juego         */
void comerFichas(Jugador *j);            /* Para que Jugador tome una Ficha del mazo          */
void ponerFicha (Jugador *j, int pos);   /* Funcion para Poner una Ficha en la Mesa           */
void repartirFichas ();                  /* Función que Reparte Fichas a cada Jugador         */
void finJuego();                         /* Función que se llama al Finalizar el Juego        */

void *jugar (void *arg);

Jugador *buscarDobles ();

/*********************************** FUNCIONES ***********************************/
// Iniciamos una Nueva Partida:
void iniciarPartida(int type, int Jugs) {
    // type = NEW: Nueva Partida : OLD: Continuar Partida

    mesa = (Mesa*) calloc (sizeof(Mesa), 1); /* Creamos la Mesa del Juego */
    if (type == NEW) {
        canJug = Jugs;              /* Indicamos la Cantidad de Jugadores solicitada      */
        crearJugadores(NEW);        /* Creamos a cada uno de los Jugadores segun 'canJug' */
    } else { crearJugadores(OLD); } /* Creamos los Jugadores a partir de un Archivo       */
    repartirFichas();               /* Creamos y repartimos las Fichas a Cada Jugador     */

    sem_init(&turno, 1, 1);
    // sem_init(&mesa_arbol, 1, 1);
    pthread_t players[canJug];

    Jugador *temp;
    while ((temp = buscarDobles()) == NULL) {
        printf ("No se encontró Ninguna Ficha Doble\n");
        printf ("Repartiendo de Nuevo.\n");
        sleep(2); system("clear");
        printf ("No se encontró Ninguna Ficha Doble\n");
        printf ("Repartiendo de Nuevo..\n");
        sleep(2); system("clear");
        printf ("No se encontró Ninguna Ficha Doble\n");
        printf ("Repartiendo de Nuevo...\n");
        sleep(2); system("clear");
        repartirFichas();
        sysPause();
    }
    for (int i = temp->turno; i < canJug; i++) {
        if (i == canJug - 1) {
            i = 0;
            pthread_create(&players[i+1], NULL, jugar, &i);
            pthread_join(players[i+1], NULL);
            // printf ("Turno de %s\n", jugadores[i].nom);
            // printf ("Fichas:\n");
            // for (int j = 0; j < jugadores[i].canMazoJug; j++) {
            //     printf ("\t#%i =\t[%i|%i]\n", j + 1, jugadores[i].mazo[j].valores[0], jugadores[i].mazo[j].valores[1]);
            // }
            // ponerFicha(&jugadores[i], 0);
            // sysPause(); system("clear");
        }
        pthread_create(&players[i+1], NULL, jugar, &i);
        pthread_join(players[i+1], NULL);
    }

    // for (int i = 0; i < canJug; i++) {
    //     pthread_join(players[i], NULL);
    // }

    sem_destroy(&turno);
    // sem_destroy(&mesa_arbol);
}

// Función para Repartir Fichas:
void repartirFichas () {
    /* REVOLVEMOS LAS FICHAS Y LAS REPARTIMOS */
    do {
        int canFichasJug = DOMINO / (canJug + 1); /* Cantidad de Fichas a Repartir */
        totalFichas = DOMINO;                     /* Existen 28 Fichas en Total    */
        inicializarFichas ();                     /* Creamos las Fichas del Juego  */
        revolverFichas (listaMazoTotal, DOMINO);  /* Revolvemos las Fichas         */
        for (int i = 0; i < canJug; i++) {
            jugadores[i].canMazoJug = canFichasJug;
            for (int j = 0; j < canFichasJug; j++) {
                jugadores[i].mazo[j] = listaMazoTotal[0];    /* Asignamos la Ficha al Mazo del Jugador */
                delElement(listaMazoTotal, 0, &totalFichas); /* Eliminamos la Ficha de la Lista        */
            }
            ordenarFichas (jugadores[i].mazo, canFichasJug); /* Ordenamos las Fichas del Jugador    */
        }
        /*************************************************
            CON EL CICLO NOS ASEGURAMOS DE QUE NINGUN
            JUGADOR POSEA MAS DE 4 DOBLES EN LA PARTIDA
        **************************************************/
    } while (verificarDobles () == TRUE);
    /* ASIGNAMOS EL RESTO DE FICHAS A LA LISTA 'listaFichasParaComer' */
    for (int i = 0; i < totalFichas; i++) { listaFichasParaComer[i] = listaMazoTotal[i]; }
    ordenarFichas (listaFichasParaComer, totalFichas); /* Ordenamos la Lista */
}

// Función para Comer Fichas:
void comerFichas (Jugador *j) {
    /********************************************************
        Esta funcion hace lo siguiente (linea por linea)
        siempre y cuando hayan fichas para comer:
        1. Revuelve la Lista de Fichas que Hay para Comer.
        2. Le asigna esa Ficha al Mazo del Jugador.
        3. Elimina de la Lista la Ficha que se agarró.
        4. Vuelve a ordenar la Lista de Fichas.
        5. Incrementa en 1 la Cantidad de Fichas que
           posee el Jugador.
        *Si ya no hay fichas para comer se termina el juego.
     ********************************************************/
    if (totalFichas > 0) {
        revolverFichas(listaFichasParaComer, totalFichas);
        j->mazo[j->canMazoJug] = listaFichasParaComer[0];
        delElement (listaFichasParaComer, 0, &totalFichas);
        ordenarFichas(listaFichasParaComer, totalFichas);
        j->canMazoJug++;
    } else { finJuego (); }
}

// Función para manejar el puntaje del Juego:
void aciertaPuntos(Jugador *j) {
    /* ESTO ES DE PRUEBA NO FUNCIONA */
    FILE *archivo = fopen(ARCHIVO, "r+");

    fseek(archivo, 0, SEEK_SET);

    char linea[100];
    int numeroLinea = 5; // Linea que se desea sobrescribir
    for (int i = 0; i < numeroLinea - 1; i++) {
        fgets(linea, 100, archivo); // Lee cada línea hasta llegar a la línea deseada
    }

    int numCaracteres = ftell(archivo);
    int posicion = (numeroLinea) * numCaracteres; // 100 es el tamaño máximo de cada línea
    fseek(archivo, posicion, SEEK_SET); // Coloca el puntero al inicio de la línea

    char nuevaLinea[100] = "Esta es la nueva línea"; // La nueva línea a escribir
    fputs(nuevaLinea, archivo);

    fclose(archivo);
}

void finJuego() {
    system("clear");
    printf ("Fin del Juego\n");
    printf ("Mesa:\n\n");
    Mostrar_Nodos(mesa);

    

    exit(0);
}

void ponerFicha (Jugador *j, int pos) {
    if (mesa->raiz == NULL) {
        AgregarNodoArbol (mesa, &j->mazo[pos], NULL, 0, 0);
        printf ("%s puso la Ficha [%i|%i] en la mesa\n", j->nom, j->mazo[pos].valores[0], j->mazo[pos].valores[1]);
        delElement (j->mazo, pos, &j->canMazoJug);
    } else {
        int posicion = -1, direccion = 0, cruzado = 0, puntos = 0;
        Lista *lista = Fichas_Libres(mesa);
        Nodo *destino = bucarDondeColocar (lista, j->mazo, j->canMazoJug, &posicion, &direccion, &cruzado, &puntos);
        if (destino != NULL) {
            AgregarNodoArbol(mesa, &j->mazo[posicion], destino, direccion, cruzado);
            Mostrar_Lista (lista);
            printf ("\nPuntos: %d\tFicha: [%i|%i]\t Posicion = %i\n", puntos, j->mazo[posicion].valores[0], j->mazo[posicion].valores[1], posicion);
            delElement (j->mazo, posicion, &j->canMazoJug);
            if (puntos != 0 && puntos % 5 == 0) { 
                j->puntos += puntos / 5;
                j->totalPuntos += puntos;
                printf ("Adquiere %i Puntos\n", (puntos / 5));
            }
        } else {
            printf ("%s tuvo que Comer una Ficha y pierde turno\n", j->nom);
            comerFichas(j);
        }
        Liberar_Lista(lista);
    }
}

Jugador *buscarDobles () {
    int doble = 6;
    while (doble >= 0) {
        for (int i = 0; i < canJug; i++) {
            for (int j = 0; j < jugadores[i].canMazoJug; j++) {
                if (jugadores[i].mazo[j].doble && jugadores[i].mazo[j].valores[0] == doble) {
                    printf ("Se encontró la Ficha Doble [%i|%i] en el Mazo de %s\n", jugadores[i].mazo[j].valores[0], jugadores[i].mazo[j].valores[1], jugadores[i].nom);
                    printf ("Colocando Ficha en la Mesa.\n\n");
                    ponerFicha(&jugadores[i], j);
                    sysPause(); system ("clear");
                    return &jugadores[i];
                }
            }
        }
        doble--;
    }
    return NULL;
}

void *jugar (void *arg) {
    int ID = *(int *)arg;

    sem_wait(&turno);

    printf ("Turno de %s\n", jugadores[ID].nom);
    printf ("Fichas:\n");
    for (int j = 0; j < jugadores[ID].canMazoJug; j++) {
        printf ("\t#%i =\t[%i|%i]\n", j + 1, jugadores[ID].mazo[j].valores[0], jugadores[ID].mazo[j].valores[1]);
    }
    printf ("\n");
    ponerFicha(&jugadores[ID], 0);
    sysPause(); system("clear");

    sem_post(&turno);
    pthread_exit(NULL);
}

#endif