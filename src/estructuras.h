#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

/************************************************************
    ARCHIVO DE CABECERA DONDE SE ENCUENTRAN LAS ESTRUCTURAS
    DE MESA, LISTA Y NODO PARA SU USO DENTRO DEL JUEGO
*************************************************************/

#include "ficha.h"

typedef struct Lista Lista;
typedef struct Nodo Nodo;
typedef struct Mesa Mesa;

struct Nodo{
	Ficha* dato;            /* Guarda una referencia a una ficha                                            */
	Nodo* anterior;         /* Guarda referencia del Nodo,"Ficha", que estaba libre anterios                */
    Nodo *arriba;           /* Guarda referencia del Nodo, colocado arriba, solo se usa en caso de ser doble*/
    Nodo *abajo;            /* Guarda referencia del Nodo, colocado abajo, solo se usa en caso de ser doble */
    Nodo *siguiente;        /* Guarda referencia del Nodo, hacia delante                                    */
    Nodo *sig_auxiliar;     /* Esto guarda solo una referencia temporal, solo para la lista de salidas      */
	int cruzado;            /* Nos dice esta colocada vertical o no                                         */	
};

struct Lista{
	Nodo *primero;          /* Guarda referencia el primer Nodo agregado a lista                            */
    Nodo *ultimo;           /* Guarda referencia al ultimo Nodo agregaddo a la lista                        */
    int contador;
};

struct Mesa{
	Nodo *raiz;
};

#endif