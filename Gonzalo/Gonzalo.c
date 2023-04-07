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

    Mesa *mesa = (Mesa *)calloc(sizeof(Mesa), 1);

    
    Nodo *n1 = (Nodo *)calloc(sizeof(Nodo),1);
    n1->dato = (Ficha *)calloc(sizeof(Ficha),1);
    n1->dato->valores[0] = 0;
    n1->dato->valores[1] = 0;
    n1->dato->salida = 1;

    Nodo *n2 = (Nodo *)calloc(sizeof(Nodo),1);
    n2->dato = (Ficha *)calloc(sizeof(Ficha),1);
    n2->dato->valores[0] = 1;
    n2->dato->valores[1] = 0;
    n2->dato->salida = 1;
    
    Nodo *n3 = (Nodo *)calloc(sizeof(Nodo),1);
    n3->dato = (Ficha *)calloc(sizeof(Ficha),1);
    n3->dato->valores[0] = 3;
    n3->dato->valores[1] = 1;
    n3->dato->salida = 1;

    Nodo *n4 = (Nodo *)calloc(sizeof(Nodo),1);
    n4->dato = (Ficha *)calloc(sizeof(Ficha),1);
    n4->dato->valores[0] = 3;
    n4->dato->valores[1] = 0;
    n4->dato->salida = 0;

    Nodo *n5 = (Nodo *)calloc(sizeof(Nodo),1);
    n5->dato = (Ficha *)calloc(sizeof(Ficha),1);
    n5->dato->valores[0] = 6;
    n5->dato->valores[1] = 3;
    n5->dato->salida = 1;
    

    AgregarNodoArbol(mesa,n1,NULL,0);
    AgregarNodoArbol(mesa,n2,n1,2);
    AgregarNodoArbol(mesa,n3,n2,2);
    AgregarNodoArbol(mesa,n4,n1,0);
    AgregarNodoArbol(mesa,n5,n4,2);
    Mostrar_Nodos(mesa);

    Lista *l = Fichas_Libres(mesa);
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