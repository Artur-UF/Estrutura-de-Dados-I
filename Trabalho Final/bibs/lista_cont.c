#include <stdio.h>
#include "lista_cont.h"

// Funcao que cria uma lista
void criaListaCont(ListaCont *lista){
   lista->ini = 0;
   lista->fim = 0;
}

// Funcao que destroi uma lista
void destroiListaCont(ListaCont *lista){
   lista->ini = 0;
   lista->fim = 0;
}

// Funcao que retorna a cardinalidade de uma lista
int tamanhoListaCont(ListaCont lista){
   return lista.fim - lista.ini;  
}

// Funcao que insere um nodo em uma posicao de uma lista
int inserePosListaCont(ListaCont *lista, Info nodo, int pos){
   int indice;
   int tamLista = tamanhoListaCont(*lista);
   
   if (TAM_MAX_LISTA == tamLista) // verifica se a lista esta cheia
      return 0;
      
   if (pos < lista->ini || pos > lista->fim) // verifica se a posicao eh valida
      return 0;

   for (indice = lista->fim-1; indice >= pos; indice--)
      lista->nodos[indice+1] = lista->nodos[indice];
   lista->fim += 1;
   lista->nodos[pos] = nodo;
   
   return 1;
}

// Funcao que remove um nodo em uma posicao de uma lista
int removePosListaCont(ListaCont *lista, int pos){
   int indice;
   
   if (pos < lista->ini || pos >= lista->fim) // verifica se a posicao eh valida
      return 0;

   // Sempre puxa tudo para o comeco
   for (indice = pos; indice < lista->fim; indice++) 
      lista->nodos[indice] = lista->nodos[indice+1];
   lista->fim -= 1;   
   
   return 1;
}

  

