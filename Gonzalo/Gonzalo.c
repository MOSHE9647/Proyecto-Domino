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
   
    return 0;
}
/**	
*   -buscarDondeColocarFicha: evalï¿½a todas las opciones donde es posible colocar la 
*	-ficha y la deja en aquella posiciï¿½n en la que el contador de puntos sea un mï¿½ltiplo 
*	-de 5. Para ello debe contar los valores acumulados en todas las puntas, y se asigna 
*	-un punto por cada mï¿½ltiplo de 5. Es decir si el total de la suma es 35 el jugador x 
*	-acumula 7 puntos.
**/