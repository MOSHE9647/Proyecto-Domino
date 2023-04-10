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
#include "jugador.h"             /* Archivo de Cabecera de Jugador      */
#include "lista.h"
#include "mesa.h"

/* SEMAFOROS (HILOS) */
void* jugar (void *arg);
sem_t mesa_arbol;
sem_t fichasComer;
sem_t primera;
sem_t turno;

/* VARIABLES GLOBALES */
int primerFicha[3] = {6, 0, FALSE};
Mesa *mesa;

/* FUNCIONES A UTILIZAR DENTRO DEL JUEGO */
// ** CTRL + Click para ir a la Funcion
void iniciarPartida(int type, int Jugs); /* Funcion para Iniciar la Partida con 'n' Jugadores */
void aciertaPuntos(Jugador *j);          /* Función para Manejar el Puntaje del Juego         */
void comerFichas(Jugador *j);            /* Para que Jugador tome una Ficha del mazo          */
void ponerFicha(Jugador *j);             /* Funcion para Poner una Ficha en la Mesa           */
void repartirFichas ();                  /* Función que Reparte Fichas a cada Jugador         */
void finJuego();                         /* Función que se llama al Finalizar el Juego        */

/*********************************** FUNCIONES ***********************************/
// Iniciamos una Nueva Partida:
void iniciarPartida(int type, int Jugs) {
    mesa = (Mesa*) calloc (sizeof(Mesa), 1); /* Creamos la Mesa del Juego */
    if (type == NEW) {
        canJug = Jugs;              /* Indicamos la Cantidad de Jugadores solicitada      */
        crearJugadores(NEW);        /* Creamos a cada uno de los Jugadores segun 'canJug' */
    } else { crearJugadores(OLD); } /* Creamos los Jugadores a partir de un Archivo       */
    repartirFichas();   /* Creamos y repartimos las Fichas a Cada Jugador     */
    
    // sem_init(&turno, 1, 1);
    // sem_init(&mesa_arbol, 1, 1);
    // pthread_t players[canJug];

    // for (int i = 0; i < canJug; i++) {
    //     pthread_create(&players[i], NULL, jugar, &i);
    // }

    // for (int i = 0; i < canJug; i++) {
    //     pthread_join(players[i], NULL);
    // }

    // sem_destroy(&turno);
    // sem_destroy(&mesa_arbol);

    while (!primerFicha[2]) {
        for (int i = 0; i < canJug; i++) {
            ponerFicha (&jugadores[i]);
            if ((primerFicha[1] + 1) == canJug) {
                primerFicha[0]--;
                i = 0;
            }
            if (primerFicha[0] < 0) {
                printf ("Ningún Jugador posee una Ficha Doble!!\n");
                printf ("Volvemos a Repartir...\n\n");
                sysPause();
                repartirFichas();
                primerFicha[0] = 6;
                primerFicha[1] = 0;
                break;
            }
        }
    }
    ponerFicha(&jugadores[0]);
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
        Esta funcion hace lo siguiente (linea por linea):
        1. Revuelve la Lista de Fichas que Hay para Comer
        2. Le asigna esa Ficha al Mazo del Jugador
        3. Elimina de la Lista la Ficha que se agarró
        4. Vuelve a ordenar la Lista de Fichas
        5. Incrementa en 1 la Cantidad de Fichas que
           posee el Jugador.
     ********************************************************/
    if (j->canMazoJug < MAX_TILES) {
        revolverFichas(listaFichasParaComer, totalFichas);
        j->mazo[j->canMazoJug + 1] = listaFichasParaComer[0];
        delElement (listaFichasParaComer, 0, &totalFichas);
        ordenarFichas(listaFichasParaComer, totalFichas);
        j->canMazoJug++;
    }
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
    printf ("Fin del Juego");
    printf ("Mesa:\n\n");
    Mostrar_Nodos(mesa);
    sysPause();
}



void ponerFicha (Jugador *j) {
    int pos = -1; /* Posición de la Ficha en el Mazo del Jugador */
    for (int i = 0; i < j->canMazoJug; i++) {
        printf ("Mazo Jugador %s", j->nom);
        printf ("\t#%i =\t[%i|%i]\n", i + 1, j->mazo[i].valores[0], j->mazo[i].valores[1]);
    }
    printf ("\n\n");

    if (mesa->raiz == NULL) {
        for (int i = 0; i < j->canMazoJug; i++) {
            if (j->mazo[i].doble && j->mazo[i].valores[0] == primerFicha[0]) {
                pos = i;
                break;
            }
        }
        if (pos == -1) { 
            primerFicha[1]++;
            return; 
        }
        AgregarNodoArbol (mesa, &j->mazo[pos], NULL, 0);
        printf ("Jugador %i puso la Ficha [%i|%i] en la mesa, pos = %i\n", j->turno, j->mazo[pos].valores[0], j->mazo[pos].valores[1], pos);
        delElement (j->mazo, pos, &j->canMazoJug);
        primerFicha[2] = TRUE;
    } else {
        int posicion = -1, direccion = 0, cruzado = 0, puntos = 0;
        Lista *lista = Fichas_Libres(mesa);
        Nodo *destino = Comparando_Lista (lista, j->mazo, j->canMazoJug, &posicion, &direccion, &cruzado, &puntos);
        if (destino != NULL) {
            AgregarNodoArbol(mesa, &j->mazo[posicion], destino, direccion);
            Mostrar_Lista (lista);
            delElement (j->mazo, posicion, &j->canMazoJug);
            if (puntos != 0) { 
                j->puntos += puntos / 5;
                j->totalPuntos += puntos; 
            }
        } else {
            totalFichas > 0 ? comerFichas(j) : finJuego();
        }
        Liberar_Lista(lista);
    }
}

// SEMAFORO:
void* jugar (void *arg) {
    int ID = *(int *) arg;

    sem_wait (&turno);
    printf("Turno del Jugador %i:\n", ID);
    
    sem_wait (&mesa_arbol);
    printf ("Buscando Ficha Doble\n");
    while (!primerFicha[2]) {
        for (int i = 0; i < canJug; i++) {
            ponerFicha (&jugadores[i]);
            if ((primerFicha[1] + 1) == canJug) {
                primerFicha[0]--;
                i = 0;
            }
            if (primerFicha[0] < 0) {
                printf ("Ningún Jugador posee una Ficha Doble!!\n");
                printf ("Volvemos a Repartir...\n\n");
                sysPause();
                repartirFichas();
                primerFicha[0] = 6;
                primerFicha[1] = 0;
                primerFicha[2] = FALSE;
                break;
            }
        }
    }
    ponerFicha(&jugadores[ID]);
    sem_post (&mesa_arbol);

    sem_post (&turno);
    pthread_exit(NULL);
}

#endif