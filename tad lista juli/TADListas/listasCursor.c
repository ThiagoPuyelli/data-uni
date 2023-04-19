#include <stdio.h>
#include <stdlib.h>
#include "listas.h"

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

//Objetivo: Crea la lista vacía. Retorna el puntero a la misma.
Lista l_crear(){
    Lista n_lista = (Lista) malloc(sizeof(struct ListaRep));
    n_lista -> cursor = calloc(TAMANIO_MAXIMO, sizeof(struct Nodo));
    n_lista -> inicio = NULO;
    n_lista -> cantidad = 0;

    for (int i = 0; i < TAMANIO_MAXIMO - 2; i++){ //Encadena los libres.
        n_lista -> cursor[i].siguiente = i + 1;
    }

    n_lista -> libre = 0; //Con esto quedan todos los nodos como libres.
    n_lista -> inicio = NULO;
    n_lista -> cursor[TAMANIO_MAXIMO - 1].siguiente = NULO;

    return n_lista;
}

//Objetivo: determinar si la lista esta vacía. Retorna “true” cuando esto sucede, caso contrario retorna “False”. 
bool l_es_vacia (Lista lista){
    return (lista -> cantidad == 0);
}

//Objetivo: determinar si la lista esta llena. Retorna “true” cuando esto sucede, caso contrario retorna “False”. 
bool l_es_llena(Lista lista){
    return (lista -> cantidad == TAMANIO_MAXIMO);
}

//Objetivo: determinar la cantidad de elementos de la lista.
int l_longitud(Lista lista){
    return (lista -> cantidad);
}

//Objetivo: Agrega un elemento al final de la lista, incrementando la cantidad de elementos de la misma.
void l_agregar(Lista lista, TipoElemento elemento){
    if (!l_es_llena(lista)){
        int x;
        x = lista -> libre;
        lista -> libre = lista -> cursor[x].siguiente;
        lista -> cursor[x].datos = elemento;
        lista -> cursor[x].siguiente = NULO; //Esto porque sera el ultimo elemento de la lista.

        if (lista -> inicio == NULO){ //Si la lista esta vacia
            lista -> inicio = x; //Se agrega el nodo x al comienzo de esta.
        }
        else{
            int i = lista -> inicio;
            while (lista -> cursor[i].siguiente != NULO){ //Recorremos hasta que el siguiente de un elemento sea NULO.
                i = lista -> cursor[i].siguiente;
            }
            lista -> cursor[i].siguiente = x; //Agregramos el nodo x como siguiente del ultimo.
        }
        lista -> cantidad++; //Incrementa cantidad.
    }
}

//Objetivo: Borra un elemento de lista. Recibe como parámetro la lista y la clave a borrar. 
//En caso de tener claves repetidas borrará todas las ocurrencias.
void l_borrar(Lista lista, int clave){
    if (!l_es_vacia(lista)){
        int p;
        int q = lista -> inicio;
        while (q != NULO && lista -> cursor[q].datos->clave == clave){
            p = q;
            lista -> inicio = lista -> cursor[q].siguiente; //pasa el inicio al siguiente
            lista -> cursor[p].siguiente = lista -> libre;
            lista -> libre = p;
            lista -> cantidad--;
            q = lista -> inicio;
        }
        
        q = lista -> inicio;
        while (q != NULO && lista -> cursor[q].siguiente != NULO){
            p = lista -> cursor[q].siguiente;
            if (lista -> cursor[p].datos->clave == clave){
                //p = lista -> cursor[q].siguiente;
                lista -> cursor[q].siguiente = lista -> cursor[p].siguiente;
                lista -> cursor[p].siguiente = lista -> libre;
                lista -> libre = p;
                lista -> cantidad--;
            }
            else{
                q = lista -> cursor[q].siguiente;
            }
        }
    }
}

