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

/* VARIABLES GLOBALES */
pthread_t players [MAX_PLAYERS]; /* Vector de Hilos para Jugadores           */
sem_t turnoJug;                  /* Semáforo para el Turno de cada Jugador   */
Mesa *mesa;

/* FUNCIONES A UTILIZAR DENTRO DEL JUEGO */
// ** CTRL + Click para ir a la Funcion
void iniciarPartida(int type, int Jugs); /* Funcion para Iniciar la Partida con 'n' Jugadores */
void aciertaPuntos(Jugador *j);          /* Función para Manejar el Puntaje del Juego         */
void comerFichas(Jugador *j);            /* Para que Jugador tome una Ficha del mazo          */
void repartirFichas ();                  /* Función que Reparte Fichas a cada Jugador         */
void finJuego();                         /* Función que se llama al Finalizar el Juego        */
void sysPause();                         /* Funcion que realiza una pausa en la Terminal      */

/*********************************** FUNCIONES ***********************************/
// Iniciamos una Nueva Partida:
void iniciarPartida(int type, int Jugs) {
    if (type == NEW) {
        canJug = Jugs;              /* Indicamos la Cantidad de Jugadores solicitada      */
        crearJugadores(NEW);        /* Creamos a cada uno de los Jugadores segun 'canJug' */
    } else { crearJugadores(OLD); } /* Creamos los Jugadores a partir de un Archivo       */
    
    repartirFichas();   /* Creamos y repartimos las Fichas a Cada Jugador     */
    /* En teoría aquí empiezan los hilos */
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
                jugadores[i].mazo[j] = listaMazoTotal[0]; /* Asignamos la Ficha al Mazo del Jugador */
                delElement(listaMazoTotal, 0);            /* Eliminamos la Ficha de la Lista        */
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
        delElement (listaFichasParaComer, 0);
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

/************************************* EXTRA *************************************/
// Funcion que realiza una pausa en la Terminal:
void sysPause() {
    /********************************************
        Esta funcion se utiliza para realizar
        una pausa en la terminal con el fin de
        poder ver mensajes y demás información
        que se vaya a mostrar por pantalla.
        
        **Esta funcion se creó como alternativa
        al system("pause") que existe en Windows.
    *********************************************/
    printf ("Press Enter to continue...");
    int c = getchar(); /* Simulamos la pausa */
    getchar();
}

void prueba () {
    iniciarPartida(NEW, 2);

    mesa = (Mesa*) calloc (sizeof(Mesa), 1);

    int posicion = -1, direccion = 0, cruzado = 0, puntos = 0;

    system ("clear");
    printf ("Mesa Vacia\n\n");
    Mostrar_Nodos (mesa);

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

    for (int i = 0; i < 3; i++) {
        if (mesa->raiz == NULL) {
            int pos = -1;
            for (int i = 0; i < jugadores[0].canMazoJug; i++) {
                if (jugadores[0].mazo[i].valores[0] == jugadores[0].mazo[i].valores[1]) {
                    pos = i;
                    break;
                }
            }
            if (pos == -1) { exit(1); }
            
            AgregarNodoArbol (mesa, &jugadores[0].mazo[pos], NULL, 0);

            delElement (jugadores[0].mazo, pos);

        } else {
            Lista *lista = Fichas_Libres(mesa);
            Nodo *destino = Comparando_Lista (lista, jugadores[0].mazo, jugadores[0].canMazoJug, &posicion, &direccion, &cruzado, &puntos);
            AgregarNodoArbol(mesa, &jugadores[0].mazo[posicion], destino, direccion);
            Mostrar_Lista (lista);
            Liberar_Lista(lista);
            delElement (jugadores[0].mazo, posicion);
        }
        printf ("Mesa Con Ficha\n\n");
    }

    printf ("Mesa Con Ficha\n\n");
    Mostrar_Nodos (mesa);

    sysPause();
}

#endif