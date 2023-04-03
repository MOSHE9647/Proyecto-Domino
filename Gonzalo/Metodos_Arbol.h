#ifndef METODOS_ARBOL_H
#define METODOS_ARBOL_H

/** -----LOS PRIMEROS METODOS SON METODOS INTERNOS OSEA SON METODOS QUE SOLO SE USARAN DENTRO DEL CODIGO DE ESTE ARCHIVO----
 * Este metodo de guardar nodo recibe una variable el cual indica
 * si esta guardando en el nodo raiz de la mesa o no
 * mas adelante incuire otra el cual indica hacia que lado de una ficha par
 * desea colocar la ficha siguiente "direccion" 1 arriba, 2 siguiente 3 abajo 0 en caso de que sea raiz
 **/
Nodo* CreandoNodo(Ficha *domino){
	Nodo *nuevo = (Ficha *)calloc(sizeof(Ficha),1);
	nuevo->dato = domino;
	return nuevo;
}
/**guarda cual es el lado de la ficha que esta disponible para la siguiente ronda**/
void determinando_salida(Nodo *actual, Nodo *nuevo){
	int salida = actual->dato->salida;
	if(actual->dato->ficha[salida] == nuevo->dato->ficha[0]){
        nuevo->dato->salida = 1;
	}else if(actual->dato->ficha[salida] == nuevo->dato->ficha[1]){
		nuevo->dato->salida = 0;
	}
}

void Guardando_Nodo(Nodo *actual, Nodo* nuevo, int direccion){
	if(actual != NULL){
		if(actual->dato->ficha[0] != actual->dato->ficha[1]){
			if(actual->siguiente == NULL){
				determinando_salida(actual, nuevo);
				nuevo->anterior = actual;
				actual->siguiente = nuevo;
			}
		}else if(actual->dato->ficha[0] == actual->dato->ficha[1] && actual->cruzado == 0){
			if(actual->arriba == NULL && direccion == 1){
				determinando_salida(actual, nuevo);
				nuevo->anterior = actual;
				actual->arriba = nuevo;
			
			}else if(actual->siguiente == NULL && direccion == 2){
				determinando_salida(actual, nuevo);
				nuevo->anterior = actual;
				actual->siguiente = nuevo;

			}else if(actual->abajo == NULL && direccion == 3){
				determinando_salida(actual, nuevo);
				nuevo->anterior = actual;
				actual->abajo = nuevo;

			}else if(actual->anterior == NULL && direccion == 0){
				determinando_salida(actual, nuevo);
				nuevo->anterior = actual;
				actual->anterior = nuevo;

			}
		}else{
			determinando_salida(actual, nuevo);
			nuevo->anterior = actual;
			actual->siguiente = nuevo;
		}
	}
}

void asignacion_recursivo(Nodo *actual, Nodo* nuevo, Nodo *destino, int direccion){
	if(actual != NULL){
		if(actual == destino)
			Guardando_Nodo(actual, nuevo, direccion);
	}else{
		if(actual->dato->ficha[0] == actual->dato->ficha[1]){
			asignacion_recursivo(actual->arriba, nuevo, destino, direccion);
			asignacion_recursivo(actual->abajo, nuevo, destino, direccion);
		}
		asignacion_recursivo(actual->siguiente, nuevo, destino, direccion);
	}
}
/**
 * metodo prinsipal que se llamara fuera de este archivo
 * 
 **/
void AgregarNodoArbol(Mesa* mesa, Ficha* domino, Nodo *destino, int direccion){
	Nodo *nuevo = CreandoNodo(domino);// crea el nodo apartir del la ficha recibida
 	if(mesa->raiz == NULL){
		mesa->raiz = nuevo;
		mesa->raiz->dato->salida = 0;
	}else if(mesa->raiz == destino)
		Guardando_Nodo(mesa->raiz, nuevo, direccion);
	else{
      	asignacion_recursivo(mesa->raiz->anterior, nuevo, destino, direccion);
		asignacion_recursivo(mesa->raiz, nuevo, destino, direccion);
	}
}	
/**
 * aqui creo la lista con los nodos libres
 **/
void ingresar_Lista(Lista *lista, Nodo* nodo){
	if(lista->primero == NULL){
		lista->primero = nodo;
		lista->ultimo = nodo;
	}else{
		lista->ultimo->sig_auxiliar = nodo;
		lista->ultimo = nodo;
	}
}
void Buscando_fichas_disponibles(Lista *lista,Nodo *actual){/**Metodo recursivo**/
    if(actual != NULL){/** esta condicion evita la recursividad "infinita" **/
		/**si la ficha es libre y no este cruzada y no este cruzada osea es 0 entoces revisa todos
		 * sus lados en busca de una salida libre para tomarlo como siguiente ficha disponible
		 * de lo contrario sera tomada como ficha ordinaria
		 * **/
		if(actual->dato->ficha[0] == actual->dato->ficha[1] && actual->cruzado == 0)
			if(actual->siguiente == NULL || actual->arriba == NULL || actual->abajo == NULL)
				ingresar_Lista(lista, actual);
		else if(actual->siguiente == NULL)
				ingresar_Lista(lista, actual);

		Buscando_fichas_disponibles(lista, actual->siguiente);
		Buscando_fichas_disponibles(lista, actual->arriba);
		Buscando_fichas_disponibles(lista, actual->abajo);
	}
}

Lista *Fichas_Libres(Lista* lista, Mesa *mesa){
	Lista* lista = NULL;
	  if(mesa->raiz != NULL){
      	lista = (Lista*)calloc(sizeof(Lista),1);
		/**---REVISA QUE LA PRIMERA FICHA ESTE LIBRE-----**/
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
/**
 * Aquie en  adelante van los metodos de mostreo
 **/
void muestra_Recursivo(Nodo *actual){
   if(actual != NULL){
      printf("[ %d | %d ]\n",actual->dato->ficha[0],actual->dato->ficha[1]);
      printf("\nsiguiente\n");
      muestra_Recursivo(actual->siguiente);
      printf("\narriba\n");
      muestra_Recursivo(actual->arriba);
      printf("\nabajo\n");
      muestra_Recursivo(actual->abajo);
   }
}

void Mostrar_Nodos(Mesa *m){
   if(m != NULL){
		muestra_Recursivo(m->raiz->anterior);
    	muestra_Recursivo(m->raiz);
   }else{
      printf("Mesa vacia\n");
   }
}
#endif