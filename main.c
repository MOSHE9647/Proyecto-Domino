#include "Isaac/src/partida.h"

/************************************************************
    ARCHIVO MAIN DEL JUEGO, AQUÍ SOLO APARECE EL MENU DONDE
    SE VA A LLAMAR A CADA FUNCION SEGÚN SEA EL CASO
    
    *** CTRL + Click sobre la funcion para ir al Archivo 
        donde se encuentra la misma.
*************************************************************/

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

int main () {
    int opc = 0;
    do {
        system ("clear");
        printf ("\n");
        printf ("\t      ╔══════════════╗\n");
        printf ("\t╔═════╣ JUEGO DOMINO ╠═════╗\n");
        printf ("\t║     ╚══════════════╝     ║\n");
        printf ("\t║     1. Nuevo Juego       ║\n");
        printf ("\t║     2. Continuar         ║\n");
        printf ("\t║     3. Puntuaciones      ║\n");
        printf ("\t║     4. Salir             ║\n");
        printf ("\t╚══════════════════════════╝\n");
        printf ("\t    Digite una Opción: ");
        scanf  ("%i", &opc);

        switch (opc) {
            case 1: {
                opc = 0;
                system ("clear");
                printf ("\n");
                printf ("\t      ╔═══════════════╗\n");
                printf ("\t╔═════╣  NUEVO JUEGO  ╠═════╗\n");
                printf ("\t║     ╚═══════════════╝     ║\n");
                printf ("\t║        2 Jugadores        ║\n");
                printf ("\t║        3 Jugadores        ║\n");
                printf ("\t║        4 Jugadores        ║\n");
                printf ("\t║        5 Jugadores        ║\n");
                printf ("\t║        6 Jugadores        ║\n");
                printf ("\t║        7 Jugadores        ║\n");
                printf ("\t╚═══════════════════════════╝\n");
                printf ("\t Digite una Opción [2-7]: ");
                scanf  ("%i", &opc); system ("clear");
                iniciarPartida(NEW, opc);
                //imprimir ();/**/
                sysPause();/**/
                break;
            }
            case 2: {
                system ("clear");
                iniciarPartida(OLD, 0);
                imprimir();/**/
                sysPause();/**/
                break;
            }
            case 3: {
                //prueba ();
                break;
            }
            case 4: {
                return 0;
                break;
            }
            default: {
                printf ("\t    Opción Inválida!!\n\n");
                sysPause();
                break;
            }
        }
    } while (opc != 4);
    return EXIT_FAILURE;
}