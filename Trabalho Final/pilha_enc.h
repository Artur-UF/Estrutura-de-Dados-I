#ifndef _PILHA_ENC_H_
#define _PILHA_ENC_H_
#include "paciencia.h"

typedef struct{
	int naipe;
	int num;
	int status;
	Rectangle tam;
	Vector2 loc;
} Info;

typedef struct nodoLEnc{
   Info info;
   struct nodoLEnc *prox;
} NodoLEnc;

typedef NodoLEnc NodoPEnc;

typedef struct pilhaEnc{
   NodoPEnc *topo;
   int tamanho;
} PilhaEnc;

// Funcao que cria uma pilha
PilhaEnc* criaPilhaEnc();

// Funcao que destroi uma pilha
void destroiPilhaEnc(PilhaEnc *pilha);

// Funcao que insere um elemento na pilha
void empilhaPilhaEnc(PilhaEnc *pilha, Info info);

// Funcao que remove um elemento da pilha
Info desempilhaPilhaEnc(PilhaEnc *pilha);

// Funcao que determina se uma pilha eh vazia
int vaziaPilhaEnc(PilhaEnc* pilha);

// Função que inverte a pilha
void invertePilhaEnc(PilhaEnc *pilha);
void invertePilhaEncBonus(PilhaEnc *pilha);


#endif
