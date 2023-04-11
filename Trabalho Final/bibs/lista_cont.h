#ifndef _LISTA_CONT_H_
#define _LISTA_CONT_H_
#include "definicoes.h"

#define TAM_MAX_LISTA 104

typedef struct{
   int ini;
   int fim;
   Info nodos[TAM_MAX_LISTA];
} ListaCont;

// Funcao que cria uma lista
void criaListaCont(ListaCont *lista);

// Funcao que destroi uma lista
void destroiListaCont(ListaCont *lista);

// Funcao que insere um nodo em uma posicao de uma lista
int inserePosListaCont(ListaCont *lista, Info nodo, int pos);

// Funcao que remove um nodo em uma posicao de uma lista
int removePosListaCont(ListaCont *lista, int pos);

// Funcao que retorna a cardinalidade de uma lista
int tamanhoListaCont(ListaCont lista);

#endif
