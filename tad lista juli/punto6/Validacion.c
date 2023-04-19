#include "Validacion.h"

//Funcion que convierta una cadena a un entero en caso de que la cadena ingresada cumpla las características de un entero, y de ser asi, castea dicha cadena a un entero.
//Recibe: el puntero al comienzo de la cadena, el puntero al entero que entrara a la recursiva y un entero que indice el largo maximo de la cadena
//Retorna: un booleano indicando si la cadena es efectivamente o no, una cadena que pueda considerarse un entero.
bool convertirCadenaEntero(char *cadena, int *numero, int largo)
{
	int i = 0;

	if (strlen(cadena) >= MAXIMO){
		printf("El numero es un valor muy alto/bajo.\n");
		return false;
	}
	
	//Compruebo que no halla espacios en blanco
	while (isspace(cadena[i])) {
		i++;
	}
	
	//Ahora controlo si el largo de la cadena es igual a i, ya que si lo es, hablamos de una cadena vacía
	if (largo == i){
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
    
    return true; //Si se llega aqui, implica que la cadena definitivamente es un entero.
	
}

//Proceso que pide el ingreso de una cadena y verifica si esta cumple las caracteristicas para ser un entero.
void pedirNumero(int *numero)
{
	bool conversionCorrecta = true; //Booleano por el cual verificamos si la cadena es o no un entero.
	do {
		char cadenaNum[MAXIMO]; 
		fgets(cadenaNum, MAXIMO, stdin); //Pedimos el ingreso del numero por teclado
		fflush(stdin);
		conversionCorrecta = convertirCadenaEntero(cadenaNum, numero, MAXIMO); //Llama a conversionCorrecta para que verifique si la cadena cumple las condiciones de un entero y de ser asi lo castea.
		if (conversionCorrecta == false)
		{
			printf("Entrada invalida, asegurese de poner numeros validos: ");
		}
	} while (conversionCorrecta == false); //Condicion de corte.
}