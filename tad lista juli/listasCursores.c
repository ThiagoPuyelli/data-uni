#include <stdio.h>
#include <stdlib.h>
#include "listas.h"
#include "tipo_elemento.h"

static const int TAMANIO_MAXIMO = 100;
static const int NULO = -1;

struct Nodo{
    TipoElemento datos;
    int siguiente; //Ahora el puntero es un int.
};

struct ListaRep{
    struct Nodo *cursor; //Puntero al array de nodos.
    int inicio;
    int libre; //Contiene el/los nodo/s libre/s.
    int cantidad;
};

struct IteradorRep{
    Lista lista;
    int posicionActual;
};

Lista l_crear(){
  Lista new_lista = (Lista) malloc(sizeof(struct ListaRep));
  new_lista -> cursor = calloc(TAMANIO_MAXIMO, sizeof(struct Nodo));
  new_lista -> cantidad = 0;
  new_lista -> libre = 0;
  new_lista -> inicio = NULO;

  int i;
  for (i = 0;i < TAMANIO_MAXIMO - 2;i++) {
    new_lista -> cursor[i].siguiente = i + 1;
  }

  new_lista -> cursor[TAMANIO_MAXIMO - 1].siguiente = NULO;
  return new_lista;
}

bool l_es_vacia (Lista lista) { return lista -> cantidad == 0; }
bool l_es_llena (Lista lista) { return lista -> cantidad == TAMANIO_MAXIMO; }
int l_longitud (Lista lista) { return lista -> cantidad; }

void l_agregar (Lista lista, TipoElemento elemento) {
  if (!l_es_llena(lista)) {
    int x = lista -> libre;
    lista -> libre = lista -> cursor[x].siguiente;
    lista -> cursor[x].datos = elemento;
    lista -> cursor[x].siguiente = NULO;
    
    if (lista -> inicio == NULO) {
      lista -> inicio = x;
    } else {
      int i = lista -> inicio;
      while (lista -> cursor[i].siguiente != NULO) {
        i = lista -> cursor[i].siguiente;
      }
      lista -> cursor[i].siguiente = x;
    }
    lista -> cantidad++;
  } 
}

void l_borrar (Lista lista, int clave) {
  if (!l_es_vacia(lista)) {
    int i = lista -> inicio;
    while (i != NULO && lista -> cursor[i].datos -> clave == clave) {
      lista->inicio = lista->cursor[i].siguiente;
      lista->cursor[i].siguiente = lista->libre;
      lista->libre = i;
      lista->cantidad--;
      i = lista->inicio;
    }
    int x = i;
    while (x != NULO && lista -> cursor[x].siguiente != NULO) {
      i = lista -> cursor[x].siguiente;
      if (lista -> cursor[i].datos -> clave == clave) {
        lista -> cursor[x].siguiente = lista -> cursor[i].siguiente;
        lista -> cursor[i].siguiente = lista -> libre;
        lista -> libre = i;
        lista -> cantidad--;
      } else {
        x = lista -> cursor[x].siguiente;
      }
    }
  }

}

TipoElemento l_buscar(Lista lista, int clave){
  if (!l_es_vacia(lista)) {
    int i = lista -> inicio;
    while (lista->cursor[i].siguiente != NULO){
      if (lista->cursor[i].datos->clave == clave){
          return lista->cursor[i].datos;
      }
      i = lista -> cursor[i].siguiente;
    }
    return NULL;
  }
}

void l_insertar(Lista lista, TipoElemento elemento, int pos){
  if (!l_es_llena(lista) || (TAMANIO_MAXIMO - 1 >= pos && pos >= 1)) {
    if (pos <= l_longitud(lista)) {
      int x = lista -> libre;
      lista -> libre = lista -> cursor[x].siguiente;
      lista -> cursor[x].datos = elemento;
      if (pos == 1) {
        lista -> cursor[x].siguiente = lista -> inicio;
        lista -> inicio = x;
      } else {
        int aux = lista -> inicio;
        int i = 0;
        while (i < pos - 2) {
          aux = lista -> cursor[aux].siguiente;
          i++;
        }
        lista -> cursor[x].siguiente = lista -> cursor[aux].siguiente;
        lista -> cursor[aux].siguiente = x;
      }
      lista -> cantidad++;
    } else {
      l_agregar(lista, elemento);
    }
  }
}

void l_eliminar(Lista lista, int pos){
  if (!l_es_vacia(lista) || l_longitud(lista) >= pos >= 1) {
    int i = lista -> inicio;
    if (pos == 1) {
      lista -> inicio = lista -> cursor[i].siguiente; //inicio siguiente 
      lista -> cursor[i].siguiente = lista -> libre;  //el anterior inicio apunta al ultimo libre
      lista -> libre = i; // el nuevo ultimo libre es el inicio anterior
    } else {
      int x;
      for (x = 0;x < pos - 2;x++) {
        i = lista -> cursor[i].siguiente;      
      }
      x = lista -> cursor[i].siguiente;
      lista -> cursor[i].siguiente = lista -> cursor[x].siguiente;
      lista -> cursor[x].siguiente = lista -> libre;
      lista -> libre = x;
    }
    lista -> cantidad--;  // resto cantidad
  }
}

TipoElemento l_recuperar(Lista lista, int pos){
  if (!l_es_vacia(lista) || l_longitud(lista) >= pos >= 1) {
    int i = lista -> inicio;
    int x;
    for (x = 0;x < pos-1;x++) {
      i = lista -> cursor[i].siguiente;
    }
    return lista -> cursor[i].datos;
  }
}

void l_mostrarLista(Lista lista){
    int i = lista->inicio;
    int x;
    printf("Contenido de la lista: ");
    for (x = 0;x<lista->cantidad;x++){
        printf("%d ",lista->cursor[i].datos->clave);
        i = lista->cursor[i].siguiente;
    }
    printf("\n");
}

Iterador iterador(Lista lista){
  Iterador new_iterador = (Iterador) malloc (sizeof(struct IteradorRep));
  new_iterador -> lista = lista;
  new_iterador -> posicionActual = lista -> inicio;
  return new_iterador;
}

bool hay_siguiente (Iterador ite) {
  return ite -> posicionActual != NULO;
}

TipoElemento siguiente(Iterador iterador){
  TipoElemento nuevo = iterador -> lista -> cursor[iterador -> posicionActual].datos;
  iterador -> posicionActual = iterador -> lista -> cursor[iterador -> posicionActual].siguiente;
  return nuevo;
}
