#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "listas.h"
//#include "listasPointer.c"
#include "listasPunteros.c"
//#include "listasArray.c"
#include "tipo_elemento.h"
#include "tipo_elemento.c"
#include "ValidacionEj5.c"
#include "ValidacionGradoPunto5.c"

// //*Generar un algoritmo que guarde en una lista enlazada los coeficientes de un polinomio.
// Realizar una función que dada la lista de coeficientes y un cierto valor de “X” nos devuelva
// el valor del polinomio para ese punto.
void polinomio(Lista coeficientes, int grado, double x, Lista resultados);
Lista calcularEnRango(Lista coeficientes, int grado, double x_min, double x_max, double intervalo, Lista resultados);
Lista crearLista(int grado);

Lista calcularEnRango(Lista coeficientes, int grado, double x_min, double x_max, double intervalo, Lista resultados){
    if (x_min > x_max) {
        return resultados;
    } else if(x_min==x_max){
        polinomio(coeficientes, grado, x_max, resultados);
        return resultados; 
    }    
    else{
        polinomio(coeficientes, grado, x_min, resultados);
        calcularEnRango(coeficientes, grado, x_min+intervalo, x_max, intervalo, resultados);
    }
}

Lista crearLista(int grado){
    Lista coeficientes = l_crear();
    double coefGrado;
    TipoElemento te;
    int salvoGrado = grado;
    for (int i = 0; grado >= 0; grado--){
        do{
            printf("Ingrese coeficiente del grado %i (Real, de -1000 a 1000): ", grado);
            pedirNumeroPunto5TP2(&coefGrado);
            if(coefGrado<-1000||coefGrado>1000){
                printf("Valor fuera de rango.\n");
            }
        } while (coefGrado<-1000||coefGrado>1000);
        
        double* valor = (double*)malloc(sizeof(double)); // crear un nuevo objeto double en memoria dinámica
        *valor = coefGrado; // asignar el coeficiente al objeto double
        te = te_crear_con_valor(grado, valor); // asignar la dirección de memoria del objeto double al campo valor de TipoElemento
        l_agregar(coeficientes, te);
    }
    return coeficientes;
}


void polinomio(Lista coeficientes, int grado, double x, Lista resultados){
    TipoElemento te;
    Iterador ite = iterador(coeficientes);
    double resultado=0;
    while (hay_siguiente(ite) && grado >= 0){
        te = siguiente(ite); //Consigo en te el primer nodo con valores
        double potencia = pow(x, grado); //Calculo x elevado al grado y ese resultado se almacena en potencia
        double* rescata_valor = ((double*) te->valor); //tomo el valor de te el cual es el coeficiente de te actual
        resultado += potencia * (*rescata_valor); //Hago la multiplicacion del coeficiente por el resultado de la potencia y se lo sumo a resultado
        grado--;
    }
    double * resultadoPuntero = (double *) malloc(sizeof(double));
    *resultadoPuntero = resultado;
    TipoElemento res = te_crear_con_valor(1, resultadoPuntero);
    l_agregar(resultados, res);
}


int main(){
    int grado;
    double x_min, x_max, intervalo;

    do{
        printf("Ingrese el grado que tendra el polinomio (Entero, mayor o igual que 0 y menor o igual a 100): ");
        pedirNumeroGrado(&grado);
        if(grado<0){
            printf("El grado no puede ser negativo.\n");
        }
        else if (grado>100){
            printf("El grado no puede ser mayor a 100\n");
        }
        
    } while (grado<0 || grado>100);

    Lista coeficientes=crearLista(grado);

    do{
        printf("Ingrese valor minimo de x para el polinomio (Real, de -1000 a 1000): ");
        pedirNumeroPunto5TP2(&x_min);
        if(x_min<-1000 || x_min>1000){
            printf("Valor fuera de rango.\n");
        }
    }while(x_min<-1000 || x_min>1000);

    do{
        printf("Ingrese valor maximo de x para el polinomio (Real, de -1000 a 1000): ");
        pedirNumeroPunto5TP2(&x_max);
        if(x_max<-1000 || x_max>1000){
            printf("Valor fuera de rango.\n");
        }
    } while (x_max<-1000 || x_max>1000);
    
    while(x_min>x_max){
        printf("El x maximo tiene que ser mayor o igual que el x minimo.\n");
        printf("Ingrese valor minimo de x para el polinomio:");
        pedirNumeroPunto5TP2(&x_max);
    }

    do{
        printf("Ingrese intervalo para el polinomio (Real, mayor que 0 y menor al rango): ");
        pedirNumeroPunto5TP2(&intervalo);
        if(intervalo<=0){
            printf("El intervalo tiene que ser mayor que 0.\n");
        }
        else if(intervalo > (x_max - x_min)){
            printf("El intervalo tiene que ser menor que el rango.\n");
        }
    } while (intervalo<=0 || intervalo > (x_max - x_min));

    Lista resultados = l_crear();
    resultados = calcularEnRango(coeficientes, grado, x_min, x_max, intervalo, resultados);
    Iterador iteRes = iterador(resultados);
    
    double intActual = x_min;
    while (hay_siguiente(iteRes)) {
      double * valorActual = siguiente(iteRes) -> valor;
      printf("El resultado del polinomio f(%.2f) es: %.2f \n", intActual, *valorActual);
      intActual += intervalo;
    }
    free(resultados);
    free(coeficientes);
    
    return 0;
}