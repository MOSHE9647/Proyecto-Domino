/*
    Archivo de Trabajo del Proyecto. Aquí vamos a unir todo lo que hayamos hecho del proyecto
    Compilar este archivo con el siguiente comando: 
    gcc -o Proyecto main.c --> Esto para tener un orden al momento de crear los ejecutables
    ./Proyecto             --> Comando para ejecutar el programa
*/

#include <stdio.h>        /* Entrada y Salida Estándar */
#include <string.h>       /* Para usar 'strncpy'       */
#include <stdlib.h>       /* Librería Estándar         */
#include <stdbool.h>      /* Para el uso de Booleanos  */
#include <unistd.h>
#include <time.h>         /* Para números aleatorios   */

#define ARCHIVO_TXT "./log.txt"
#define CHAR_LIMIT 1024   /* Límite de Carácteres para los Nombres y Lectura de Archivos */
#define MAX_PLAYERS 7     /* Cantidad Maxima de Jugadores que admite el Juego            */
#define DOMINO 28         /* Cantidad máxima de fichas que posee el juego                */

/* 
    Si les marca error con las variables o funciones de tipo 'bool',
    eliminen la librería '<stdbool.h>' y descomenten los siguientes #define,
    luego cambien el tipo 'bool' de las funciones por el tipo 'int'
*/

// #define true 1         
// #define false 0

// Estructura para las Fichas:
typedef struct {
    int valores[2]; /* Cada número que posee la ficha [a|b] */
    int numFicha    /* Variable para conocer la posicion y reordenar las fichas */
} Ficha;

// Estructura para crear a los jugadores:
typedef struct {
    /* 
        Estas variables hay que cambiarlas por 
        las variables que pide el Proyecto    
    */
    char nombre[CHAR_LIMIT];    
    int edad;
    int ID;
} Jugador;

// Variables Globales:
Jugador jugadores[MAX_PLAYERS]; /* Vector de Jugadores                                          */
Ficha *fichas = NULL;           /* Vector Dinámico de Fichas                                    */
int posFicha = 1;               /* Variable para reordenar las fichas con el método de Burbuja  */
int canJug = 0;                 /* Variable para almacenar la cantidad de jugadores por partida */

// Declaración de las funciones a utilizar dentro del Código:
void iniciarJuego();                        /* Funcion donde se solicitan los datos iniciales   */
Ficha *crearFicha (int a, int b);           /* Funcion que crea las fichas al iniciar el juego  */
Jugador *crearJugador (Jugador *j);         /* Funcion que crea a los Jugadores                 */
void imprimir(Jugador *j, int i);           /* Funcion para mostrar la información del Jugador  */
void escribir(Jugador *j);                  /* Funcion para escribir en un archivo txt          */
void leer ();                     /* Funcion para leer de un archivo txt              */
void revolver(Ficha *fichas, int size);     /* Funcion que revuelve todas las fichas            */
void ordenar(Ficha *fichas, int longitud);  /* Funcion para ordenar las fichas del juego y maso */
void systemPause();                         /* Funcion para pausar la pantalla                  */

/* Inico: Funcion Principal del Programa */
int main () {
    int opc = 0;
	do {
		printf ("\n\t╔════════╣ JUEGO DOMINO ╠════════╗\n");
		printf ("\t║                                ║\n");
		printf ("\t║         1. Juego Nuevo         ║\n");
		printf ("\t║         2. Puntuaciones        ║\n");
		printf ("\t║         3. Salir               ║\n");
		printf ("\t║                                ║\n");
		printf ("\t╚════════════════════════════════╝\n");
		printf ("\t       Digite una Opcion: ");
		scanf ("%d", &opc);

		switch (opc) {
			case 1:
				iniciarJuego();
                break;
            case 2:
                leer();
                systemPause();
                break;
            case 3:
                return 0;
                break;
            default:
                system("clear");
                printf ("\tOpcion Invalida...\n");
                printf ("\tDigite una Opción Válida.\n\n");
                break;
		}
        system("clear");
	} while (opc != 3);

    return 0;
}
/* Fin: Funcion Principal del Programa */

/* Aquí creamos las Funciones que vamos a utilizar dentro del Código */
// Creamos las Fichas:
Ficha *crearFicha (int a, int b) {
    Ficha *nueva = calloc(sizeof(Ficha), 1); /* Variable auxiliar para crear las fichas */
    nueva->valores[0] = a;                   /* Asignamos 'a'                           */
    nueva->valores[1] = b;                   /* Asignamos 'b'                           */
    nueva->numFicha = posFicha;              /* Le damos un Número a la Ficha           */
    posFicha++;                              /* Aumentamos ese numero                   */
    return nueva;                            /* Retornamos la Nueva Ficha               */
}

// Creamos a los Jugadores:
Jugador *crearJugador(Jugador *j) {
    /* 
        Estas variables hay que cambiarlas por 
        las variables que pide el Proyecto:
    */
    char nom[CHAR_LIMIT];
    int edad = 0, ID = 0;

    // Solicitamos los Datos al Usuario y Asignamos las Variables:
    printf ("Digite su Nombre: ");
    scanf ("%s", j->nombre);
    printf ("Digite su Edad: ");
    scanf ("%d", &j->edad);
    printf ("Digite su ID: ");
    scanf ("%d", &j->ID);    
}

