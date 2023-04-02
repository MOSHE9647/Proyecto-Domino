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

int main(){
    Nodo *n1 = (Nodo *)calloc(sizeof(Nodo),1);
    n1->dato =(Ficha* )calloc(sizeof(Ficha),1);
    n1->dato->ficha[0]=0;
    n1->dato->ficha[1]=0;

    Nodo *n2 = (Nodo *)calloc(sizeof(Nodo),1);
    n2->dato =(Ficha* )calloc(sizeof(Ficha),1);
    n2->dato->ficha[0]=1;
    n2->dato->ficha[1]=6;
    
    Nodo *n3= (Nodo *)calloc(sizeof(Nodo),1);
    n3->dato =(Ficha* )calloc(sizeof(Ficha),1);
    n3->dato->ficha[0]=2;
    n3->dato->ficha[1]=5;

    Nodo *n4 = (Nodo *)calloc(sizeof(Nodo),1);
    n4->dato =(Ficha* )calloc(sizeof(Ficha),1);
    n4->dato->ficha[0]=3;
    n4->dato->ficha[1]=4;
    
    Nodo *n5 = (Nodo *)calloc(sizeof(Nodo),1);
    n5->dato =(Ficha* )calloc(sizeof(Ficha),1);
    n5->dato->ficha[0]=4;
    n5->dato->ficha[1]=5;
    Mesa *m = (Mesa *)calloc(sizeof(Mesa),1); 

    AgregarNodoArbol(m,n1,NULL);
    AgregarNodoArbol(m,n2,n1);
    AgregarNodoArbol(m,n3,n1);
    AgregarNodoArbol(m,n4,n1);
    AgregarNodoArbol(m,n5,n1);
    Mostrar_Nodos(m);
    return 0;
}