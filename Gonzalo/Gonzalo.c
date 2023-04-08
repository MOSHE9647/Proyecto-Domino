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
#define MAX 28
Ficha ficha[MAX];

void gotoxy(int x,int y){
    printf("%c[%d;%df",0x1B,y,x);
}

int main(){

    int contador = 0;
    for (int i = 0; i <= 6; i++){
        for(int j = i; j <= 6; j++){
            ficha[contador].valores[0] = i;
            ficha[contador].valores[1] = j;
            contador++;
        }
    }
    printf("\n\n");
    for (int i = 0; i < 28; i++){
            printf("[%d|%d]\n",ficha[i].valores[0],ficha[i].valores[1]);
    }


    Mesa *mesa = (Mesa *)calloc(sizeof(Mesa), 1);

    
    Nodo *n1 = (Nodo *)calloc(sizeof(Nodo),1);
    n1->dato = (Ficha *)calloc(sizeof(Ficha),1);
    n1->dato->valores[0] = 4;
    n1->dato->valores[1] = 4;
    n1->dato->salida = 1;

    Nodo *n2 = (Nodo *)calloc(sizeof(Nodo),1);
    n2->dato = (Ficha *)calloc(sizeof(Ficha),1);
    n2->dato->valores[0] = 1;
    n2->dato->valores[1] = 4;
    n2->dato->salida = 1;
    /**
    Nodo *n3 = (Nodo *)calloc(sizeof(Nodo),1);
    n3->dato = (Ficha *)calloc(sizeof(Ficha),1);
    n3->dato->valores[0] = 2;
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
    n5->dato->salida = 1;**/
   
    AgregarNodoArbol(mesa,n1,NULL,0);
    AgregarNodoArbol(mesa,n2,n1,2);
    /**AgregarNodoArbol(mesa,n3,n2,2);
    AgregarNodoArbol(mesa,n4,n1,0);
    AgregarNodoArbol(mesa,n5,n4,2);
    Mostrar_Nodos(mesa);**/

    Lista *l = Fichas_Libres(mesa);
    printf("Lista...\n");
    Mostrar_Lista(l);

    gotoxy(15,15);printf("........\n\n");
    int posicion;
    int direccion;
    int cruzado;
    int puntos;
    int n = 28;
    printf("Puntos sumados : %d\n",l->contador);
    Nodo *nodo = Comparando_Lista(l,ficha,n, &posicion, &direccion, &cruzado, &puntos);
    printf("Posicion %d\n",posicion);
    printf("ficha [%d|%d]   direccion %d  cruzado %d    puntos %d \n",ficha[posicion].valores[0],ficha[posicion].valores[1],direccion, cruzado,puntos);
    Liberar_Lista(l);
    gotoxy(0,30); printf("..");
    return 0;
}
/**	
*   -buscarDondeColocarFicha: evalï¿½a todas las opciones donde es posible colocar la 
*	-ficha y la deja en aquella posiciï¿½n en la que el contador de puntos sea un mï¿½ltiplo 
*	-de 5. Para ello debe contar los valores acumulados en todas las puntas, y se asigna 
*	-un punto por cada mï¿½ltiplo de 5. Es decir si el total de la suma es 35 el jugador x 
*	-acumula 7 puntos.
**/