void iniciarJuego() {
    // Creamos las Fichas para el Juego:
    Ficha *temp;        /* Variable temporal para crear las fichas del Juego */
    int contador = 0;   /* Contador para la cantidad de Fichas creadas       */

    for (int i = 0; i <= 6; i++) {
        for (int j = 0; j <= 6; j++) {
            if (j >= i) {
                /* Le asignamos la memoria al Vector Dinámico: */
                fichas = realloc(fichas, (contador + 1) * sizeof(Ficha));
                temp = crearFicha(i, j);                        /* Creamos la ficha        */
                memcpy(&fichas[contador], temp, sizeof(Ficha)); /* La ponemos en el Vector */
                free(temp);                                     /* Liberamos la memoria    */
                contador++;                                     /* Aumentamos el contador  */
            }
        }
    }

    // Solicitamos la Cantidad de Jugadores:
    printf ("Digite el Número de Jugadores: ");
    scanf ("%d", &canJug);

    // Solicitamos los Datos y creamos a los Jugadores:
    for (int i = 0; i < canJug; i++) {
        system ("clear"); /* Limpia Pantalla */
        printf ("Datos del Jugador %d:\n\n", i+1);
        crearJugador(&jugadores[i]);
    }
}

void imprimir(Jugador *j, int i) {
    /* Esta información también hay que cambiarla */
    // Mostramos los datos del Jugador correpondiente:
    printf ("Datos del Jugador %d:\n", i+1);
    printf ("Nombre:\t%s\n", j->nombre);
    printf ("Edad:\t%d\n", j->edad);
    printf ("ID:\t%d\n\n", j->ID);
}

void escribir (Jugador *j) {
    FILE* archivo;      /* Variable que apunta al Archivo que vamos a utilizar */
    /* 
        Las siguientes variables hay que cambiarlas por 
        las variables que pide el Proyecto:
    */
	char Edad[CHAR_LIMIT];  /* Variable para almacenar la edad en formato string   */
	char ID[CHAR_LIMIT];    /* Variable para almacenar la ID en formato string     */

	archivo = fopen(ARCHIVO_TXT, "a"); /* Abrimos el archivo en modo escritura sin sobreescribir */

    // Verificamos que se haya leído el archivo:
	if (archivo == NULL) {
		printf("Error al abrir el archivo.");
        return;                       /* No se leyó correctamente */
	} else {
		sprintf (Edad, "%d", j[0].edad);    /* Convertimos edad de 'int' a 'string' */
		sprintf (ID, "%d", j[0].ID);        /* Convertimos ID de 'int' a 'string'   */
        
        /* Escribimos la información de las variables en el archivo */
		fputs (j->nombre, archivo); fputs ("\n", archivo);
		fputs (Edad, archivo);      fputs ("\n", archivo);
		fputs (ID, archivo);        fputs ("\n", archivo);
	}

	fclose (archivo);                       /* Cerramos el archivo   */
}

/* No sé si esta función sea necesaria */
void leer () {
	FILE *archivo;                   /* Variable que apunta al Archivo que vamos a utilizar */
	archivo = fopen(ARCHIVO_TXT, "r"); /* Abrimos el archivo en Modo Lectura */
	
    char nombre[CHAR_LIMIT];         /* Variable que almacena el nombre en formato string */
	int edad;
	int ID;

    // Verificamos que se haya leído el archivo:
	if (archivo == NULL) {
		/* Mostramos un mensaje de Error: */
        system ("clear");
		printf("Error al abrir el archivo.\n");
        printf("Revise el nombre del archivo e intentelo nuevamente.\n\n");
		return;  /* No se leyó correctamente */
	}
    /* 
        Leemos el archivo y almacenamos lo leído en sus
        respectivas variables: 
    */
	while (!feof(archivo)) {
        fscanf (archivo, "%s %d %d", nombre, &edad, &ID);
    }

    /* Descomenten esto para probar si funciona: */
	//printf ("Nombre:\t%sEdad:\t%d\nID:\t%d", j->nombre, j->edad, j->ID);
    printf ("Nombre:\t%s\nEdad:\t%d\nID:\t%d\n\n", nombre, edad, ID);
	fclose(archivo);    /* Cerramos el archivo   */
}

void revolver (Ficha *fichas, int size) {
    /*
        Revolvemos las fichas intercambiandolas de lugar
        de forma aleatoria utilizando la funcion 'rand()'
    */
    srand(time(NULL));  /* Semilla para los números aleatorios */
    for (int i = 0; i < size; i++) {
        /* Realizamos el Intercambio */
        int j = rand() % size;  /* Variable con las posiciones a intercambiar  */
        Ficha temp = fichas[i]; /* Variable auxiliar para realizar el cambio   */
        fichas[i] = fichas[j];
        fichas[j] = temp;
    }
}

void ordenar (Ficha *fichas, int longitud) {
    /* Ordenamiento por Método de la Burbuja */
    for (int i = 0; i < longitud; i++) {
        for (int actual = 0; actual < longitud - 1; actual++) {
            int siguiente = actual + 1;
            /*
                Si el actual es mayor que el que le sigue a la derecha intercambiamos, es decir,
                movemos el actual a la derecha y el de la derecha al actual:
            */
            if (fichas[actual].numFicha > fichas[siguiente].numFicha) {
                Ficha temporal = fichas[actual];
                fichas[actual] = fichas[siguiente];
                fichas[siguiente] = temporal;
            }
        }
    }
}

void systemPause() {
    printf ("Press any key to continue...");
    int c = getchar();
    getchar();
}