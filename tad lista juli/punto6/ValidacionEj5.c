#include<stdio.h>
#include<ctype.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

#define MAXIMO 50
bool convertirCadenaEnteroPunto5TP2(char *cadena, double *numero, int largo);
bool pedirNumeroPunto5TP2(double *numero);

bool convertirCadenaEnteroPunto5TP2(char *cadena, double *numero, int largo)
{
	int i = 0;
	cadena[strlen(cadena)]='\0'; //quito el \n puesto por el fgets en la ultima linea
	if(strlen(cadena)>MAXIMO){
		return false;
	}
	//Compruebo que no halla espacios en blanco
	while (isspace(cadena[i])) 
	{
		i++;
	}
	
	//Ahora controlo si el largo de la cadena es igual a i, ya que si lo es, hablamos de una cadena vacía
	if (largo == i)
	{
		return false;
	}
	
	char cadenaNueva[MAXIMO]; //En este nueva cadena se irán copiando los digitos numéricos uno por uno.
	int indiceNuevo = 0; //Este índice va de la mano con la nueva cadena
	
	//Controlo si el numero es negativo
	if(cadena[i]=='.'){
		return false;
	}

	if (cadena[i] == '-') //Si esta condición se cumple, quiere decir que el número que se está validando es negativo
	{
		cadenaNueva[indiceNuevo] = '-';
		indiceNuevo++;
		i++;
		
		if (!isdigit(cadena[i])) return false;
	}
	
	//Se leen los dígitos Uno por uno
	int contadorPuntos=0;
	while ( i < largo && !isspace(cadena[i]))
	{	
		if(cadena[i]=='.'){
			contadorPuntos++;
		}
		if((!(((cadena[i]>=48) && (cadena[i]<=57)) || (cadena[i]=='.')))||contadorPuntos>1){ //Si no está entre los digitos ascii de 0 a 9 tira mensaje de error
            printf("Entrada invalida, ingrese nuevamente: \n");
            return false;
            }
		cadenaNueva[indiceNuevo] = cadena[i];
		indiceNuevo++;
		i++;
	}
	
	//Una vez cargados los dígitos a la nueva Cadena, se agrega el carácter '\0' al final de esta, indicando que no hay más carácteres en esta
	cadenaNueva[indiceNuevo] = '\0';
	
	//Se termina de recorrer el string
	while (isspace(cadena[i]))
	{
		i++;
	}
	
	// Si hay mas para recorrer y no son blancos, el string contiene otros caracteres.
    if (cadena[i] != '\0') 
	{
		return false;	
	}
    
    // Convierto el string a un entero.
    *numero = atof(cadenaNueva);
    
    return true;
	
}

bool pedirNumeroPunto5TP2(double *numero)
{
	bool conversionCorrecta = true;
	do {
		char cadenaNum[MAXIMO];
		printf("");
		fgets(cadenaNum, MAXIMO, stdin);
		conversionCorrecta = convertirCadenaEnteroPunto5TP2(cadenaNum, numero, MAXIMO);
		fflush(stdin);
		if(!conversionCorrecta){
			printf("Entrada invalida, ingrese nuevamente: ");
		}
	} while (conversionCorrecta == false);
	return conversionCorrecta;
}