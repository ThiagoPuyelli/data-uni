#include <stdio.h>
#include <stdlib.h>
#include "listas.h"
#include "listasPunteros.c"
#include "stdbool.h"
#include "tipo_elemento.c"
#include "Validacion.c"

void multiplo(Lista list1,Lista list2){
    Iterador ite1 = iterador(list1); 
    Iterador ite2 = iterador(list2); 
    TipoElemento x = siguiente(ite1);
    TipoElemento x2 = siguiente(ite2);
    int escalar = x2->clave / x->clave;
    int bandera = 1;
    if ((x2->clave % x->clave) == 0){
        while(hay_siguiente(ite1) && hay_siguiente(ite2)){
            x = siguiente(ite1);
            x2 = siguiente(ite2);
            if ((x2->clave / x->clave) != escalar){
                bandera = 0;
            }
            if ((x2->clave % x->clave) != 0){
                printf("no son");
                return;
            }
        }
        if (bandera == 1){
            printf("si son y son por escalar");
        }else{
            printf("si son pero no son escalar");
        }
        
    }else{
        printf("no son");   
    }
    
}

int main(){
    Lista lista1 = l_crear();
    Lista lista2 = l_crear();
    
    int cant;

    do {
      printf("Ingrese cuantos elementos van a tener las listas (maximo 100): ");
      pedirNumero(&cant);
      if (cant > 100 || cant < 0) {
        printf("No aceptamos esa cantidad, entre 1 a 100 tiene que ser\n");
      }
    } while (cant > 100 || cant < 0);
    
    TipoElemento valor;
    int clave;
    int i = 0;
    printf("Ingrese los valores de la primer lista (maximo 9 digitos y caracteres): \n");
    while (i < cant) {
      printf("Ingrese un numero: ");
      pedirNumero(&clave);
      valor = te_crear(clave);
      l_agregar(lista1, valor);
      i++;
    }

    i = 0;
    printf("Ingrese los valores de la segunda lista (maximo 9 digitos y caracteres): \n");
    while (i < cant) {
      printf("Ingrese un numero: ");
      pedirNumero(&clave);
      valor = te_crear(clave);
      l_agregar(lista2, valor);
      i++;
    }

    l_mostrarLista(lista1);
    l_mostrarLista(lista2);
    multiplo(lista1,lista2);
}