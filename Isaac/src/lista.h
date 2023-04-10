#ifndef LISTA_H
#define LISTA_H

/************************************************************
    ARCHIVO DE CABECERA DONDE SE ENCUENTRAN LA ESTRUCTURA,
    FUNCIONES O MÉTODOS RELACIONADOS A LAS LISTAS Y A LOS
    NODOS DE ESTAS DENTRO DEL JUEGO
*************************************************************/

#include "estructuras.h"

int Sumando_Extremos_De_Mesa(int contador, Nodo* nuevo){
    if(nuevo->cruzado == 0 && nuevo->dato->doble){
        if(nuevo->arriba == NULL){
            contador += nuevo->dato->valores[0];
        }if(nuevo->abajo == NULL){
            contador += nuevo->dato->valores[0];   
        }
    }else{
        contador += nuevo->dato->valores[nuevo->dato->salida];
    }
    return contador;
}

void ingresar_Lista(Lista *lista, Nodo* nodo){
	if(lista->primero == NULL){
		lista->primero = nodo;
		lista->ultimo = nodo; 
	}else if(lista->primero->dato->valores[lista->primero->dato->salida] >= nodo->dato->valores[nodo->dato->salida]){
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

void Buscando_fichas_disponibles(Lista *lista, Nodo *actual){/**Metodo recursivo**/
    if(actual != NULL){
		if(actual->dato->valores[0] == actual->dato->valores[1] && actual->cruzado == 0){
			if(actual->siguiente == NULL || actual->arriba == NULL || actual->abajo == NULL){
                lista->contador = Sumando_Extremos_De_Mesa(lista->contador, actual);
				ingresar_Lista(lista, actual);
            }
		}else if(actual->siguiente == NULL){
                lista->contador = Sumando_Extremos_De_Mesa(lista->contador, actual);
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
                lista->contador = Sumando_Extremos_De_Mesa(lista->contador, mesa->raiz);
                ingresar_Lista(lista,mesa->raiz);
            }
            Buscando_fichas_disponibles(lista, mesa->raiz->arriba);
		    Buscando_fichas_disponibles(lista, mesa->raiz->abajo);
		    Buscando_fichas_disponibles(lista, mesa->raiz->siguiente);
		    Buscando_fichas_disponibles(lista, mesa->raiz->anterior);
	  }
	  return lista;
}

void Liberar_Lista(Lista *lista){
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
        printf("\n\nPuntos en mesa %d \n", l->contador);
        while (actual != NULL){
            int salida = actual->dato->salida;
            if(salida == 1){
                printf("[ %d | %d ]\n",actual->dato->valores[0], actual->dato->valores[1]);
            }else{
                printf("[ %d | %d ]\n",actual->dato->valores[1], actual->dato->valores[0]);
            }
            actual = actual->sig_auxiliar;
        }
    }
}

/* Mostrando Puntos junto con variables del jugador */
void Mostrando_posibles_Puntajes(Nodo *actual, int valor_x, int valor_y, int puntos){
    int salida = actual->dato->salida;
        if(salida == 1){
            printf("[ %d | %d*] -> ",actual->dato->valores[0],actual->dato->valores[1]);
        }else{
            printf("[ %d |-%d-] -> ",actual->dato->valores[1],actual->dato->valores[0]);
        }   
    printf(" [*%d| %d ]           hace suma de: %d\n\n", valor_x, valor_y, puntos);
}
// void Mostrando_posibles_Puntajes(Nodo *actual, int valor_x, int valor_y, int puntos, int numNodo){
//     int salida = actual->dato->salida;
//         if(salida == 1){
//             printf("#%d  [ %d | %d ] ->",numNodo,actual->dato->valores[0],actual->dato->valores[1]);
//         }else{
//             printf("%d   [ %d | %d ] ->",numNodo,actual->dato->valores[1],actual->dato->valores[0]);
//         }
//     printf(" [ %d | %d ]           Suma: %d\n", valor_x, valor_y, puntos);
// }

void Selector_al_mayor(int *ficha_select, int i, int *mayor, int puntos){
        (*ficha_select) = i;
        (*mayor) = puntos;   
}

// void Selector_al_mayor(Nodo *destino,Nodo *actual,int *ficha_select, int i, int *mayor, int puntos){
//         //destino = actual;
//         (*ficha_select) = i;
//         (*mayor) = puntos;   
// }
// Nodo* Comparando_Lista(Lista *lista, Ficha mazo[], int tamano, int *posicion_elegido, int *direccion, int *cruzado, int *puntos_sumados){
//     Nodo *destino = NULL;
//     /*Guarda cierto nodo destino y posicion de ficha
//     en caso de comparacion a mayor divisibles entre 5*/
//     Nodo *aux_div_5 = NULL;
//     int ficha_selct_div_5 = 0;
//     int direccion_1 = 0;
//     int cruzado_1 = 0; /*Cruzado es 0 y no cruzado es 1 */

//     /* En caso de que no hayase ninguno que sume puntos divisibles entre 5 */
//     Nodo *aux_No_div = NULL;
//     int ficha_selct = 0;
//     int direccion_2 = 0;
//     int cruzado_2 = 0; /* Cruzado es 0 y no cruzado es 1 */
//     /* Variables temporales */
//     int puntos = 0;
//     int mayor_Div = 0, mayor_No_Div = 0,contador_nodo = 0;
//     Nodo *actual = lista->primero;
  
//     while(actual != NULL){
//         int salida = actual->dato->salida;
//         for(int i = 0; i < tamano; i++){  
//             int valor_x = mazo[i].valores[0];
//             int valor_y = mazo[i].valores[1];
//             if((valor_x == valor_y) && (valor_x == actual->dato->valores[salida])){
//                     puntos = lista->contador;
//                     puntos = (puntos - actual->dato->valores[salida]) + mazo[i].valores[0] + mazo[i].valores[1];
//                     if((puntos % 5 == 0)){
//                         if(puntos > mayor_Div ){
//                             Selector_al_mayor(aux_div_5,actual, &ficha_selct_div_5, i, &mayor_Div, puntos);
//                             cruzado_1 = 0;
//                             aux_div_5 = actual;
//                         }
//                     }else if(puntos > mayor_No_Div){
//                         Selector_al_mayor(aux_No_div,actual, &ficha_selct, i, &mayor_No_Div,puntos);
//                         cruzado_2 = 0; 
//                         aux_No_div = actual;
//                     } 
//                     //printf("x==y Actual [%d|%d]   f [%d|%d]  p :%d\n",actual->dato->valores[0],actual->dato->valores[1],valor_x,valor_y,puntos);
//                     puntos = lista->contador;             
//                     puntos = (puntos - actual->dato->valores[salida]) + mazo[i].valores[0];
//                     if((puntos % 5 == 0)){
//                         if(puntos > mayor_Div ){
//                             Selector_al_mayor(aux_div_5,actual, &ficha_selct_div_5, i, &mayor_Div, puntos);
//                             cruzado_1 = 1;
//                             aux_div_5 = actual;
//                         }
//                     }else if(puntos > mayor_No_Div){
//                         Selector_al_mayor(aux_No_div,actual, &ficha_selct, i, &mayor_No_Div, puntos);
//                         cruzado_2 = 1;
//                         aux_No_div = actual;
//                     } 
//                    // printf("2x==y Actual [%d|%d]   f [%d|%d]  p :%d\n",actual->dato->valores[0],actual->dato->valores[1],valor_x,valor_y,puntos);
//             }else if((actual->dato->valores[0] == actual->dato->valores[1]) && (actual->cruzado == 0) && (valor_x == actual->dato->valores[0] || valor_y == actual->dato->valores[0])){
//                     puntos = lista->contador;
//                     if(actual->anterior == NULL){
//                         if(mazo[i].valores[0] == actual->dato->valores[salida]){
//                             puntos += mazo[i].valores[1];
//                         }else if(mazo[i].valores[1] == actual->dato->valores[salida]){
//                             puntos += mazo[i].valores[0];
//                         }
//                         if((puntos % 5 == 0)){
//                             if(puntos > mayor_Div ){
//                                 Selector_al_mayor(aux_div_5,actual, &ficha_selct_div_5, i, &mayor_Div, puntos);
//                                 direccion_1 = 0; 
//                                 aux_div_5 = actual;
//                             }
//                         }else if(puntos > mayor_No_Div){
//                             Selector_al_mayor(aux_No_div,actual, &ficha_selct, i, &mayor_No_Div, puntos);
//                             direccion_2 = 0;
//                             aux_No_div = actual;
//                         } 
//                     }
//                     puntos = lista->contador;
//                     if(actual->siguiente == NULL){
//                         if(mazo[i].valores[0] == actual->dato->valores[salida]){
//                             puntos += mazo[i].valores[1];
//                         }else if(mazo[i].valores[1] == actual->dato->valores[salida]){
//                             puntos += mazo[i].valores[0];
//                         }
//                         if((puntos % 5 == 0)){
//                             if(puntos > mayor_Div ){
//                                 Selector_al_mayor(aux_div_5,actual, &ficha_selct_div_5, i, &mayor_Div, puntos);
//                                 direccion_1 = 2;
//                                 aux_div_5 = actual;
//                             }
//                         }else if(puntos > mayor_No_Div){
//                             Selector_al_mayor(aux_No_div,actual, &ficha_selct, i, &mayor_No_Div, puntos);
//                             direccion_2 = 2;
//                             aux_No_div = actual;
//                         }  
//                     }
//                     puntos = lista->contador;
//                     if(actual->arriba == NULL){
//                             int aux;
//                             if(mazo[i].valores[0] == actual->dato->valores[salida]){
//                                 aux = puntos - actual->dato->valores[salida] + mazo[i].valores[1];
//                             }else if(mazo[i].valores[1] == actual->dato->valores[salida]){
//                                 aux = puntos - actual->dato->valores[salida] + mazo[i].valores[0];
//                             }
//                             if((aux % 5 == 0)){
//                                 if(aux > mayor_Div ){
//                                     Selector_al_mayor(aux_div_5,actual, &ficha_selct_div_5, i, &mayor_Div,aux);
//                                     direccion_1 = 1;
//                                     aux_div_5 = actual;
//                                 }
//                             }else if(aux > mayor_No_Div){
//                                 Selector_al_mayor(aux_No_div,actual, &ficha_selct,i, &mayor_No_Div,aux);
//                                 direccion_2 = 1;
//                                 aux_No_div = actual;
//                             }    
//                     }
//                     puntos = lista->contador;
//                     if(actual->abajo == NULL){
//                             int aux;
//                             if(mazo[i].valores[0] == actual->dato->valores[salida]){
//                                 aux = puntos - actual->dato->valores[salida] + mazo[i].valores[1];
//                             }else if(mazo[i].valores[1] == actual->dato->valores[salida]){
//                                 aux = puntos - actual->dato->valores[salida] + mazo[i].valores[0];
//                             }
//                             if((aux % 5 == 0)){
//                                 if(aux > mayor_Div ){
//                                     Selector_al_mayor(aux_div_5, actual, &ficha_selct_div_5, i, &mayor_Div,aux);
//                                     direccion_1 = 3;
//                                     aux_div_5 = actual;
//                                 }
//                             }else if(aux > mayor_No_Div){
//                                     Selector_al_mayor(aux_No_div, actual, &ficha_selct, i, &mayor_No_Div, aux);
//                                     direccion_2 = 3;
//                                     aux_No_div = actual;
//                             }
//                     }
//                     //printf("ax == bx Actual [%d|%d]   f [%d|%d]\n",actual->dato->valores[0],actual->dato->valores[1],valor_x,valor_y );
//             }else if(valor_x == actual->dato->valores[salida]){
//                     puntos = lista->contador;
//                     puntos = (puntos - actual->dato->valores[salida]) + mazo[i].valores[1];
//                     if((puntos % 5 == 0)){
//                         if(puntos > mayor_Div ){
//                             Selector_al_mayor(aux_div_5,actual,&ficha_selct_div_5, i, &mayor_Div,puntos);
//                             direccion_1 = 2;
//                             aux_div_5 = actual;
//                         }
//                     }else if(puntos > mayor_No_Div){
//                         Selector_al_mayor(aux_No_div, actual, &ficha_selct, i, &mayor_No_Div, puntos);
//                         direccion_2 = 2;
//                         aux_No_div = actual;
//                     }  
//                     //printf("x !=  Actual [%d|%d]   f [%d|%d]\n",actual->dato->valores[0],actual->dato->valores[1],valor_x,valor_y );
//             }else if(valor_y == actual->dato->valores[salida]){
//                     puntos = lista->contador;
//                     puntos = (puntos - actual->dato->valores[salida]) + mazo[i].valores[0]; 
//                     if((puntos % 5 == 0)){
//                         if(puntos > mayor_Div ){
//                             Selector_al_mayor(aux_div_5,actual, &ficha_selct_div_5, i, &mayor_Div, puntos);
//                             direccion_1 = 2;   
//                             aux_div_5 = actual; 
//                         }
//                     }else if(puntos > mayor_No_Div){
//                         Selector_al_mayor(aux_No_div,actual, &ficha_selct, i, &mayor_No_Div, puntos);
//                         direccion_2 = 2;
//                         aux_No_div = actual;
//                     }       
//                     //printf("y != Actual [%d|%d]   f [%d|%d]\n",actual->dato->valores[0],actual->dato->valores[1],valor_x,valor_y );
//             } 
//         }
//         actual = actual->sig_auxiliar;
//     }

//     if(mayor_Div > 0 ){
//         (*posicion_elegido) = ficha_selct_div_5;
//         (*puntos_sumados) = mayor_Div;
//         (*cruzado) = cruzado_1;
//         (*direccion) = direccion_1;
//         destino = aux_div_5;
//     }else{
//         (*posicion_elegido) = ficha_selct;
//         (*puntos_sumados) = 0;
//         (*cruzado) = cruzado_2;
//         (*direccion) = direccion_2;
//         destino = aux_No_div;
//     }

//     return destino;
// }

Nodo* bucarDondeColocar(Lista *lista, Ficha mazo[], int tamano, int *posicion_elegido, int *direccion, int *cruzado, int *puntos_sumados){
    Nodo *destino = NULL;
    /*Guarda cierto nodo destino y posicion de ficha
    en caso de comparacion a mayor divisibles entre 5*/
    Nodo *aux_div_5 = NULL;
    int ficha_selct_div_5 = 0;
    int direccion_1 = 0;
    int cruzado_1 = 0; /*Cruzado es 0 y no cruzado es 1 */

    /* En caso de que no hayase ninguno que sume puntos divisibles entre 5 */
    Nodo *aux_No_div = NULL;
    int ficha_selct = 0;
    int direccion_2 = 0;
    int cruzado_2 = 0; /* Cruzado es 0 y no cruzado es 1 */
    /* Variables temporales */
    int puntos = 0;
    int mayor_Div = 0, mayor_No_Div = 0;
    Nodo *actual = lista->primero;
  
    while(actual != NULL){
        int salida = actual->dato->salida;

        /* Recorriendo el vector de fichas para seleccionar al mas conveniente */
        for(int i = 0; i < tamano-1; i++){  
            int valor_x = mazo[i].valores[0];
            int valor_y = mazo[i].valores[1];

            if((valor_x == valor_y) && (valor_x == actual->dato->valores[salida])){
                    puntos = lista->contador;
                    puntos = (puntos - actual->dato->valores[salida]) + valor_x + valor_y;
                    if((puntos % 5 == 0)){
                        if(puntos > mayor_Div ){
                            Selector_al_mayor(&ficha_selct_div_5, i, &mayor_Div, puntos);
                            cruzado_1 = 0;
                            aux_div_5 = actual;
                        }
                    }else if(puntos > mayor_No_Div){
                        Selector_al_mayor( &ficha_selct, i, &mayor_No_Div,puntos);
                        cruzado_2 = 0; 
                        aux_No_div = actual;
                    } 
                    Mostrando_posibles_Puntajes(actual,valor_x,valor_y,puntos);
                    puntos = lista->contador;             
                    puntos = (puntos - actual->dato->valores[salida]) + valor_x;
                    if((puntos % 5 == 0)){
                        if(puntos > mayor_Div ){
                            Selector_al_mayor(&ficha_selct_div_5, i, &mayor_Div, puntos);
                            cruzado_1 = 1;
                            aux_div_5 = actual;
                        }
                    }else if(puntos > mayor_No_Div){
                        Selector_al_mayor(&ficha_selct, i, &mayor_No_Div, puntos);
                        cruzado_2 = 1;
                        aux_No_div = actual;
                    } 
                    printf("cruzado-> ");
                    Mostrando_posibles_Puntajes(actual,valor_x,valor_y,puntos);
            }else if((actual->dato->valores[0] == actual->dato->valores[1]) && (actual->cruzado == 0) && (valor_x == actual->dato->valores[0] || valor_y == actual->dato->valores[0])){
                    puntos = lista->contador;
                    if(actual->anterior == NULL){
                        printf ("ANT -> ");
                        if(valor_x == actual->dato->valores[salida]){
                            puntos += valor_y;
                            Mostrando_posibles_Puntajes(actual,valor_x,valor_y,puntos);
                        }else if(valor_y == actual->dato->valores[salida]){
                            puntos += valor_x;
                            Mostrando_posibles_Puntajes(actual,valor_y,valor_x,puntos);
                        }
                        if((puntos % 5 == 0)){
                            if(puntos > mayor_Div ){
                                Selector_al_mayor(&ficha_selct_div_5, i, &mayor_Div, puntos);
                                direccion_1 = 0; 
                                aux_div_5 = actual;
                            }
                        }else if(puntos > mayor_No_Div){
                            Selector_al_mayor( &ficha_selct, i, &mayor_No_Div, puntos);
                            direccion_2 = 0;
                            aux_No_div = actual;
                        } 
                    }
                    puntos = lista->contador;
                    if(actual->siguiente == NULL){
                        printf ("SIG -> ");
                        if(valor_x == actual->dato->valores[salida]){
                            puntos += valor_y;
                            Mostrando_posibles_Puntajes(actual,valor_x,valor_y,puntos);
                        }else if(valor_y == actual->dato->valores[salida]){
                            puntos += valor_x;
                            Mostrando_posibles_Puntajes(actual,valor_y,valor_x,puntos);
                        }
                        if((puntos % 5 == 0)){
                            if(puntos > mayor_Div ){
                                Selector_al_mayor(&ficha_selct_div_5, i, &mayor_Div, puntos);
                                direccion_1 = 2;
                                aux_div_5 = actual;
                            }
                        }else if(puntos > mayor_No_Div){
                            Selector_al_mayor(&ficha_selct, i, &mayor_No_Div, puntos);
                            direccion_2 = 2;
                            aux_No_div = actual;
                        }
                    }
                    puntos = lista->contador;
                    if(actual->arriba == NULL){
                        printf ("ARR -> ");
                            if(valor_x == actual->dato->valores[salida]){
                                puntos = puntos - actual->dato->valores[salida] + valor_y;
                                Mostrando_posibles_Puntajes(actual,valor_x,valor_y,puntos);
                            }else if(valor_y == actual->dato->valores[salida]){
                                puntos = puntos - actual->dato->valores[salida] + valor_x;
                                Mostrando_posibles_Puntajes(actual,valor_y,valor_x,puntos);
                            }
                            if((puntos % 5 == 0)){
                                if(puntos > mayor_Div ){
                                    Selector_al_mayor(&ficha_selct_div_5, i, &mayor_Div,puntos);
                                    direccion_1 = 1;
                                    aux_div_5 = actual;
                                }
                            }else if(puntos > mayor_No_Div){
                                Selector_al_mayor(&ficha_selct,i, &mayor_No_Div,puntos);
                                direccion_2 = 1;
                                aux_No_div = actual;
                            }    
                    }
                    puntos = lista->contador;
                    if(actual->abajo == NULL){
                        printf ("ABA -> ");
                            if(valor_x == actual->dato->valores[salida]){
                                puntos = puntos - actual->dato->valores[salida] + valor_y;
                                Mostrando_posibles_Puntajes(actual,valor_x,valor_y,puntos);
                            }else if(valor_y == actual->dato->valores[salida]){
                                puntos = puntos - actual->dato->valores[salida] + valor_x;
                                Mostrando_posibles_Puntajes(actual,valor_y,valor_x,puntos);
                            }
                            if((puntos % 5 == 0)){
                                if(puntos > mayor_Div ){
                                    Selector_al_mayor(&ficha_selct_div_5, i, &mayor_Div,puntos);
                                    direccion_1 = 3;
                                    aux_div_5 = actual;
                                }
                            }else if(puntos > mayor_No_Div){
                                    Selector_al_mayor(&ficha_selct, i, &mayor_No_Div, puntos);
                                    direccion_2 = 3;
                                    aux_No_div = actual;
                            }
                    }
                    
            }else if(valor_x == actual->dato->valores[salida]){
                    puntos = lista->contador;
                    puntos = (puntos - actual->dato->valores[salida]) + mazo[i].valores[1];
                    if((puntos % 5 == 0)){
                        if(puntos > mayor_Div ){
                            Selector_al_mayor(&ficha_selct_div_5, i, &mayor_Div,puntos);
                            direccion_1 = 2;
                            aux_div_5 = actual;
                        }
                    }else if(puntos > mayor_No_Div){
                        Selector_al_mayor(&ficha_selct, i, &mayor_No_Div, puntos);
                        direccion_2 = 2;
                        aux_No_div = actual;
                    }  
                    Mostrando_posibles_Puntajes(actual,valor_x,valor_y,puntos);
            }else if(valor_y == actual->dato->valores[salida]){
                    puntos = lista->contador;
                    puntos = (puntos - actual->dato->valores[salida]) + mazo[i].valores[0]; 
                    if((puntos % 5 == 0)){
                        if(puntos > mayor_Div ){
                            Selector_al_mayor(&ficha_selct_div_5, i, &mayor_Div, puntos);
                            direccion_1 = 2;   
                            aux_div_5 = actual; 
                        }
                    }else if(puntos > mayor_No_Div){
                        Selector_al_mayor(&ficha_selct, i, &mayor_No_Div, puntos);
                        direccion_2 = 2;
                        aux_No_div = actual;
                    }
                    Mostrando_posibles_Puntajes(actual,valor_y,valor_x,puntos);       
              } 
        }
        actual = actual->sig_auxiliar;
    }

    if(mayor_Div > 0 ){
        (*posicion_elegido) = ficha_selct_div_5;
        (*puntos_sumados) = mayor_Div;
        (*cruzado) = cruzado_1;
        (*direccion) = direccion_1;
        destino = aux_div_5;
    }else{
        (*posicion_elegido) = ficha_selct;
        (*puntos_sumados) = 0;
        (*cruzado) = cruzado_2;
        (*direccion) = direccion_2;
        destino = aux_No_div;
    }

    return destino;
}

#endif