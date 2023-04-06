#include <string.h>         /* Para uso de la función 'strcpy' */
#include <stdlib.h>         /* Para uso de Memoria Dinámica    */
#include <unistd.h>         /* Para funciones propias de Linux */
#include <stdio.h>          /* Entrada y Salida Estándar de C  */
#include <time.h>           /* Para uso de Números Aleatorios  */


#define ARCHIVO "log.txt"   /* Ubicación del Registro del Programa    */
#define CHAR_LIMIT 1024     /* Límite de carácteres para nombres      */
#define MAX_PLAYERS 7       /* Número Máximo de Jugadores por partida */
#define MAX_COMER 10        /* Tamaño máximo de las Fichas para Comer */
#define MAX_TILES 9         /* Cantidad máxima de Fichas por Jugador  */
#define DOMINO 28           /* Cantidad de Fichas que posee el Juego  */
#define FALSE 0             /* Creamos el tipo Booleano False = 0     */
#define TRUE 1              /* Creamos el tipo Booleano True = 1      */ 

typedef struct Nodo Nodo;
typedef struct Lista Lista;
typedef struct Mesa Mesa;

/* ESTRUCTURA DE FICHA */
typedef struct {
    int valores[2];         /* Valores que tiene la Ficha ( [Izq|Der] )     */
    int salida;             /* Variable para obtener la 'punta' de la Ficha */
    int numFicha;           /* Variable para el ordenamiento de las fichas  */
} Ficha;

/* ESTRUCTURA DE JUGADOR */
typedef struct {
    char nom[CHAR_LIMIT];   /* Variable que guarda el Nombre del Jugador           */
    Ficha mazo[MAX_TILES];  /* Vector del Mazo para las Fichas del Jugador         */
    int totalGanados;       /* Cantidad de Juegos Ganados que lleva cada Jugador   */
    int totalPuntos;        /* Cantidad total de puntos que posee cada Jugador     */
    int puntos;             /* Cantidad de puntos que lleva el Jugador por partida */
} Jugador;

/** ESTRUCTURA NODO **/
struct Nodo{
	Ficha* dato;            /* Guarda una referencia a una ficha                                            */
	Nodo* anterior;         /* Guarda referencia del Nodo,"Ficha", que estaba libre anterios                */
    Nodo *arriba;           /* Guarda referencia del Nodo, colocado arriba, solo se usa en caso de ser doble*/
    Nodo *abajo;            /* Guarda referencia del Nodo, colocado abajo, solo se usa en caso de ser doble */
    Nodo *siguiente;        /* Guarda referencia del Nodo, hacia delante                                    */
    Nodo *sig_auxiliar;     /* Esto guarda solo una referencia temporal, solo para la lista de salidas      */
	int cruzado;            /* Nos dice esta colocada vertical o no                                         */	
};

/** ESTRUCTURA LISTA **/
struct Lista{
	Nodo *primero;          /* Guarda referencia el primer Nodo agregado a lista                            */
    Nodo *ultimo;           /* Guarda referencia al ultimo Nodo agregaddo a la lista                        */
};
/** ESTRUCTURA MESA **/
struct Mesa{
	Nodo *raiz;             /* Mantiene la referencia de la ficha inicia osea la primera colocada           */
};
/* VARIABLES GLOBALES */
Ficha listaFichasParaComer[MAX_COMER];  /* Lista de las Fichas para Comer           */
Jugador jugadores[MAX_PLAYERS];         /* Lista de Jugadores por partida           */
Ficha listaMazoTotal[DOMINO];           /* Lista de todas las Fichas del Juego      */
int totalFichas = DOMINO;               /* Para Manejo de Vectores en el Juego      */
int canFichasJug = 0;                   /* Cantidad de Fichas que hay por Jugador   */
int canMazoJug = 0;                     /* Cantidad de Fichas para cada Jugador     */
int canJug = 0;                         /* Cantidad de Jugadores por partida        */

