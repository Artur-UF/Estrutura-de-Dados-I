/*
A atividade é criar um TAD que respresente e manipule números complexos do tipo a + bi
*/
// $ gcc main.c complex.c

#include <stdio.h>
#include "complex.h"

int main (){

	complex z1, z2, z3;
	
	printf("Insira as componentes do z1:\n");
	scanf("%lf %lf", &z1.a, &z1.b);
	
	printf("Insira as componentes do z2:\n");
	scanf("%lf %lf", &z2.a, &z2.b);
	
	printf("z1 = ");
	imprimez(z1);
	
	printf("z2 = ");
	imprimez(z2);
	
	z3 = somaz(z1, z2);
	
	printf("z1 + z2 = ");
	imprimez(z3);
	
	z3 = subtraz(z1, z2);
	
	printf("z1 - z2 = ");
	imprimez(z3);
	
		
	return 0;
}
