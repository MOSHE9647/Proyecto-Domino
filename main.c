#include "src/partida.h"

/************************************************************
    ARCHIVO MAIN DEL JUEGO, AQUÍ SOLO APARECE EL MENU DONDE
    SE VA A LLAMAR A CADA FUNCION SEGÚN SEA EL CASO
    
    *** CTRL + Click sobre la funcion para ir al Archivo 
        donde se encuentra la misma.
*************************************************************/

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
        scanf  ("%i", &opc); system ("clear");

        switch (opc) {
            case 1: {
                opc = 0;
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
                break;
            }
            case 2: {
                printf ("Iniciando Partida desde Archivo 'log.txt'.\n");
                sleep(1); system("clear");
                printf ("Iniciando Partida desde Archivo 'log.txt'..\n");
                sleep(1); system("clear");
                printf ("Iniciando Partida desde Archivo 'log.txt'...\n");
                sleep(1); system("clear");
                printf ("Iniciando Partida desde Archivo 'log.txt'....\n");
                sleep(1); system("clear");
                iniciarPartida(OLD, 0);
                break;
            }
            case 3: {
                puntuaciones();
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