/* LISTA DE FUNCIONES A UTILIZAR DENTRO DEL JUEGO */
void revolverFichas (Ficha f[], int size);  /* Función para Revolver una Lista de Fichas       */
void ordenarFichas (Ficha f[], int size);   /* Función para Ordenar una Lista de Fichas        */
void delElement (Ficha f[], int pos);       /* Función para Borrar Elementos de una Lista      */
void inicializarFichas ();                  /* Inicializa las Variables de 'listaMazoTotal'    */
void repartirFichas ();                     /* Función que Reparte Fichas a cada Jugador       */
void crearJugadores ();                     /* Función para Crear a cada Jugador               */
int verificarDobles ();                     /* Verifica si Existen más de 4 Dobles por Jugador */

/* METODOS DEL ARBOL  Linea 241 - 370 456 */
void AgregarNodoArbol(Mesa* mesa, Ficha* domino, Nodo *destino, int direccion);
    /*Estos metodos son los utilizados por AgregarNodoArbol por lo que son internos a este mismo */  
    Nodo* CreandoNodo(Ficha *domino);
    void determinando_salida(Nodo *actual, Nodo *nuevo);
    void Guardando_Nodo(Nodo *actual, Nodo* nuevo, int direccion);
    void asignacion_recursivo(Nodo *actual, Nodo* nuevo, Nodo *destino, int direccion);
/* estos metodos son solo de prueba */
void muestra_Recursivo(Nodo *actual);
void Mostrar_Nodos(Mesa *mesa);

/* METODOS LISTAS     Linea 370 - 456 */
Lista *Fichas_Libres(Mesa *mesa);
    /*Estos metodos son funciones usadas internamente por el metodo Fichas_Libres */
    void ingresar_Lista(Lista *lista, Nodo* nodo);
    void Buscando_fichas_disponibles(Lista *lista, Nodo *actual);/* Metodo recursivo */

void Liberar_Lista(Lista *lista);/* Liberacion del Nodo *nodo->sig_auxiliar*/
void Mostrar_Lista(Lista *l);

/* FUNCION DE PRUEBA */
void imprimir();

/* FUNCIÓN MAIN */
int main () {

    repartirFichas ();
    imprimir ();
    
    // for (int i = 0; i < DOMINO; i++) {
    //     printf ("#%i:\t[%i|%i]\n", i + 1, listaMazoTotal[i].valores[0], listaMazoTotal[i].valores[1]);
    // }
    return 0;
}

/* DESARROLLO DE FUNCIONES */
// Función para Repartir Fichas:
void repartirFichas () {
    /* PEDIMOS CANTIDAD DE JUGADORES Y LOS CREAMOS */
    // ** CTRL + Click para ir a la función ** //
    crearJugadores ();
    
    /* DIVIDIMOS LA CANTIDAD DE FICHAS */
    canFichasJug = DOMINO / (canJug + 1);           /* Cantidad de Fichas a Repartir */

    /* REVOLVEMOS LAS FICHAS Y LAS REPARTIMOS */
    do {
        totalFichas = DOMINO;
        inicializarFichas ();
        revolverFichas (listaMazoTotal, DOMINO);
        for (int i = 0; i < canJug; i++) {
            for (int j = 0; j < canFichasJug; j++) {
                jugadores[i].mazo[j] = listaMazoTotal[0];
                delElement(listaMazoTotal, 0);
            }
            ordenarFichas (jugadores[i].mazo, canFichasJug);
        }
    } while (verificarDobles () == TRUE);
    /* ASIGNAMOS EL RESTO DE FICHAS A LA LISTA 'listaFichasParaComer' */
    for (int i = 0; i < totalFichas; i++) { listaFichasParaComer[i] = listaMazoTotal[i]; }
    ordenarFichas (listaFichasParaComer, totalFichas);
}

// Función para Inicializar las Fichas:
void inicializarFichas () {
    int numFicha = 0;
    for (int i = 0; i <= 6; i++) {
        for (int j = i; j <= 6 ; j++) {
            listaMazoTotal[numFicha].numFicha = numFicha + 1;
            listaMazoTotal[numFicha].valores[0] = i;
            listaMazoTotal[numFicha].valores[1] = j;
            listaMazoTotal[numFicha].salida = 0;
            numFicha ++;
        }
    }
}

