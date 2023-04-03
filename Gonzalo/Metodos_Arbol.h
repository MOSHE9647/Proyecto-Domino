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

void Guardando_Nodo(Nodo *actual, Nodo* nuevo, int direccion){
	if(actual != NULL){
		if(actual->dato->ficha[0] != actual->dato->ficha[1]){
			if(actual->siguiente == NULL){
				nuevo->anterior = actual;
				actual->siguiente = nuevo;
			}
		}else if(actual->dato->ficha[0] == actual->dato->ficha[1] && actual->cruzado == 1){
			if(actual->arriba == NULL && direccion == 1){
				nuevo->anterior = actual;
				actual->arriba = nuevo;
			
			}else if(actual->siguiente == NULL && direccion == 2){
				nuevo->anterior = actual;
				actual->siguiente = nuevo;

			}else if(actual->abajo == NULL direccion == 3){
				nuevo->anterior = actual;
				actual->abajo = nuevo;

			}else if(actual->anterior == NULL && direccion == 0){
				nuevo->anterior = actual;
				actual->anterior = nuevo;

			}
		}else{	
			nuevo->anterior = actual;
			actual->siguiente = nuevo;
		}
	}
}

void asignacion_recursivo(Nodo *actual, Nodo* nuevo, Nodo *destino, int direccion){
	if(actual != NULL){
		if(actual == destino){
			Guardando_Nodo(actual, nuevo, direccion);
		}
	}else{
		if(actual->dato->ficha[0] == actual->dato->ficha[1]){
			asignacion_recursivo(actual->arriba, nuevo, destino);
			asignacion_recursivo(actual->abajo, nuevo, destino);
		}
		asignacion_recursivo(actual->siguiente, nuevo, destino);
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
	}else if(mesa->raiz == destino){
		Guardando_Nodo(mesa->raiz, nuevo,int direccion);
	}else{
      	asignacion_recursivo(mesa->raiz->anterior, nuevo, destino, direccion);
		asignacion_recursivo(mesa->raiz, nuevo, destino, direccion);
	}
}	
/**
 * aqui creo la lista con los nodos libres
 **/
void ingresar_Lista(Lista *lista, Nodo* Nodo){

}
void Buscando_fichas_disponibles(){

}

Lista *Fichas_Libres(Lista* lista, Mesa *mesa){

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