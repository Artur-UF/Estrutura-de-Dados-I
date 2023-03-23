#ifndef _PACIENCIA_H_
#define _PACIENCIA_H_
#include <stdio.h>
#include "raylib.h"
#include "pilha_enc.h"
#include "fila_enc.h"

typedef struct{
	int naipe;
	int num;
	int status;
	Rectangle tam;
	Vector2 loc;
} Info;


ouble uniform(double min, double max);

#endif
