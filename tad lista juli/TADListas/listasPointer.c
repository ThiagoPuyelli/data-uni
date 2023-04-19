#include <stdio.h>
#include <stdlib.h>
#include "listas.h"

static const int MAXIMO = 100;

struct Nodo{
    TipoElemento datos;
    struct Nodo *siguiente;
};

struct ListaRep{
    struct Nodo *inicio;
    int cantidad;
};

struct IteradorRep{
    struct Nodo *posicionActual;
};

//Objetivo: Crea la lista vacía. Retorna el puntero a la misma.
Lista l_crear(){
    Lista lista = (Lista) malloc(sizeof(struct ListaRep));
    lista -> inicio = NULL;
    lista -> cantidad = 0;
    return lista;
}

//Objetivo: determinar si la lista esta vacía. Retorna “true” cuando esto sucede, caso contrario retorna “False”. 
bool l_es_vacia (Lista lista){
    return (lista -> cantidad == 0);
}

//Objetivo: determinar si la lista esta llena. Retorna “true” cuando esto sucede, caso contrario retorna “False”. 
bool l_es_llena(Lista lista){
    return (lista -> cantidad == MAXIMO);
}

//Objetivo: determinar la cantidad de elementos de la lista.
int l_longitud(Lista lista){
    return (lista -> cantidad);
}

//Objetivo: Agrega un elemento al final de la lista, incrementando la cantidad de elementos de la misma.
void l_agregar(Lista lista, TipoElemento elemento){
    if (!l_es_llena(lista)){
        struct Nodo *nuevo_nodo = malloc(sizeof(struct Nodo)); //Nuevo Nodo
        nuevo_nodo -> datos = elemento; //Le asignamos los datos de tipo elemento que recibe el proceso.
        nuevo_nodo -> siguiente = NULL; //Dado que lo vamos a agregar como ultimo elemento, su siguiente debe apuntar a Null.

        if (l_es_vacia(lista)){ //Si la lista es una lista vacia, asigno al comienzo de esta el nuevo nodo.
            lista -> inicio = nuevo_nodo;
        }
        else{
            struct Nodo *Aux = lista -> inicio; //Nodo Auxiliar.
            while (Aux -> siguiente != NULL){ //Mientras el puntero a siguiente de Nodo sea distinto a Null implica que no llegamos al ultimo elemento de la lista.
                Aux = Aux -> siguiente; //Asignamos a Aux el siguiente de Aux.
            }
            Aux -> siguiente = nuevo_nodo; //Aqui ya tenemos el puntero del ultimo elemento de la lista, por tanto, asignamos como siguiente de este el nuevo nodo.
        }
        lista -> cantidad++; //Aumentamos cantidad, pues tenemos un elemento mas en la lista.
    }
}

//Objetivo: Borra un elemento de lista. Recibe como parámetro la lista y la clave a borrar. 
//En caso de tener claves repetidas borrará todas las ocurrencias.
void l_borrar(Lista lista, int clave){
    if (!l_es_vacia(lista)){
        struct Nodo *nuevo_nodo = lista -> inicio;
        while (nuevo_nodo != NULL && nuevo_nodo -> datos -> clave == clave){
            lista -> inicio = nuevo_nodo -> siguiente;
            free(nuevo_nodo); 
            lista -> cantidad--;
            nuevo_nodo = lista -> inicio;
        }
        
        while (nuevo_nodo != NULL && nuevo_nodo -> siguiente != NULL){
            
            if (nuevo_nodo -> siguiente -> datos -> clave == clave){ //Si la clave del siguiente nodo es igual a la clave a borrar.
                struct Nodo *Temp2 = nuevo_nodo -> siguiente; //Nodo auxiliar. 
                nuevo_nodo -> siguiente = Temp2 -> siguiente;
                lista -> cantidad--;
                free(Temp2);
            }
            else{
                nuevo_nodo = nuevo_nodo -> siguiente;
            }
        }
    }
}

