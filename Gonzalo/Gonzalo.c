/*
    Archivo de Trabajo de Gonzalo. Compilar su archivo con el siguiente comando: 
    gcc -o Gonzalo Gonzalo.c --> Esto para tener un orden al momento de crear los ejecutables
    ./Gonzalo --> Comando para ejecutar el programa
    
    git status
    git add nombre_archivo
    git commit -m "Cualquier mensaje"
    git push -uf origin main
*/
#include <stdio.h>
#include <stdlib.h>
#include "Estructura.h"
#include "Arbol.h"
#include "Metodos_Arbol.h"
#include "Metodos_Lista.h"

int main(){
    
    Nodo *n1 = (Nodo *)calloc(sizeof(Nodo),1);
    n1->dato = (Ficha *)calloc(sizeof(Ficha),1);
    n1->dato->valores[0] = 0;
    n1->dato->valores[1] = 3;
    n1->dato->salida = 1;

    Nodo *n2 = (Nodo *)calloc(sizeof(Nodo),1);
    n2->dato = (Ficha *)calloc(sizeof(Ficha),1);
    n2->dato->valores[0] = 2;
    n2->dato->valores[1] = 5;
    n2->dato->salida = 1;
    
    Nodo *n3 = (Nodo *)calloc(sizeof(Nodo),1);
    n3->dato = (Ficha *)calloc(sizeof(Ficha),1);
    n3->dato->valores[0] = 0;
    n3->dato->valores[1] = 0;
    n3->dato->salida = 1;

    Nodo *n4 = (Nodo *)calloc(sizeof(Nodo),1);
    n4->dato = (Ficha *)calloc(sizeof(Ficha),1);
    n4->dato->valores[0] = 3;
    n4->dato->valores[1] = 6;
    n4->dato->salida = 0;


    Lista *l = (Lista *)calloc(sizeof(Lista),1);
    ingresar_Lista(l,n1);
    ingresar_Lista(l,n2);
    ingresar_Lista(l,n3);
    ingresar_Lista(l,n4);

    Mostrar_Lista(l);
    Liberar_Lista(l);

    if(n3->sig_auxiliar == NULL){
        printf("Esta nulo\n");
    }

    return 0;
}
/**	
*   -buscarDondeColocarFicha: evalï¿½a todas las opciones donde es posible colocar la 
*	-ficha y la deja en aquella posiciï¿½n en la que el contador de puntos sea un mï¿½ltiplo 
*	-de 5. Para ello debe contar los valores acumulados en todas las puntas, y se asigna 
*	-un punto por cada mï¿½ltiplo de 5. Es decir si el total de la suma es 35 el jugador x 
*	-acumula 7 puntos.
**/