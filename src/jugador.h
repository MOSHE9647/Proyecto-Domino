#ifndef JUGADOR_H
#define JUGADOR_H

/************************************************************
    ARCHIVO DE CABECERA DONDE SE ENCUENTRAN LA ESTRUCTURA,
    FUNCIONES O MÉTODOS RELACIONADOS A LOS JUGADORES
*************************************************************/

#include "ficha.h"          /* Archivo de Cabecera de Fichas    */
#include <string.h>         /* Para el uso de 'strcpy()'        */

#define ARCHIVO "log.txt"   /* Ubicación del Registro del Programa     */
#define CHAR_LIMIT 1024     /* Límite de carácteres para nombres       */
#define MAX_PLAYERS 7       /* Número Máximo de Jugadores por partida  */
#define FALSE 0             /* Creamos el tipo Booleano False = 0      */
#define TRUE 1              /* Creamos el tipo Booleano True = 1       */
#define NEW 1               /* Para Definir si es una Nueva Partida    */
#define OLD 0               /* Para Definir si se Continúa una Partida */

/* ESTRUCTURA DE JUGADOR */
typedef struct {
    Ficha mazo[MAX_TILES];  /* Vector del Mazo para las Fichas del Jugador          */
    char nom[CHAR_LIMIT];   /* Variable que guarda el Nombre del Jugador            */
    int totalGanados;       /* Cantidad de Juegos Ganados que lleva cada Jugador    */
    int totalPuntos;        /* Cantidad total de puntos que posee cada Jugador      */
    int canMazoJug;         /* Cantidad de Fichas que posee cada Jugador en el Mazo */
    int puntos;             /* Cantidad de puntos que lleva el Jugador por partida  */
    int turno;
} Jugador;

/* VARIABLES GLOBALES */
Jugador jugadores[MAX_PLAYERS]; /* Lista de Jugadores por partida           */
int canFichasJug = 0;           /* Cantidad de Fichas que hay por Jugador   */
int canJug = 0;                 /* Cantidad de Jugadores por partida        */

/* LISTA DE FUNCIONES A UTILIZAR DENTRO DEL JUEGO */
// ** CTRL + Click para ir a la Funcion
void crearJugadores (int type); /* Función para Crear a cada Jugador               */
int verificarDobles ();         /* Verifica si Existen más de 4 Dobles por Jugador */
void sysPause();                         /* Funcion que realiza una pausa en la Terminal      */

/*********************************** FUNCIONES ***********************************/
// Función para Crear a los Jugadores:
void crearJugadores (int type) {
    /* CREAMOS A LOS JUGADORES */
    if (type == OLD) {
        FILE *archivo;                 /* Puntero al Archivo que se va a leer */
	    archivo = fopen(ARCHIVO, "r"); /* Abrimos el archivo en Modo Lectura  */

        /* VERIFICAMOS QUE EXISTA EL ARCHIVO */
        if (archivo == NULL) {
            /* Mostramos un mensaje de Error: */
            system ("clear"); /* Limpiamos Pantalla */
            printf("Error al abrir el archivo.\n");
            printf("Revise el nombre del archivo e intentelo nuevamente.\n\n");
            exit (1);         /* No se leyó correctamente */
        }

        /* LEEMOS LA INFORMACION DEL ARCHIVO */
        while (!feof(archivo)) {
            /* Sintaxis: fscanf (*archivo, "tipo_de_dato_a_leer", donde_se_guarda) */
            char nombre[CHAR_LIMIT] = "";
            int Puntos = 0;
            int TotalPts = 0;
            int Ganados = 0;
            fscanf (archivo, "%s %d %d %d", nombre, &Puntos, &TotalPts, &Ganados);
            if (nombre[0] != '\0') {
                strcpy(jugadores[canJug].nom, nombre);
                jugadores[canJug].puntos = Puntos;
                jugadores[canJug].totalPuntos = TotalPts;
                jugadores[canJug].totalGanados = Ganados;
                canJug++; /* Se creó un Jugador Nuevo */
            }
        }

        /* CERRAMOS EL ARCHIVO */
        fclose(archivo);
    } else {
        for (int i = 0; i < canJug; i++) {
            system ("clear"); /* Limpiamos la Pantalla del Terminal */
            /* SOLICITAMOS EL NOMBRE DE CADA JUGADOR */
            printf ("Digite el nombre del Jugador %i\n-> ", i + 1);
            scanf ("%s", jugadores[i].nom);
        }
    }
    //srand (time(NULL));
    for (int i = 0; i < canJug; i++) {
        //int turno = rand() % canJug;
        jugadores[i].turno = i;
        system("clear");
    }
}

// Función para Verficiar que no Existan Más de 4 Dobles:
int verificarDobles () {
    /******************************************************
        Recorremos el mazo de cada jugador buscando a ver
        si existe alguna ficha doble [6|6], [5|5], etc...
        Si existe, aumentamos el contador 'dobles'.
        Si al terminar de recorrer el mazo de un jugador,
        la cantidad de dobles es mayor o igual a 4, se 
        devuelve TRUE, de lo contrario se devuelve FALSE
    *******************************************************/
    for (int i = 0; i < canJug; i++) {
        int dobles = 0;
        for (int j = 0; j < jugadores[i].canMazoJug; j++) {
            if (jugadores[i].mazo[j].valores[0] == jugadores[i].mazo[j].valores[1]) {
                dobles++;
            }
        }
        if (dobles >= 4) { return TRUE; }
    }
    return FALSE;
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

#endif