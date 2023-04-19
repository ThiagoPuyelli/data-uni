#include <stdio.h>
#include <stdlib.h>
#include "listas.h"
#include "tipo_elemento.h"

static const int TAMANIO_MAXIMO = 100;

struct Nodo {
  TipoElemento datos;
  struct Nodo * siguiente;
};

struct ListaRep {
  struct Nodo * inicio;
  int cantidad;
};

struct IteradorRep {
  struct Nodo *posicionActual;
};

Lista l_crear () {
  Lista new_list = (Lista) malloc(sizeof(struct ListaRep));
  new_list->cantidad = 0;
  new_list->inicio = NULL;
  return new_list;
}

bool l_es_vacia (Lista lista) {
  return lista->cantidad == 0;
};

bool l_es_llena (Lista lista) {
  return lista->cantidad == TAMANIO_MAXIMO;
};

int l_longitud (Lista lista) {
  return lista->cantidad;
};

void l_agregar (Lista lista, TipoElemento elemento) {
  if (!l_es_llena(lista)) {
    struct Nodo * new_nodo = malloc(sizeof(struct Nodo));
    new_nodo->datos = elemento;
    new_nodo->siguiente = NULL;
    if (lista->cantidad == 0) {
      lista->inicio = new_nodo;
    } else {
      struct Nodo * nodo = lista->inicio;
      while (nodo->siguiente != NULL) {
        nodo = nodo->siguiente;
      }
      nodo->siguiente = new_nodo;
    }
    lista->cantidad++;
  }
};

void l_borrar(Lista lista, int clave) {
  if (!l_es_vacia(lista)) {
    struct Nodo * nodo = lista->inicio;
    while (nodo != NULL && nodo->datos->clave == clave) {
      lista->inicio = nodo->siguiente;
      free(nodo);
      nodo = lista->inicio;
      lista->cantidad--;
    }
    while (nodo != NULL && nodo->siguiente != NULL) {
      if (nodo->siguiente->datos->clave == clave) {
        struct Nodo * temp = nodo->siguiente;
        nodo->siguiente = temp->siguiente;
        free(temp);
        lista->cantidad--;
      } else {
        nodo = nodo->siguiente;
      }
    }
  }
}

TipoElemento l_buscar (Lista lista, int clave) {
  if (!l_es_vacia(lista)) {
    struct Nodo * nodo = lista->inicio;
    
    while (nodo != NULL) {
      if (nodo->datos->clave == clave) {
        return nodo->datos;
      } else {
        nodo = nodo->siguiente;
      }
    }
  }
}

void l_insertar(Lista lista, TipoElemento elemento, int pos){
  if (!l_es_llena(lista)) {
    if (pos <= lista->cantidad) {
      struct Nodo * new_nodo = malloc(sizeof(struct Nodo));
      new_nodo->datos = elemento;
      new_nodo->siguiente = NULL;
    
      if (pos == 1) {
        new_nodo->siguiente = lista->inicio;
        lista->inicio = new_nodo;
      } else {
        int i = 0;
        struct Nodo * nodo = lista->inicio; 
        while (i < pos - 2) {
          nodo = nodo->siguiente;
          i++;
        }
        new_nodo->siguiente = nodo->siguiente;
        nodo->siguiente = new_nodo;
      }
      lista->cantidad++;
    } else {
      l_agregar(lista, elemento);
    }
  }
}

void l_eliminar(Lista lista, int pos){
  if (pos > lista->cantidad) return;
  struct Nodo * nodo = lista->inicio;
  if (pos == 1) {
    lista->inicio = nodo->siguiente;
    free(nodo);
  } else {
    int i = 0;
    while (i < pos - 2) {
      nodo = nodo->siguiente;
      i++;
    }
    struct Nodo * nodoDelete = nodo->siguiente;
    if (nodoDelete->siguiente == NULL) {
      nodo->siguiente = NULL;
    } else {
      nodo->siguiente = nodoDelete->siguiente;
    }
    free(nodoDelete);
  }

  lista->cantidad--;
}

TipoElemento l_recuperar(Lista lista, int pos){
  if (lista->cantidad >= pos) {
    int i = 0;
    struct Nodo * nodo = lista->inicio;
    if (pos > 1) {
      while (i < pos - 1) {
        nodo = nodo->siguiente;
        i++;
      }
    }
    return nodo->datos;
  }
}

void l_mostrarLista(Lista lista){
  if (!l_es_vacia(lista)) {
    struct Nodo * nodo = lista->inicio;
    printf("Contenido de la lista: ");
    while (nodo != NULL) {
      printf("%d ", nodo->datos->clave);
      nodo = nodo->siguiente;
    }
    printf("\n");
  }
}

Iterador iterador(Lista lista) {
  Iterador new_iterador = (Iterador) malloc(sizeof(struct IteradorRep));
  new_iterador->posicionActual = lista->inicio;
  return new_iterador;
}

bool hay_siguiente(Iterador iterador) {
  return iterador->posicionActual != NULL;
}

TipoElemento siguiente (Iterador iterador) {
  TipoElemento actual = iterador->posicionActual->datos;
  iterador->posicionActual = iterador->posicionActual->siguiente;
  return actual;
}