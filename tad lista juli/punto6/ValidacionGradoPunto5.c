#include<stdio.h>
#include<ctype.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

#define MAXIMO 50
bool convertirCadenaEnteroGrado(char *cadena, int *numero, int largo);
bool pedirNumeroGrado(int *numero);

bool convertirCadenaEnteroGrado(char *cadena, int *numero, int largo)
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
	if (cadena[i] == '-') //Si esta condición se cumple, quiere decir que el número que se está validando es negativo
	{
		cadenaNueva[indiceNuevo] = '-';
		indiceNuevo++;
		i++;
		
		if (!isdigit(cadena[i])) return false;
	}
	
	//Se leen los dígitos Uno por uno
	while ( i < largo && !isspace(cadena[i]))
	{
		if (!isdigit(cadena[i]))
		{
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
    *numero = atoi(cadenaNueva);
    
    return true;
	
}

bool pedirNumeroGrado(int *numero){
	bool conversionCorrecta = true;
	do {
		char cadenaNum[MAXIMO];
		printf("");
		fgets(cadenaNum, MAXIMO, stdin);
		conversionCorrecta = convertirCadenaEnteroGrado(cadenaNum, numero, MAXIMO);
		fflush(stdin);
		if(!conversionCorrecta){
			printf("Entrada invalida, ingrese nuevamente: ");
		}
	} while (conversionCorrecta == false);
	return conversionCorrecta;
}