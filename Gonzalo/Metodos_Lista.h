#ifndef METODOS_LISTA_H
#define METODOS_LISTA_H
/**
 * aqui creo la lista con los nodos libres de la mesa
 * de una manera ordenada jejej
 **/
void ingresar_Lista(Lista *lista, Nodo* nodo){
	if(lista->primero == NULL){
		lista->primero = nodo;
		lista->ultimo = nodo; 
	}else{
		if(lista->primero->dato->valores[lista->primero->dato->salida] >= nodo->dato->valores[nodo->dato->salida]){
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
}

void Buscando_fichas_disponibles(Lista *lista, Nodo *actual){/**Metodo recursivo**/
    if(actual != NULL){
		if(actual->dato->valores[0] == actual->dato->valores[1] && actual->cruzado == 0){
			if(actual->siguiente == NULL || actual->arriba == NULL || actual->abajo == NULL)
				ingresar_Lista(lista, actual);
		}else if(actual->siguiente == NULL){
				ingresar_Lista(lista, actual);
		}
		Buscando_fichas_disponibles(lista, actual->siguiente);
		Buscando_fichas_disponibles(lista, actual->arriba);
		Buscando_fichas_disponibles(lista, actual->abajo);
	}
}

Lista *Fichas_Libres(Lista* lista, Mesa *mesa){
	//Lista* lista = NULL;
	  if(mesa->raiz != NULL){
      	lista = (Lista*)calloc(sizeof(Lista),1);
		/**---REVISA QUE LA PRIMERA FICHA RAIZ ESTE LIBRE-----**/
		if(mesa->raiz->siguiente == NULL || mesa->raiz->anterior == NULL || mesa->raiz->arriba == NULL || mesa->raiz->abajo == NULL){
			ingresar_Lista(lista,mesa->raiz);
		}
		/** si el nodo raiz es uno de los que tiene libre entoces
		 * entoces lo guardara en en la condicion if linea 108 y 109
		 * por lo que no hace falta pasarlo al buscando_fichas disponible()
		 * y en el tal caso de que no cumpla no afectara ya que no cumplira con los requisitos
		 * **/
		Buscando_fichas_disponibles(lista, mesa->raiz->arriba);
		Buscando_fichas_disponibles(lista, mesa->raiz->abajo);
		Buscando_fichas_disponibles(lista, mesa->raiz->siguiente);
		Buscando_fichas_disponibles(lista, mesa->raiz->anterior);
	  }
	  return lista; // si retorna NULL es por que no hay nada en la mesa
}

/** ESTE METODO HACE QUE LOS NODOS NO DEJEN RASTRO DE LA LISTA YA QUE AL SER INGRESADAS ESOS
 *  ESPACIOS GUARDAN REFERENCIA LAS CUALES DEBES LIMBIARES OJO LIMPIAR EL PUNTERO NO LIBERAR EL ESPACIO
 *  DE MEMORIA AL DE NO USARSE PERJUDICARA LAS LISTAS FUTURAS, POR ESO SIEMPRE QUE EL 
 *  JUGADOR YA HAYASE AGREGADO, ELEGIDO LA FICHA SE DEBE USAR ESTE METODO PARA NO DEJAR REFERENCIAS
 * 	EN LOS NODOS DEL ARBOL (nodo->sig_auxiliar != NULL):
 * **/
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

void Mostrar_Lista(Lista *l){
    if(l->primero != NULL){
        Nodo *actual = l->primero;
        while (actual != NULL){
            int salida = actual->dato->salida;
            if(salida == 0){
                printf("[ %d | %d ]\n",actual->dato->valores[0],actual->dato->valores[1]);
            }else{
                printf("[ %d | %d ]\n",actual->dato->valores[1],actual->dato->valores[0]);
            }
            actual = actual->sig_auxiliar;
        }
    }
}

#endif