// Función para Crear a los Jugadores:
void crearJugadores () {
    //AQUÍ HAY QUE VERIFICAR 'log.txt'
    
    /* SOLICITAMOS LA CANTIDAD DE JUGADORES */
    printf ("Digite la Cantidad de Jugadores\n-> ");
    scanf ("%i", &canJug);

    /* CREAMOS A LOS JUGADORES */
    for (int i = 0; i < canJug; i++) {
        system ("clear");           /* Limpiamos la Pantalla del Terminal  */

        /* SOLICITAMOS EL NOMBRE DE CADA JUGADOR */
        printf ("Digite el nombre del Jugador %i\n-> ", i + 1);
        scanf ("%s", jugadores[i].nom);
    }
}

// Función para Revolver las Fichas:
void revolverFichas (Ficha f[], int size) {
    /*******************************************************
        Revolvemos las fichas intercambiandolas de lugar
        de forma aleatoria utilizando la funcion 'rand()'
    ********************************************************/
    srand(time(NULL)); // <- SEMILLA
    for (int i = 0; i < size; i++) {
        int aux = rand () % size;       /* Auxiliar para tener una posición aleatoria     */
        Ficha temp = f[i];              /* Auxiliar Temporal para Realizar el Intercambio */
        // INTERCAMBIAMOS POSICIONES:
        f[i] = f[aux];
        f[aux] = temp;
    }
}

// Función para Ordenar las Fichas:
void ordenarFichas (Ficha f[], int size) {
    /* ORDENAMOS CON EL MÉTODO DE LA BURBUJA */
    for (int i = 0; i < size; i++) {
        for (int actual = 0; actual < size - 1; actual++) {
            int sig = actual + 1;
            /************************************************************************
                Si el 'actual' es mayor que 'siguiente', intercambiamos. Es decir,
                movemos el actual a la derecha y el de la derecha al actual:
            *************************************************************************/
            if (f[actual].numFicha > f[sig].numFicha) {
                // INTERCAMBIAMOS POSICIONES:
                Ficha temp = f[actual];
                f[actual] = f[sig];
                f[sig] = temp;
            }
        }
    }
}

// Función para Eliminar Elementos de un Vector:
void delElement (Ficha f[], int pos) {
    for (int i = pos; i < totalFichas; i++) {
        f[i] = f[i + 1];
    }
    totalFichas--;
    // printf ("totalFichas = \t%i\n", totalFichas);
}

// Función para Verficiar que no Existan Dobles:
int verificarDobles () {
    for (int i = 0; i < canJug; i++) {
        int dobles = 0;
        for (int j = 0; j < canFichasJug; j++) {
            if (jugadores[i].mazo[j].valores[0] == jugadores[i].mazo[j].valores[1]) {
                dobles++;
            }
        }
        if (dobles >= 4) { return TRUE; }
    }
    return FALSE;
}

/* FUNCIONES PARA PROBAR EL PROGRAMA */
void imprimir() {
    // Mostramos los datos del Jugador correpondiente:
    for (int i = 0; i < canJug; i++) {
        printf ("Datos del Jugador %d:\n", i+1);
        printf ("Nombre:\t%s\n", jugadores[i].nom);
        printf ("Fichas:\n");
        for (int j = 0; j < canFichasJug; j++) {
            printf ("\t#%i =\t[%i|%i]\n", j + 1, jugadores[i].mazo[j].valores[0], jugadores[i].mazo[j].valores[1]);
        }
        printf ("\n\n");
    }
}
/* AQUI ESTAN LOS METODOS DEL ARBOL Y LAS LISTA ENTRE OTROS 
 * CODIGO DE GONZALO EL CRACK
 */
/*-----ESTOS METODOS SON PARA EL AGREGACION DE NODOS AL ARBOL------*/
/*Crea nodos recibbiendo una ficha*/
Nodo* CreandoNodo(Ficha *domino){
	Nodo *nuevo = (Nodo *)calloc(sizeof(Nodo),1);
	nuevo->dato = domino;
	return nuevo;
}
/**
 * Determina cual lado de la ficha queda lire para seguir colocando
 * **/
void determinando_salida(Nodo *actual, Nodo *nuevo){
	int salida = actual->dato->salida;
	if(actual->dato->valores[salida] == nuevo->dato->valores[0]){
        nuevo->dato->salida = 1;
	}else if(actual->dato->valores[salida] == nuevo->dato->valores[1]){
		nuevo->dato->salida = 0;
	}
}
/**
 * Se encarga de guardar el nuevo nodo 
 * en la direccion deseada
 * asi mismo llamando el metodo determinar_salida
 * asi mismo se encarga de que de saber si una ficha doble esta cruzada o similar al restro
 * **/
