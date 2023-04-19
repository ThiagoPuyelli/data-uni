#include <stdio.h>
#include <stdlib.h>
#include "listas.h"
#include "listasPunteros.c"
//#include "listasCursores.c"
//#include "listasArray.c"
#include "tipo_elemento.c"
#include "stdbool.h"
#include "Validacion.c"
#include <time.h>

Lista carga(Lista lista, int cantidad){
    TipoElemento X;
    srand(time(NULL));
    for (int i = 0; i < cantidad; i++){
        int n_random = rand() % 15; 
        X = te_crear(n_random);
        l_agregar(lista, X);   
    }
    return lista;
}

void menor(Lista lista){
    if (l_es_vacia(lista) != true){
        TipoElemento minimo = l_recuperar(lista,1); 
        TipoElemento inicio;
        int pos = 1;
        int pos_menor = 1;
        Iterador ite = iterador(lista);
        while (hay_siguiente(ite)){
          inicio = siguiente(ite);
          if (minimo -> clave > inicio -> clave) {
            minimo = inicio;
            pos_menor = pos;
          }
          pos++;
        }
        printf("el menor es : %i ",minimo->clave);
        printf("y esta en la posicion: %i\n",pos_menor);
    }
}

void maximo(Lista lista){
    if (l_es_vacia(lista) != true){
        TipoElemento mayor = l_recuperar(lista,1); 
        TipoElemento actual;
        int rep = 1;
        int bandera = 1;
        Iterador ite = iterador(lista);
        while (hay_siguiente(ite)){
          actual = siguiente(ite);
          if (mayor -> clave < actual -> clave) {
            mayor = actual;
            rep = 1;
          } else if (mayor -> clave == actual -> clave && bandera > 1) {
            rep++;
          }
          bandera++;
        }
        printf("el mayor es : %i ",mayor->clave);
        printf("repeticiones: %i\n",rep);
    }
}

void promedio(Lista lista, float suma, int cantidad){
    if (cantidad > l_longitud(lista)){
        float promedio = suma / (cantidad - 1);
        printf("\nel promedio es %.2f",promedio);
    }
    else{
        TipoElemento X = l_recuperar(lista, cantidad);
        suma = suma + (float) X -> clave;
        promedio(lista, suma, cantidad + 1);
    }
}

Lista escalar(Lista lista, int escalar){
    if (!l_es_vacia(lista)){
        Lista nueva_lista = l_crear();
        Iterador ite = iterador(lista);
        while (hay_siguiente(ite)){
            TipoElemento X = siguiente(ite);
            if (X -> clave % escalar == 0){
                l_agregar(nueva_lista, X);
            }
        }
        return nueva_lista;
    }
}

int main(){
    Lista list = l_crear();
    printf("Elija cuantas claves se generaran aleatoriamente: ");
    int cant;
    pedirNumero(&cant);
    while (cant > 100 || cant < 0) {
      printf("Entre 0 y 100 elementos, elige un numero valido:");
      pedirNumero(&cant);
    }
    carga(list, cant);
    printf("Lista generada: ");
    l_mostrarLista(list);
    
    maximo(list);
    menor(list);
    promedio(list, 0, 1);
    
    Lista list2 = escalar(list, 2);
    printf("\n \n");
    printf("Lista de multiplos \n");
    l_mostrarLista(list2);
}