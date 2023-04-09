#ifndef _DEFS_H_
#define _DEFS_H_
#include "raylib.h"

#define SCREENWIDTH 1500
#define SCREENHEIGHT 900


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

#endif