void Guardando_Nodo(Nodo *actual, Nodo* nuevo, int direccion){
	if(actual != NULL){/*evitar posible error*/
		if(actual->dato->valores[0] != actual->dato->valores[1]){
			if(actual->siguiente == NULL){
				determinando_salida(actual, nuevo);
				nuevo->anterior = actual;
				actual->siguiente = nuevo;
			}
		}else if(actual->dato->valores[0] == actual->dato->valores[1] && actual->cruzado == 0){
			if(actual->arriba == NULL && direccion == 1){
				determinando_salida(actual, nuevo);
				nuevo->anterior = actual;
				actual->arriba = nuevo;
			
			}else if(actual->siguiente == NULL && direccion == 2){
				determinando_salida(actual, nuevo);
				nuevo->anterior = actual;
				actual->siguiente = nuevo;

			}else if(actual->abajo == NULL && direccion == 3){
				determinando_salida(actual, nuevo);
				nuevo->anterior = actual;
				actual->abajo = nuevo;

			}else if(actual->anterior == NULL && direccion == 0){
				determinando_salida(actual, nuevo);
				nuevo->anterior = actual;
				actual->anterior = nuevo;

			}
		}else{
			determinando_salida(actual, nuevo);
			nuevo->anterior = actual;
			actual->siguiente = nuevo;
		}
	}
}
/**
 * Metodo recursivo encargado de recorrer las fichas de mesa para asignar nueva ficha
 * recive el nodo actua el cual es el nodo por el que se esta revisando
 * el nodo destino el cual es el en donde se colocara la ficha
 * y direccio explicado mas adelante
 * **/
void asignacion_recursivo(Nodo *actual, Nodo* nuevo, Nodo *destino, int direccion){
	if(actual != NULL){/* Corte de la recursividad */
		if(actual == destino){
            /*Guarda el nodo nuevo en caso de que actual sea el nodo buscado ose el mismo nodo destino*/
			Guardando_Nodo(actual, nuevo, direccion);
	    }else{
            /*Llamando al mismo metodo asignacion_recursivo */
            /*Condicional para realizar busqueda de todos los lados en caso de ficha par*/
		    if(actual->dato->valores[0] == actual->dato->valores[1]){
			    asignacion_recursivo(actual->arriba, nuevo, destino, direccion);
			    asignacion_recursivo(actual->abajo, nuevo, destino, direccion);
		    }
		    asignacion_recursivo(actual->siguiente, nuevo, destino, direccion);
        }
	}
}
/* Este metodo es el que se encarga de la ejecucion del proceso guardar
*  Mesa *mesa;      Es el arbol osea las fichas de la mesa
*  Ficha *domio;    Ficha elegida por el jugador para ser colocada en la mesa
*  Nodo *destino;   Ficha de la mesa a la cual se le colocar una ficha siguente
*  int direccion;   Esto en caso de colocar ficha en una ficha destino doble 
*                   1 arriba
*                   2 siguiente
*                   3 abajo
*                   0 anterior   ""esto solo si es en nodo raiz, mejorara mas adelante
*/
void AgregarNodoArbol(Mesa* mesa, Ficha* domino, Nodo *destino, int direccion){
	Nodo *nuevo = CreandoNodo(domino);/*crea el nodo apartir del la ficha recibida*/
 	if(mesa->raiz == NULL){/* Colocasion primera ficha*/
		mesa->raiz = nuevo;
		mesa->raiz->dato->salida = 0;
	}else if(mesa->raiz == destino){/*cololoca en caso de que se desea colocar al rededos de la ficha raiz*/
		Guardando_Nodo(mesa->raiz, nuevo, direccion);
	}else{
        /* llamando los metodos recursivos para recorrer el arbol */
      	asignacion_recursivo(mesa->raiz->anterior, nuevo, destino, direccion);
		asignacion_recursivo(mesa->raiz, nuevo, destino, direccion);
	}
}	

/* Aquie en  adelante van los metodos de mostreo
 * equis de
 */
void muestra_Recursivo(Nodo *actual){
   if(actual != NULL){
      printf("[ %d | %d ]\n",actual->dato->valores[0],actual->dato->valores[1]);
      muestra_Recursivo(actual->siguiente);
      muestra_Recursivo(actual->arriba);
      muestra_Recursivo(actual->abajo);
   }
}

