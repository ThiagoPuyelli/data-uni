#include <stdlib.h>
#include <stdio.h>
#include "listasCursores.c"
#include <stdbool.h>
#include "tipo_elemento.c"
#include "Validacion.c"

bool subLista (Lista lista1, Lista lista2);

void main () {
  Lista lista1 = l_crear();
  Lista lista2 = l_crear();
  int cant1;
  int cant2;
  printf("Cuantos elementos tiene la primer lista (entre 1 y 100): ");
  pedirNumero(&cant1);
  while (cant1 > 100 || cant1 < 0) { // Pregunto cuantos elementos tiene la lista, verifico que sea valido
    printf("Entre 1 y 100 elementos, elige un numero valido: ");
    pedirNumero(&cant1);
  }
  int i = 0;
  int clave1;
  int clave2;
  TipoElemento p;
  while (i < cant1) { // Pido cada numero, validando si es correcto
    printf("Ingresa un numero (maximo 9 digitos y caracteres): ");
    pedirNumero(&clave1);
    if (l_buscar(lista1, clave1)) {
      printf("No puede haber numeros repetidos en la lista, envia otro por favor \n");
    } else {
      p = te_crear(clave1);
      l_agregar(lista1, p);
      i++;
    }
  }

  printf("Cuantos elementos tiene la segunda lista (maximo 100): "); // Lo mismo que antes
  pedirNumero(&cant2);
  while (cant2 > 100 || cant2 < 0) {  
    printf("Entre 1 y 100 elementos, elige un numero valido: ");
    pedirNumero(&cant2);
  }

  i = 0;
  while (i < cant2) {
    printf("Ingresa un numero (maximo 9 digitos y caracteres): ");
    pedirNumero(&clave2);
    if (l_buscar(lista2, clave2)) {
      printf("No puede haber numeros repetidos en la lista, envia otro por favor \n");
    } else {
      p = te_crear(clave2);
      l_agregar(lista2, p);
      i++;
    }
  }

  printf("\n");
  printf("La primera lista ingresada \n");
  l_mostrarLista(lista1);
  printf("La segunda lista ingresada \n");
  l_mostrarLista(lista2);
  bool sub;
  if (cant1 > cant2) { // En el caso de que la primera lista sea mayor que la segunda lo paso de esta manera
    sub = subLista(lista1, lista2);
  } else { // Si son iguales de tamaño o la segunda es mas chica, lo paso de esta manera
    sub = subLista(lista2, lista1);
  }
  printf("\n");
  if (sub) {
    if (cant1 > cant2) { // Si se encuentra una sublista, especifico cual es la sublista de cual
      printf("La segunda lista es una sublista de la primera\n");
    } else if (cant1 < cant2) {
      printf("La primera lista es una sublista de la segunda\n");
    } else {
      printf("Las dos listas tienen los mismos elementos es decir que son sublistas entre si\n");
    }
    printf("La complejidad del ejercicio es de O(%d)", cant1 * cant2);
  } else {
    printf("No se encuentra una sublista");
  }

  free(lista1);
  free(lista2);
}

bool subLista (Lista lista1, Lista lista2) {
  Iterador ite1 = iterador(lista1);
  Iterador ite2 = iterador(lista2);

  while (hay_siguiente(ite2)) { // recorro la segunda lista, elijo esta porque es la mas corta
    int clave = siguiente(ite2) -> clave; // saco la clave de cada elemento
    if (!l_buscar(lista1, clave)) { // si no existe dentro de la primera lista, corta el bucle
      return false;
    }
  }

  return true;
}