//Objetivo: Busca un elemento en la lista recorriéndola. Si hay repetidos retorna la primer ocurrencia.
//Si la clave a buscar no existe retorna la constante “NULL”.
TipoElemento l_buscar(Lista lista, int clave){
    if (!l_es_vacia(lista)){
        int x;
        x = lista -> inicio;
        while (x != NULO){
            
            if (lista -> cursor[x].datos->clave == clave){
                return lista -> cursor[x].datos;
            }

            else{
                x = lista -> cursor[x].siguiente;
            }
        
        }
        return NULL;
    }
}

//Objetivo: Inserta un elemento en las posición “pos” dentro de la lista. Incrementa la cantidad.
void l_insertar(Lista lista, TipoElemento elemento, int pos){
    if (!l_es_llena(lista)){
        if (pos < lista -> cantidad){
            int x;
            x = lista -> libre;
            lista -> libre = lista -> cursor[x].siguiente; //actualizo libre
            lista -> cursor[x].datos = elemento;
        
            if (pos == 1){
                lista -> cursor[x].siguiente = lista -> inicio;
                lista -> inicio = x;
            }
            
            else{
                int Aux = lista -> inicio;
                for (int i = 0; i < pos - 2; i++){
                    Aux = lista -> cursor[Aux].siguiente;
                }
                lista -> cursor[x].siguiente = lista -> cursor[Aux].siguiente;
                lista -> cursor[Aux].siguiente = x;
            }
            lista -> cantidad++;
        }
        else{
            l_agregar(lista, elemento);
        }
    }
}

//Objetivo: Elimina una posición de la lista sin importar el dato que esta en esa posición.
//Se diferencia de la función borrar porque el “borrar” elimina a partir de una clave y borra todas las ocurrencias.
void l_eliminar(Lista lista, int pos){
    if (!l_es_vacia(lista)){
        int p;
        int q = lista -> inicio;
        if (1 <= pos && pos <= l_longitud(lista)){

            if (pos == 1){
                p = q;
                lista -> inicio = lista -> cursor[q].siguiente;
                lista -> cursor[p].siguiente = lista -> libre;
                lista -> libre = p;
            }
            else{
                for (int i = 0; i < pos - 2; i++){
                    q = lista -> cursor[q].siguiente;
                }
                p = lista -> cursor[q].siguiente;
                lista -> cursor[q].siguiente = lista -> cursor[p].siguiente;
                lista -> cursor[lista -> libre].siguiente = p;
                lista -> libre = p;
            }
        lista -> cantidad--;
        }
    }
}

//Objetivo: retorna el elemento (dato) de la posición “pos” recibida como parámetro.
TipoElemento l_recuperar(Lista lista, int pos){
    if (!l_es_vacia(lista)){
        if (pos >= 0 && pos <= l_longitud(lista)){
            int p = lista -> inicio;
            for (int i = 0; i < pos - 1; i++){
                p = lista -> cursor[p].siguiente;
            }
            return lista -> cursor[p].datos;
        }
    }
}

//Objetivo: Muestra las claves de lista en la pantalla.
void l_mostrarLista(Lista lista){
    int p = lista -> inicio;
    printf("Claves de la lista: ");
    while (p != NULO){
        printf("%i ", lista -> cursor[p].datos->clave);
        p = lista -> cursor[p].siguiente;
    }
    printf("\n");
}

//Objetivo: Inicializa el iterador para poder hacer un recorrido de la lista.
Iterador iterador(Lista lista){
    Iterador ite = (Iterador) malloc(sizeof(struct IteradorRep));
    ite -> lista = lista;
    ite -> posicionActual = lista -> inicio;
    return ite;
}

//Objetivo: Retorna “true” mientras existen mas elementos por recorrer de la lista. Caso contrario retorna “false”.
bool hay_siguiente(Iterador iterador){
    return (iterador -> posicionActual != NULO);
}

//Objetivo: Retorna el próximo elemento de la lista a recorrer.
TipoElemento siguiente(Iterador iterador){
    TipoElemento nuevo = iterador -> lista -> cursor[iterador -> posicionActual].datos;
    iterador -> posicionActual = iterador -> lista -> cursor[iterador -> posicionActual].siguiente;
    return nuevo;   
}