void Mostrar_Nodos(Mesa *mesa){
   if(mesa != NULL){
		muestra_Recursivo(mesa->raiz->anterior);
    	muestra_Recursivo(mesa->raiz);
   }
}

/*----ESTOS METODOS SON DE LA LISTA DE NODOS DIPONIBLES DEL ARBOL*/
/* Ingresa nodos fichas a la lista de una manera ordenada */
void ingresar_Lista(Lista *lista, Nodo* nodo){
	if(lista->primero == NULL){
		lista->primero = nodo;
		lista->ultimo = nodo; 
	}else{
		if(lista->primero->dato->valores[lista->primero->dato->salida] >= nodo->dato->valores[nodo->dato->salida]){
			nodo->sig_auxiliar = lista->primero;
			lista->primero = nodo;
		}else if(lista->ultimo->dato->valores[lista->primero->dato->salida] <= nodo->dato->valores[nodo->dato->salida]){
			lista->ultimo->sig_auxiliar = nodo;
			lista->ultimo = nodo;
		}else{
			Nodo *actual = lista->primero;
            int salida = nodo->dato->salida;
			while (actual != NULL){
                int auxiliar = actual->dato->salida;
				if(nodo->dato->valores[salida] <= actual->sig_auxiliar->dato->valores[auxiliar]){
                    nodo->sig_auxiliar = actual->sig_auxiliar;
					actual->sig_auxiliar = nodo;
                    actual = lista->ultimo;
				}
				actual = actual->sig_auxiliar;
			}
		}
	}
}

void Buscando_fichas_disponibles(Lista *lista, Nodo *actual){/**Metodo recursivo**/
    if(actual != NULL){
		if(actual->dato->valores[0] == actual->dato->valores[1] && actual->cruzado == 0){
			if(actual->siguiente == NULL || actual->arriba == NULL || actual->abajo == NULL)
				ingresar_Lista(lista, actual);
		}else if(actual->siguiente == NULL){
				ingresar_Lista(lista, actual);
		}
		Buscando_fichas_disponibles(lista, actual->siguiente);
		Buscando_fichas_disponibles(lista, actual->arriba);
		Buscando_fichas_disponibles(lista, actual->abajo);
	}
}

Lista *Fichas_Libres(Mesa *mesa){
	  Lista* lista = NULL;
	  if(mesa->raiz != NULL){
      	lista = (Lista*)calloc(sizeof(Lista),1);
		/**---REVISA QUE LA PRIMERA FICHA (RAIZ) ESTE LIBRE-----**/
		if(mesa->raiz->siguiente == NULL || mesa->raiz->anterior == NULL || mesa->raiz->arriba == NULL || mesa->raiz->abajo == NULL){
			ingresar_Lista(lista,mesa->raiz);
		}
		Buscando_fichas_disponibles(lista, mesa->raiz->arriba);
		Buscando_fichas_disponibles(lista, mesa->raiz->abajo);
		Buscando_fichas_disponibles(lista, mesa->raiz->siguiente);
		Buscando_fichas_disponibles(lista, mesa->raiz->anterior);
	  }
	  return lista;
}

void Liberar_Lista(Lista *lista){/**/
	if(lista->primero != NULL){
		while (lista->primero!=NULL){
			Nodo *auxiliar = lista->primero;
			lista->primero = lista->primero->sig_auxiliar;
			auxiliar->sig_auxiliar = NULL;
		}
		lista->ultimo = NULL;
	}
}
/*MUsESTA FICHAS*/
void Mostrar_Lista(Lista *l){
    if(l->primero != NULL){
        Nodo *actual = l->primero;
        while (actual != NULL){
            int salida = actual->dato->salida;
            if(salida == 0){
                printf("[ %d | %d ]\n",actual->dato->valores[0],actual->dato->valores[1]);
            }else{
                printf("[ %d | %d ]\n",actual->dato->valores[1],actual->dato->valores[0]);
            }
            actual = actual->sig_auxiliar;
        }
    }
}
/* FIN DE LOS METODOS DEL ARBOL Y LISTAS 
 * CODIGO DEL MAS ZAICO AQUI
 * "COMO AROZ!!"
 */