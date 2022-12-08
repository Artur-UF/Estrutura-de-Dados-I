// compplex.h

typedef struct {
	double a;
	double b;
} complex;

// Função que recebe 2 estruturas complex, soma as duas e retorna o resultado
complex somaz(complex z1, complex z2);

// Função que recebe 2 estruturas complex, soma as duas e retorna o resultado
complex subtraz(complex z1, complex z2);

// Imprime um número complexo na sua forma algébrica
void imprimez(complex z);

