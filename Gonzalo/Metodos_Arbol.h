#ifndef METODOS_ARBOL_H
#define METODOS_ARBOL_H

void asignacion_recursivo(Nodo *actual, Nodo* nuevo, Nodo *destino){
	if(actual != NULL){
		if(actual == destino){
			if(actual->dato->ficha[0] != actual->dato->ficha[1])
				actual->siguiente = nuevo;
         else if(actual->dato->ficha[0] == actual->dato->ficha[1]){
				if(actual->arriba == NULL)
					actual->arriba = nuevo;
				else if(actual->abajo == NULL)
					actual->abajo = nuevo;
				else if(actual->siguiente == NULL)
					actual->siguiente = nuevo;
			}
		}else{
			asignacion_recursivo(actual->arriba, nuevo, destino);
			asignacion_recursivo(actual->abajo, nuevo, destino);
			asignacion_recursivo(actual->siguiente, nuevo, destino);
		}
	}
}
	
void AgregarNodoArbol(Mesa* mesa, Nodo* nuevo, Nodo *destino){
   Nodo *raiz = mesa->raiz;
 	if(raiz == NULL){
      printf("[ %d | %d ] guardado como raiz\n",nuevo->dato->ficha[0],nuevo->dato->ficha[1]);
		mesa->raiz = nuevo;
	}else if(raiz == destino){
		if(raiz->dato->ficha[0] != raiz->dato->ficha[1]){
			if(raiz->siguiente == NULL)
            printf("[ %d | %d ] guardado como sig f1 != f2\n",nuevo->dato->ficha[0],nuevo->dato->ficha[1]);
				mesa->raiz->siguiente = nuevo;
		}else if(raiz->dato->ficha[0] == raiz->dato->ficha[1]){
			if(raiz->arriba == NULL){
           printf("[ %d | %d ] guardado como arriba f1 0= f2\n",nuevo->dato->ficha[0],nuevo->dato->ficha[1]);
				mesa->raiz->arriba = nuevo;
         }else if(raiz->abajo == NULL){
            printf("[ %d | %d ] guardado como abajo f1 != f2\n",nuevo->dato->ficha[0],nuevo->dato->ficha[1]);
				mesa->raiz->abajo = nuevo;
         }else if(raiz->siguiente == NULL){
             printf("[ %d | %d ] guardado como siguiente f1 != f2\n",nuevo->dato->ficha[0],nuevo->dato->ficha[1]);
				mesa->raiz->siguiente = nuevo;
         }else if(raiz->anterior ==NULL){
            printf("[ %d | %d ] guardado como anterior f1 != f2\n",nuevo->dato->ficha[0],nuevo->dato->ficha[1]);
            mesa->raiz->anterior = nuevo;
         }
		}
	}else{
      asignacion_recursivo(mesa->raiz->anterior, nuevo, destino);
		asignacion_recursivo(mesa->raiz, nuevo, destino);
	}
}	


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
      muestra_Recursivo(m->raiz);
      muestra_Recursivo(m->raiz->anterior);
   }else{
      printf("Mesa vacia\n");
   }
}
#endif