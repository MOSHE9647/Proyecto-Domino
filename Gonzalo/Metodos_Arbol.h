#ifndef METODOS_ARBOL_H
#define METODOS_ARBOL_H

/** -----LOS PRIMEROS METODOS SON METODOS INTERNOS OSEA SON METODOS QUE SOLO SE USARAN DENTRO DEL CODIGO DE ESTE ARCHIVO----
 * Este metodo de guardar nodo recibe una variable el cual indica
 * si esta guardando en el nodo raiz de la mesa o no
 * mas adelante incuire otra el cual indica hacia que lado de una ficha par
 * desea colocar la ficha siguiente "direccion" 1 arriba, 2 siguiente 3 abajo 0 en caso de que sea raiz
 **/
Nodo* CreandoNodo(Ficha *domino){
	Nodo *nuevo = (Nodo *)calloc(sizeof(Nodo),1);
	nuevo->dato = domino;
	return nuevo;
}

void determinando_salida(Nodo *actual, Nodo *nuevo){
	int salida = actual->dato->salida;
	if(actual->dato->valores[salida] == nuevo->dato->valores[0]){
        nuevo->dato->salida = 1;
	}else if(actual->dato->valores[salida] == nuevo->dato->valores[1]){
		nuevo->dato->salida = 0;
	}
}

void Guardando_Nodo(Nodo *actual, Nodo* nuevo, int direccion){
	if(actual != NULL){
		if(actual->dato->valores[0] != actual->dato->valores[1]){
			if(actual->siguiente == NULL){
				determinando_salida(actual, nuevo);
				nuevo->anterior = actual;
				actual->siguiente = nuevo;
			}
		}else if(actual->dato->valores[0] == actual->dato->valores[1] && actual->cruzado == 0){
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
		if(actual->dato->valores[0] == actual->dato->valores[1]){
			asignacion_recursivo(actual->arriba, nuevo, destino, direccion);
			asignacion_recursivo(actual->abajo, nuevo, destino, direccion);
		}
		asignacion_recursivo(actual->siguiente, nuevo, destino, direccion);
	}
}

void AgregarNodoArbol(Mesa* mesa, Ficha* domino, Nodo *destino, int direccion){
	Nodo *nuevo = CreandoNodo(domino);// crea el nodo apartir del la ficha recibida
 	if(mesa->raiz == NULL){
		mesa->raiz = nuevo;
		mesa->raiz->dato->salida = 0;
	}else if(mesa->raiz == destino)
		Guardando_Nodo(mesa->raiz, nuevo, direccion);
		/*sdasdasd*/
	else{
      	asignacion_recursivo(mesa->raiz->anterior, nuevo, destino, direccion);
		asignacion_recursivo(mesa->raiz, nuevo, destino, direccion);
	}
}	

/**
 * Aquie en  adelante van los metodos de mostreo
 * adasd
 **/
void muestra_Recursivo(Nodo *actual){
   if(actual != NULL){
      printf("[ %d | %d ]\n",actual->dato->valores[0],actual->dato->valores[1]);
      muestra_Recursivo(actual->siguiente);
      muestra_Recursivo(actual->arriba);
      muestra_Recursivo(actual->abajo);
   }
}

void Mostrar_Nodos(Mesa *m){
   if(m != NULL){
		muestra_Recursivo(m->raiz->anterior);
    	muestra_Recursivo(m->raiz);
   }
}
#endif