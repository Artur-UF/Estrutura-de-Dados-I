#include "lista_enc.h"
#include <stdio.h>
#include <stdlib.h>

// Funcao que cria uma lista
ListaEnc* criaListaEnc(){
   ListaEnc *lista = (ListaEnc*)malloc(sizeof(ListaEnc));
   if (lista != NULL) // Idealmente, sempre checar!
      lista->prim = NULL; // Representacao de lista vazia
   return lista;
}

// Funcao que destroi uma lista
void destroiListaEnc(ListaEnc *lista){
   NodoLEnc *aux = lista->prim;
   while(aux != NULL){
       NodoLEnc *tmp = aux->prox;
       free(aux); // Cuidar ordem do free
       aux = tmp;
   }
   free(lista);
}

// Funcao que imprime todos os nodos de uma lista
void imprimeListaEnc(ListaEnc *lista){
   NodoLEnc *aux;
   printf("-----------------------------------------\n");
   for(aux = lista->prim; aux != NULL; aux = aux->prox)
      printf("%d | %s (%s)\n", aux->info.chave,
                               aux->info.nome,
                               aux->info.email);
   printf("-----------------------------------------\n");
}

// Funcao que insere um nodo no inicio de uma lista
int insereInicioListaEnc(ListaEnc *lista, Info info){
   NodoLEnc *novo = (NodoLEnc*)malloc(sizeof(NodoLEnc));
   if (novo == NULL) // Idealmente, sempre checar!
      return 0;
   novo->info = info;
   novo->prox = lista-> prim;
   lista->prim = novo;
   return 1;
}

// Funcao que resgata um nodo com uma informacao de uma lista
NodoLEnc* buscaInfoListaEnc(ListaEnc* lista, int chave){
   NodoLEnc *aux;
   for(aux = lista->prim; aux != NULL; aux = aux->prox)
      if (aux->info.chave == chave)
         return aux;
   return NULL; 
}

// Funcao que remove um nodo com uma informacao de uma lista
int removeInfoListaEnc(ListaEnc* lista, int chave){
   NodoLEnc* ant = NULL;
   NodoLEnc *aux = lista->prim; 
   while(aux != NULL && aux->info.chave != chave){
      ant = aux;
      aux = aux->prox;
   }
   if (aux != NULL){
      if (ant == NULL)
         lista->prim = aux->prox;
      else
         ant->prox = aux->prox;
      free(aux);
      return 1;
   }
   return 0; // Nao encontrou
}

int concatenaListaEnc(ListaEnc *listaA, ListaEnc *listaB){ // VERIFICAR SE TÁ VAZIA
	int retorno;
	// Se A e B for vazia
	if(listaA->prim == NULL && listaB->prim == NULL){
		return 1;
	}	

	// Se lista A for vazia retorno uma cópia de B em A 
	if(listaA->prim == NULL){
		retorno = insereInicioListaEnc(listaA, listaB->prim->info);
		NodoLEnc *auxB, *fimA = listaA->prim;	
		for(auxB = listaB->prim->prox; auxB != NULL; auxB = auxB->prox){
			NodoLEnc *novo = (NodoLEnc*)malloc(sizeof(NodoLEnc));
			if(novo == NULL) return 0;
			fimA->prox = novo;
			novo->info = auxB->info;
			fimA = novo;
			novo->prox = NULL;
		}
		return 1;
	}

	// Se lista B for vazia não tenho oq concatenar
	if(listaB->prim == NULL){
		return 1;
	}

	// Se nenhuma for vazia eu faço o normal
	NodoLEnc *fimA = listaA->prim;
	NodoLEnc *auxB;

	while(fimA->prox != NULL){
		fimA = fimA->prox;
	}
	for(auxB = listaB->prim; auxB != NULL; auxB = auxB->prox){
		NodoLEnc *novo = (NodoLEnc*)malloc(sizeof(NodoLEnc));
		if(novo == NULL) return 0;
		fimA->prox = novo;
		novo->info = auxB->info;
		fimA = novo;
		novo->prox = NULL;
	}
	return 1;
}



