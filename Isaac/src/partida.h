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
int finPartida = FALSE;
sem_t mutex;
Mesa *mesa;

/* FUNCIONES A UTILIZAR DENTRO DEL JUEGO */
// ** CTRL + Click para ir a la Funcion
void iniciarPartida(int type, int Jugs); /* Funcion para Iniciar la Partida con 'n' Jugadores */
void ponerFicha (Jugador *j, int pos);   /* Funcion para Poner una Ficha en la Mesa           */
void comerFichas(Jugador *j);            /* Para que Jugador tome una Ficha del mazo          */
Jugador *buscarDobles ();
void *jugar (void *arg);
void repartirFichas ();                  /* Función que Reparte Fichas a cada Jugador         */
void aciertaPuntos();                    /* Función para Manejar el Puntaje del Juego         */
void finJuego();                         /* Función que se llama al Finalizar el Juego        */
void imprimir();

/***************************************** FUNCIONES *****************************************/
// Iniciamos una Nueva Partida:
void iniciarPartida(int type, int Jugs) {
    // type = NEW: Nueva Partida : OLD: Continuar Partida
    mesa = (Mesa*) calloc (sizeof(Mesa), 1); /* Creamos la Mesa del Juego */
    if (type == NEW) {
        canJug = Jugs;              /* Indicamos la Cantidad de Jugadores solicitada      */
        crearJugadores(NEW);        /* Creamos a cada uno de los Jugadores segun 'canJug' */
    } else { 
        crearJugadores(OLD);        /* Creamos los Jugadores a partir de un Archivo       */
        finPartida = FALSE;
    } 
    repartirFichas();               /* Creamos y repartimos las Fichas a Cada Jugador     */

    sem_init(&mutex, 1, 1);
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
    for (int i = temp->turno + 1; i < canJug; i++) {
        if (i == canJug - 1) {
            pthread_create(&players[i], NULL, jugar, &i);
            pthread_join(players[i], NULL);
            i = -1;
        } else {
            pthread_create(&players[i], NULL, jugar, &i);
            pthread_join(players[i], NULL);
        }
    }

    sem_destroy(&mutex);
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
            ordenarFichas (jugadores[i].mazo, canFichasJug); /* Ordenamos las Fichas del Jugador       */
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
void aciertaPuntos() {
    FILE* archivo; /* Variable que apunta al Archivo que vamos a utilizar */

	char PUNTOS[CHAR_LIMIT];  /* Variable para almacenar la edad en formato string   */
	char TOTALP[CHAR_LIMIT];  /* Variable para almacenar la ID en formato string     */
    char GANADOS[CHAR_LIMIT];

	archivo = fopen(ARCHIVO, "w"); /* Abrimos el archivo en modo escritura sin sobreescribir */

    // Verificamos que se haya leído el archivo:
	if (archivo == NULL) {
		printf("Error al abrir el archivo.");
        return; /* No se leyó correctamente */
	} else {
		for (int i = 0; i < canJug; i++) {
            sprintf (PUNTOS, "%d", jugadores[i].puntos);        /* Convertimos puntos de 'int' a 'string'       */
            sprintf (TOTALP, "%d", jugadores[i].totalPuntos);   /* Convertimos totalPuntos de 'int' a 'string'  */
            sprintf (GANADOS, "%d", jugadores[i].totalGanados); /* Convertimos totalGanados de 'int' a 'string' */
            
            /* Escribimos la información de las variables en el archivo */
            fputs (jugadores[i].nom, archivo);  fputs (" ", archivo);
            fputs (PUNTOS, archivo);            fputs (" ", archivo);
            fputs (TOTALP, archivo);            fputs (" ", archivo);
            fputs (GANADOS, archivo);           fputs ("\n", archivo);
        }
	}
	fclose (archivo); /* Cerramos el archivo   */
}

void finJuego() {
    system("clear");
    int puntajeMayor = 0;
    char ganador[CHAR_LIMIT];
    int pos = 0;
    printf ("\n");
    printf ("\t      ╔═══════════════════╗\n");
    printf ("\t╔═════╣   FIN DEL JUEGO   ╠═════╗\n");
    printf ("\t╠═════╣ REPORTE DE PUNTOS ╠═════╣\n");
    printf ("\t║     ╚═══════════════════╝     ║\n");
    printf ("\t║  JUGADOR        PTS     WINS  ║\n");
    printf ("\t║  ═══════════════════════════  ║\n");
    for (int i = 0; i < canJug; i++) {
        printf ("\t║  %s\t   %i\t %i\t║\n", jugadores[i].nom, jugadores[i].puntos, jugadores[i].totalGanados);
        if (jugadores[i].puntos > puntajeMayor) { 
            puntajeMayor = jugadores[i].puntos;
            strcpy (ganador, jugadores[i].nom);
            pos = i;
        }
    }
    jugadores[pos].totalGanados++;
    printf ("\t║                               ║\n");
    printf ("\t║  ═══════════════════════════  ║\n");
    printf ("\t║                               ║\n");
    printf ("\t║     GANADOR:    %s\t\t║\n", ganador);
    printf ("\t╚═══════════════════════════════╝\n\n");

    finPartida = TRUE;
    aciertaPuntos();
    return;
}

void ponerFicha (Jugador *j, int pos) {
    if (mesa->raiz == NULL) {
        AgregarNodoArbol (mesa, &j->mazo[pos], NULL, 0, 0);
        printf ("%s puso la Ficha [%i|%i] en la mesa\n", j->nom, j->mazo[pos].valores[0], j->mazo[pos].valores[1]);
        delElement (j->mazo, pos, &j->canMazoJug);
    } else {
        int posicion = -1, direccion = 0, cruzado = 0, puntos = 0;
        Lista *lista = Fichas_Libres(mesa);
        printf ("Posibles Jugadas:\n");
        Nodo *destino = bucarDondeColocar (lista, j->mazo, j->canMazoJug, &posicion, &direccion, &cruzado, &puntos);
        if (destino != NULL) {
            AgregarNodoArbol(mesa, &j->mazo[posicion], destino, direccion, cruzado);
            Mostrar_Lista (lista);
            printf ("Puntos: %d\tFicha: [%i|%i]\n", puntos, j->mazo[posicion].valores[0], j->mazo[posicion].valores[1]);
            delElement (j->mazo, posicion, &j->canMazoJug);
            if (puntos != 0 && puntos % 5 == 0) { 
                j->puntos += puntos / 5;
                j->totalPuntos += puntos;
                aciertaPuntos();
                printf ("Adquiere %i Puntos\n\n", (puntos / 5));
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

    sem_wait(&mutex);

    printf ("Turno de %s\n", jugadores[ID].nom);
    printf ("Fichas:\n");
    for (int j = 0; j < jugadores[ID].canMazoJug; j++) {
        printf ("\t#%i =\t[%i|%i]\n", j + 1, jugadores[ID].mazo[j].valores[0], jugadores[ID].mazo[j].valores[1]);
    }
    printf ("\n");
    ponerFicha(&jugadores[ID], 0);
    sysPause(); system("clear");

    sem_post(&mutex);
    pthread_exit(NULL);
}


/* FUNCIONES PARA PROBAR EL PROGRAMA */
void imprimir() {
    // Mostramos los datos del Jugador correpondiente:
    for (int i = 0; i < canJug; i++) {
        printf ("Datos del Jugador %d:\n", i+1);
        printf ("Nombre:\t\t%s\n", jugadores[i].nom);
        printf ("Puntos:\t\t%i\n", jugadores[i].puntos);
        printf ("Total Puntos:\t%i\n", jugadores[i].totalPuntos);
        printf ("Total Ganados:\t%i\n", jugadores[i].totalGanados);
        printf ("Fichas:\n");
        for (int j = 0; j < jugadores[i].canMazoJug; j++) {
            printf ("\t#%i =\t[%i|%i]\n", j + 1, jugadores[i].mazo[j].valores[0], jugadores[i].mazo[j].valores[1]);
        }
        printf ("\n\n");
    }
    
    printf ("Fichas para Comer:\ttotalFichas = %i\n", totalFichas);
    for (int i = 0; i < totalFichas; i++) {
        printf ("\tFicha #%i =\t[%i|%i]\n", i + 1, listaFichasParaComer[i].valores[0], listaFichasParaComer[i].valores[1]);
    }
    printf ("\n");
}

#endif