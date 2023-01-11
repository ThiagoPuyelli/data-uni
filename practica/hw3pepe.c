#include <stdio.h>

int sin_lluvias(FILE* fp, int mes){ 
	fp = fopen("datos_lluvia_temp.tsv", "r");
	int d;
	int a;
	int b;
	int c;
	int e;
	int i;
	int v = 1;
	int contador = 0;
	fscanf(fp, "%d %d %d %d %d %d", &d, &i, &a, &b, &c, &e);
    printf("%d %d %d %d %d %d \n", d, i, a, b, c, e);
	while (!feof(fp) && v == 1) {
	  if (i == mes) {
		while (!feof(fp) && i == mes) {
		  contador++;
	      fscanf(fp, "%d %d %d %d %d %d", &d, &i, &a, &b, &c, &e);
		}
		v = 0;
	  }
	  if (v == 1) {
	    fscanf(fp, "%d %d %d %d %d %d", &d, &i, &a, &b, &c, &e);
	  }
	}
	return contador;
}

void dia_mas_frio_mes(FILE* fp, int mes, int* dia, int* temp_minima){ 
  fp = fopen("datos_lluvia_temp.tsv", "r");
  int a;
  int b;
  int c;
  int d;
  int e;
  int f;
  int v = 1;
  int menor = 99;
  fscanf(fp, "%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);
  while (!feof(fp) && v == 1) {
	if (b == mes) {
		while (!feof(fp) && b == mes && v == 1) {
          printf("%d %d", e, menor);
		  if (e < menor) {
			*temp_minima = e;
			*dia = a;
		  }
          fscanf(fp, "%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);
		}
		v = 0;
	  }
	if (v == 1) {
      fscanf(fp, "%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);
	}
  }
}

int main () {
  FILE * fp;
 // int pepe = sin_lluvias (fp, 2);
  int dia;
  int temp = 15;
  dia_mas_frio_mes(fp, 2, &dia, &temp);
  //printf("%d %d", dia, temp);
  return 0;
}