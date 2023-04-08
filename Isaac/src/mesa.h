#ifndef MESA_H
#define MESA_H

/************************************************************
    ARCHIVO DE CABECERA DONDE SE ENCUENTRAN LA ESTRUCTURA,
    FUNCIONES O MÉTODOS RELACIONADOS A LA MESA DEL JUEGO
*************************************************************/

#include "estructuras.h"

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
void AgregarNodoArbol(Mesa* mesa, Ficha *domino, Nodo *destino, int direccion){
	Nodo *nuevo = CreandoNodo(domino);/*crea el nodo apartir del la ficha recibida*/
 	if(mesa->raiz == NULL){/* Colocasion primera ficha*/
		mesa->raiz = nuevo;
		mesa->raiz->dato->salida = 0;
	}else if(mesa->raiz == destino){/*cololoca en caso de que se desea colocar al rededos de la ficha raiz*/
		printf("Igual a la raiz\n");
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
     
		if(actual->arriba != NULL)
      		muestra_Recursivo(actual->arriba); 

		muestra_Recursivo(actual->siguiente);
	  	printf("[ %d | %d ][\n",actual->dato->valores[0],actual->dato->valores[1]);
	  	
		if(actual->abajo != NULL)
			muestra_Recursivo(actual->abajo);	
	  	printf("\n]\n");
   }
}

void Mostrar_Nodos(Mesa *mesa){
   if(mesa->raiz != NULL){
		muestra_Recursivo(mesa->raiz->anterior);
    	muestra_Recursivo(mesa->raiz);
   }
}

#endif