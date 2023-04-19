#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "listas.h"
#include "listasArray.c"
//#include "listasCursor.c"
//#include "listasArray.c"
#include "tipo_elemento.h"
#include "tipo_elemento.c"
#include "Validacion.c"

/*Dadas dos listas L1 y L2, se pide compararlas siempre en el sentido L1L2. Por lo tanto
puede suceder que: L1 > L2, L1 = L2 o L1 < L2. La forma de obtener la comparación es por
la clave, posición a posición, donde si L1 tiene más cantidad de claves mayores que L2 se
considera L1 > L2, por el contrario se considera L1 < L2, o de lo contrario L1 será igual a L2.
Determinar la complejidad algorítmica de la solución empleada. */

//A fines de conseguir el algoritmo, voy a hacer que las listas se carguen con valores random,
//Luego habra que implementar la carga manual.
Lista carga(Lista lista){
    TipoElemento X;
    srand(time(NULL));
    for (int i = 0; i < 4; i++){
        int n_random = rand() % 10; 
        X = te_crear(n_random);
        l_agregar(lista, X);   
    }
    return lista;
}

void comparacion(Lista lista1, Lista lista2){
    TipoElemento X;
    TipoElemento Y;
    //Iterador ite = iterador(lista1); //Uso lista1 para iterar dado que ya verifique que ambas listas son iguales en cuanto a cantidad de elementos.
    int l1 = 0, l2 = 0;
    for (int i = 1; i <= l_longitud(lista1); i++){
        X = l_recuperar(lista1, i);
        Y = l_recuperar(lista2, i);
        if (X -> clave > Y -> clave) l1++;
        else if (X -> clave < Y -> clave) l2++;
        else{
            l1++; l2++;}
    }

    if (l1 > l2){
        printf("L1 > L2");
    }
    else if (l1 < l2){
        printf("L1 < L2");
    }
    else{
        printf("L1 = L2");
    }
}

int main(){
    Lista lista1;
    Lista lista2;
    lista1 = l_crear();
    lista2 = l_crear();

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

    comparacion(lista1, lista2);
}