//Objetivo: Busca un elemento en la lista recorriéndola. Si hay repetidos retorna la primer ocurrencia.
//Si la clave a buscar no existe retorna la constante “NULL”.
TipoElemento l_buscar(Lista lista, int clave){
    if (!l_es_vacia(lista)){
        struct Nodo *Aux = lista -> inicio;
        while (Aux != NULL){
            if (Aux -> datos -> clave == clave){
                return Aux -> datos;
            }
            else{
                Aux = Aux -> siguiente;
            }
        }
        return NULL;
    }
}

//Objetivo: Inserta un elemento en las posición “pos” dentro de la lista. Incrementa la cantidad.
void l_insertar(Lista lista, TipoElemento elemento, int pos){
    if (!l_es_llena(lista)){
        if (pos <= l_longitud(lista)){    
            struct Nodo *nuevo_nodo = malloc(sizeof(struct Nodo)); //Nuevo Nodo
            nuevo_nodo -> datos = elemento;
            
            if (pos == 1){ //Si la pos. ordinal es la primera
                nuevo_nodo -> siguiente = lista -> inicio; //El siguiente de nuevo nodo es el inicio de la lista.
                lista -> inicio = nuevo_nodo; //El inicio de la lista es nuevo nodo.
            }
            else{
                struct Nodo *Aux = lista -> inicio; //Nodo Auxiliar que es situada al comienzo de la lista.
                for (int i = 0; i < pos -2; i++){ //Recorremos hasta pararnos en la posicion anterior del espacio donde debemos insertar el nuevo nodo.
                    Aux = Aux -> siguiente; 
                }
                nuevo_nodo -> siguiente = Aux ->siguiente; //El siguiente de nuevo nodo es el siguiente de Aux, el cual es justamente el posterior a la posicion donde queremos insertar.
                Aux -> siguiente = nuevo_nodo; //El siguiente de Aux ahora es nuevo nodo.
            }
            lista -> cantidad++; //Incrementamos cantidad.
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
        struct Nodo *nuevo_nodo = lista -> inicio;
        if (1 <= pos && pos <= l_longitud(lista)){

            if (pos == 1){
                lista -> inicio = nuevo_nodo -> siguiente;
                free(nuevo_nodo);
            }
            else{
                for (int i = 0; i < pos -2; i++){
                    nuevo_nodo = nuevo_nodo -> siguiente;
                }
                struct Nodo *Aux = nuevo_nodo -> siguiente;
                nuevo_nodo -> siguiente = Aux -> siguiente;
                free(Aux);
            }
            lista -> cantidad--;
        }
    }
}

//Objetivo: retorna el elemento (dato) de la posición “pos” recibida como parámetro.
TipoElemento l_recuperar(Lista lista, int pos){
    if (!l_es_vacia(lista)){
        if (pos <= l_longitud(lista)){
            struct Nodo *Aux = lista -> inicio;
            for (int i = 0; i < pos -1; i++){
                Aux = Aux -> siguiente;
            }
            return Aux -> datos;
        }
    }
}

//Objetivo: Muestra las claves de lista en la pantalla.
void l_mostrarLista(Lista lista){
    struct Nodo *Aux = lista -> inicio;
    printf("Claves de la lista: ");
    while (Aux != NULL){
        printf("%i ", Aux -> datos -> clave);
        Aux = Aux -> siguiente;
    }
    printf("\n");
}

//Objetivo: Inicializa el iterador para poder hacer un recorrido de la lista.
Iterador iterador(Lista lista){
    Iterador iterador = (Iterador) malloc(sizeof(struct IteradorRep)); 
    iterador -> posicionActual = lista -> inicio;
    return iterador;
}

//Objetivo: Retorna “true” mientras existen mas elementos por recorrer de la lista. Caso contrario retorna “false”.
bool hay_siguiente(Iterador iterador){
    return (iterador -> posicionActual != NULL);
}

//Objetivo: Retorna el próximo elemento de la lista a recorrer.
TipoElemento siguiente(Iterador iterador){
    TipoElemento actual = iterador -> posicionActual -> datos;
    iterador -> posicionActual = iterador -> posicionActual -> siguiente;
    return actual; 
}