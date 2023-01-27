#include "lista_enc_dupla.h"
#include <stdio.h>
#include <stdlib.h>

// Funcao que cria uma lista
ListaEnc2* criaListaEnc2(){
   ListaEnc2 *lista = (ListaEnc2*)malloc(sizeof(ListaEnc2));
   if (lista != NULL) // Idealmente, sempre checar!
      lista->prim = NULL; // Representacao de lista vazia
   return lista;
}

// Funcao que destroi uma lista
void destroiListaEnc2(ListaEnc2 *lista){
   NodoLEnc2 *aux = lista->prim;
   while(aux != NULL){
       NodoLEnc2 *tmp = aux->prox;
       free(aux); // Cuidar ordem do free
       aux = tmp;
   }
   free(lista);
}

// Funcao que imprime todos os nodos de uma lista
void imprimeListaEnc2(ListaEnc2 *lista){
   NodoLEnc2 *aux;
   printf("-----------------------------------------\n");
   for(aux = lista->prim; aux != NULL; aux = aux->prox)
      printf("%d | %s (%s)\n", aux->info.chave,
                               aux->info.nome,
                               aux->info.email);
   printf("-----------------------------------------\n");
}

// Funcao que resgata um nodo com uma informacao de uma lista
NodoLEnc2* buscaInfoListaEnc2(ListaEnc2* lista, int chave){
   NodoLEnc2 *aux;
   for(aux = lista->prim; aux != NULL; aux = aux->prox)
      if (aux->info.chave == chave)
         return aux;
   return NULL; 
}

// Funcao que insere um nodo no inicio de uma lista
int insereInicioListaEnc2(ListaEnc2 *lista, Info info){
   NodoLEnc2 *novo = (NodoLEnc2*)malloc(sizeof(NodoLEnc2));
   if (novo == NULL) // Idealmente, sempre checar!
      return 0; 
   novo->info = info;
   novo->ant = NULL;
   novo->prox = lista->prim;
   if (lista->prim != NULL)
      lista->prim->ant = novo;
   lista->prim = novo;
   lista->tam += 1;
   return 1;
}

// Funcao que remove um nodo com uma informacao de uma lista
int removeInfoListaEnc2(ListaEnc2* lista, int chave){
   NodoLEnc2 *aux = lista->prim; 
   while(aux != NULL && aux->info.chave != chave){
      aux = aux->prox;
   }
   if (aux != NULL){
      if (aux->ant == NULL){
         lista->prim = aux->prox;
         if (aux->prox != NULL)
            aux->prox->ant = NULL;   
      }else{
         aux->ant->prox = aux->prox;
         if (aux->prox != NULL)
            aux->prox->ant = aux->ant;            
      }
      free(aux);
      return 1;
   }
   return 0; // Nao encontrou
}


// Copia a lista
ListaEnc2* velhocopiaListaEnc2(ListaEnc2 *lista){
	ListaEnc2 *copia;
	copia = criaListaEnc2();

	NodoLEnc2 *aux;
	NodoLEnc2 *aux2;

	// Trata uma lista vazia
	if(lista->prim == NULL){
		return copia;
	}

	for(aux = lista->prim; aux != NULL; aux = aux->prox){
		NodoLEnc2 *novo = (NodoLEnc2*)malloc(sizeof(NodoLEnc2));
		if (novo == NULL)
		  return 0;
		
		if(aux->ant = NULL){
			copia->prim = novo;
			novo->ant = NULL;
			novo->prox = NULL;
			novo->info = aux->info;
			printf("Aqui foi\n");
		}else{
			novo->info = aux->info;
		
			novo->ant = aux2;
			aux2->prox = novo;
			novo->prox = NULL;
			printf("Aqui tmb\n");
		}
		aux2 = novo;
	}
	return copia;
}


// outra tentativa
ListaEnc2* copiaListaEnc2(ListaEnc2 *lista){
	ListaEnc2 *copia;
	copia = criaListaEnc2();

	NodoLEnc2 *aux;

	// Trata uma lista vazia
	if(lista->prim == NULL){
		return copia;
	}
	
	// Lista normal
	for(aux = lista->prim; aux->prox != NULL; aux = aux->prox);
	for(; aux != NULL; aux = aux->ant){
		insereInicioListaEnc2(copia, aux->info);	
	}
	return copia;
}

// Insere um nodo em qualquer posição
int inserePosListaEnc2(ListaEnc2 *lista,  Info info, int pos){
	if(pos < 0 || pos > lista->tam){
		return 0;	
	}

	NodoLEnc2 *novo = (NodoLEnc2*)malloc(sizeof(NodoLEnc2));
	novo->info = info;

	NodoLEnc2 *aux;

	for(aux = lista->prim; aux->prox != NULL; aux = aux->prox){
		
	}
	
}






