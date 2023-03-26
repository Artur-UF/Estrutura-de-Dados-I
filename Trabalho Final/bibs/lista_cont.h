#ifndef _LISTA_CONT_H_
#define _LISTA_CONT_H_
#include "paciencia.h"

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

// Funcao que resgata um nodo de uma posicao de uma lista
Info buscaPosListaCont(ListaCont lista, int pos);

// Funcao que resgata um nodo com uma informacao de uma lista
//Info buscaInfoListaCont(ListaCont lista, int chave);

// Funcao que imprime todos os nodos de uma lista
void imprimeListaCont(ListaCont lista);

/*
Recebe um ponteiro para uma lista na qual vamos copiar de maneira inversa o conteúdo
de outra lista
*/
void inverteListaCont(ListaCont listaA, ListaCont *listaB);

//Busca por chave qual Info será removida da lista e retorna a mesma info
//Info removeInfoListaCont(ListaCont *lista, int chave);

// Concatena duas listas
int concatenaListaCont(ListaCont *listaA, ListaCont listaB);

#endif
