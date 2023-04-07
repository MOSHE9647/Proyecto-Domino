#ifndef METODOS_LISTA_H
#define METODOS_LISTA_H
/**
 * aqui creo la lista con los nodos libres de la mesa
 * de una manera ordenada jejej
 **/
void Sumando_Extremos_De_Mesa(int *contador, Nodo* nuevo){
    if(nuevo->cruzado == 0 && nuevo->dato->valores[0] == nuevo->dato->valores[1]){
        if(nuevo->abajo == NULL)
            contador += nuevo->dato->valores[nuevo->dato->salida];
         if(nuevo->abajo == NULL)
            contador += nuevo->dato->valores[nuevo->dato->salida];
    }else{
        contador += nuevo->dato->valores[nuevo->dato->salida];
    }
}

void ingresar_Lista(Lista *lista, Nodo* nodo){
	if(lista->primero == NULL){
		lista->primero = nodo;
		lista->ultimo = nodo; 
        lista->cantidad_Nodos++;
	}else{
		if(lista->primero->dato->valores[lista->primero->dato->salida] >= nodo->dato->valores[nodo->dato->salida]){
			nodo->sig_auxiliar = lista->primero;
			lista->primero = nodo;
            lista->cantidad_Nodos++;
		}else if(lista->ultimo->dato->valores[lista->primero->dato->salida] <= nodo->dato->valores[nodo->dato->salida]){
			lista->ultimo->sig_auxiliar = nodo;
			lista->ultimo = nodo;
            lista->cantidad_Nodos++;
		}else{
			Nodo *actual = lista->primero;
            int salida = nodo->dato->salida;
			while (actual != NULL){
                int auxiliar = actual->dato->salida;
				if(nodo->dato->valores[salida] <= actual->sig_auxiliar->dato->valores[auxiliar]){
                    nodo->sig_auxiliar = actual->sig_auxiliar;
					actual->sig_auxiliar = nodo;
                    lista->cantidad_Nodos++;
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
			if(actual->siguiente == NULL || actual->arriba == NULL || actual->abajo == NULL){
                Sumando_Extremos_De_Mesa(&lista->contador, actual);
				ingresar_Lista(lista, actual);
            }
		}else if(actual->siguiente == NULL){
                Sumando_Extremos_De_Mesa(&lista->contador, actual);
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
void Mostrando_posibles_Puntajes(Nodo *actual, int valor_x, int valor_y, int puntos, int numNodo){
    int salida = actual->dato->salida;
    if(salida == 1){
        printf("#%d  [ %d | %d ] ->",numNodo,actual->dato->valores[0],actual->dato->valores[1]);
    }else{
        printf("%d   [ %d | %d ] ->",numNodo,actual->dato->valores[1],actual->dato->valores[0]);
    }
    printf(" [ %d | %d ]           Suma: %d\n", valor_x, valor_y, puntos);
}

Nodo* Comparando_Lista(Lista *lista, Ficha mazo[], int tamano , int *seleccion_f){
    Nodo *destino = NULL;
    Nodo *actual = lista->primero;
    int puntos = 0, contador_nodo = 1;
    int ficha = 0, mayor_Mult = 0, mayor_Genr = 0;

    while (actual != NULL){
        int salida = actual->dato->salida;
        for(int i = 0; i < tamano; i++){
            int valor_x = mazo[i].valores[0];
            int valor_y = mazo[i].valores[1];
            if((valor_x == valor_y) && (valor_x == actual->dato->valores[salida])){
                    puntos = lista->contador;
                    puntos = mazo[i].valores[0] + mazo[i].valores[1];
                    Mostrando_posibles_Puntajes(actual, valor_x, valor_y, puntos, contador_nodo);
            }else{
                if(valor_x == actual->dato->valores[salida]){
                    puntos = lista->contador;
                    puntos = mazo[i].valores[0] - actual->dato->valores[salida];
                    Mostrando_posibles_Puntajes(actual, valor_x, valor_y, puntos, contador_nodo);
                }
                if(valor_y == actual->dato->valores[salida]){
                    puntos = lista->contador;
                    puntos = mazo[i].valores[1] - actual->dato->valores[salida]; 
                    Mostrando_posibles_Puntajes(actual, valor_y, valor_x, puntos, contador_nodo);
                }
            } 
        }
        contador_nodo++;
        actual = actual->sig_auxiliar;
    }
}


#endif