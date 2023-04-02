#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

typedef struct Ficha Ficha;
typedef struct Nodo Nodo;
typedef struct Lista Lista;

struct Ficha{
      int ficha[2];
	  int salida;
};

struct Nodo{
	Ficha* dato;
	Nodo* anterior, *arriba, *abajo, *siguiente;	
	int cruzado;/**nos dice esta colocada vertical o no**/	
};

struct Lista{
	Nodo *primero,*ultimo;
};

#endif