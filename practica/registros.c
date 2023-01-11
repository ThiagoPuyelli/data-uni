#include <stdio.h>

typedef struct {
  char nombre;
  int edad;
  char sexo;
  char estado;
  long salario;
} t_empleado;

int main () {
  int cantidad;
  printf("Ingrese la cantidad de empleados que necesita: ");
  scanf("%d", &cantidad);

  typedef t_empleado t_tabla_empleados[cantidad];
  t_tabla_empleados empleados;
  for (int i = 0;i < cantidad;i++) {
    fflush(stdin);
    printf("Ingrese el nombre del empleado: \n");
    scanf("%s", &(empleados[i].nombre));
    fflush(stdin);
    printf("Ingrese la edad del empleado: \n");
    scanf("%d", &(empleados[i].edad));
    fflush(stdin);
    printf("Ingrese el sexo del empleado: \n");
    scanf("%s", &(empleados[i].sexo));
    fflush(stdin);
    printf("Ingrese el estado del empleado: \n");
    scanf("%s", &(empleados[i].estado));    
    fflush(stdin);
    printf("Ingrese el salario del empleado: \n");
    scanf("%ld", &(empleados[i].salario));
  }

  int masculinos = 0;
  char joven;
  int edadJoven = 100;
  int sumaSalarios = 0;
  for (int i = 0;i < cantidad;i++) {
    sumaSalarios += empleados[i].salario;
    if (edadJoven >= empleados[i].edad) {
      edadJoven = empleados[i].edad;
      joven = empleados[i].nombre;
    }
    if (empleados[i].sexo == 'M') {
      masculinos++;
    }
  }
  printf("Hay %d hombres, el mas joven es %d y tiene %d, la suma de salarios es %d", masculinos, joven, edadJoven, sumaSalarios);
  return 0;
}