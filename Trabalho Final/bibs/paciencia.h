#ifndef _PACIENCIA_H_
#define _PACIENCIA_H_
#include "raylib.h"

typedef struct{
	int naipe;
	int num;
	int status;
	Rectangle tam;
	Vector2 loc;
} Carta;

typedef Carta Info;

typedef struct nodoLEnc{
   Info info;
   struct nodoLEnc *prox;
} NodoLEnc;

double uniform(double min, double max);

#endif
