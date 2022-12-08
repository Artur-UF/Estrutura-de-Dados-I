#include <stdio.h>
#include "complex.h"

complex somaz(complex z1, complex z2){
	complex z3 = {.a = (z1.a + z2.a), .b = (z1.b + z2.b)};
	return z3;
}

complex subtraz(complex z1, complex z2){
	complex z3 = {.a = (z1.a - z2.a), .b = (z1.b - z2.b)};
	return z3;
}

void imprimez(complex z){
	printf("%.1lf + %.1lfi\n", z.a, z.b);
}

