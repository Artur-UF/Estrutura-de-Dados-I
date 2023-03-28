#include "pilha_enc.h"
#include "fila_enc.h"
#include <stdio.h>
#include <stdlib.h>

// Funcao que cria uma pilha
PilhaEnc* criaPilhaEnc(){
   PilhaEnc *pilha = (PilhaEnc*)malloc(sizeof(PilhaEnc));
   if (pilha != NULL) // Idealmente, sempre checar!
      pilha->topo = NULL;
   return pilha;
}

// Funcao que destroi uma pilha
void destroiPilhaEnc(PilhaEnc *pilha){
   NodoPEnc *aux = pilha->topo;
   while(aux != NULL){
       NodoPEnc *tmp = aux->prox;
       free(aux); // Cuidar ordem do free
       aux = tmp;
   }
   free(pilha);
}

// Funcao que insere um elemento na pilha
void empilhaPilhaEnc(PilhaEnc *pilha, Info info){
   NodoPEnc *novo = (NodoPEnc*)malloc(sizeof(NodoPEnc));
   if (novo != NULL){ // Idealmente, sempre checar!
      novo->info = info;
      novo->prox = pilha->topo;
      pilha->topo = novo;
   }
}

// Funcao que remove um elemento da pilha
Info desempilhaPilhaEnc(PilhaEnc* pilha){
   NodoPEnc *aux = pilha->topo; 
   /* Aqui assumimos que desempilha eh 
   chamada apenas se a pilha nao eh vazia */
   Info info = aux->info;
   pilha->topo = aux->prox;
   free(aux);
   return info;
}

// Funcao que determina se uma pilha eh vazia
int vaziaPilhaEnc(PilhaEnc *pilha){
   return (pilha->topo == NULL);
}

// Função que inverte uma pilha
void invertePilhaEnc(PilhaEnc *pilha){
	PilhaEnc *pilhaAux1;
	pilhaAux1 = criaPilhaEnc();

	PilhaEnc *pilhaAux2;
	pilhaAux2 = criaPilhaEnc();
	
	while(!vaziaPilhaEnc(pilha)){
		empilhaPilhaEnc(pilhaAux1, desempilhaPilhaEnc(pilha));
	}

	while(!vaziaPilhaEnc(pilhaAux1)){
		empilhaPilhaEnc(pilhaAux2, desempilhaPilhaEnc(pilhaAux1));
	}
	
	while(!vaziaPilhaEnc(pilhaAux2)){
		empilhaPilhaEnc(pilha, desempilhaPilhaEnc(pilhaAux2));
	}

	destroiPilhaEnc(pilhaAux1);
	destroiPilhaEnc(pilhaAux2);
}


void invertePilhaEncBonus(PilhaEnc *pilha){
	FilaEnc *filaAux;
	filaAux = criaFilaEnc();

	while(!vaziaPilhaEnc(pilha)){
		enfileiraFilaEnc(filaAux, desempilhaPilhaEnc(pilha));
	}

	while(!vaziaFilaEnc(filaAux)){
		empilhaPilhaEnc(pilha, desenfileiraFilaEnc(filaAux));
	}

	destroiFilaEnc(filaAux);
}

// Função que retorna uma cópia de uma fila invertida
PilhaEnc* copiaPilhaEnc(PilhaEnc *pilha){
	PilhaEnc *pilhaCopia;
	pilhaCopia = criaPilhaEnc();

	PilhaEnc *pilhaAux;
	pilhaAux = criaPilhaEnc();
	
	Info infoaux;	

	while(!vaziaPilhaEnc(pilha)){
		printf("Oi\n");
		empilhaPilhaEnc(pilhaAux, desempilhaPilhaEnc(pilha));
 	}
	
	while(!vaziaPilhaEnc(pilhaAux)){
		infoaux = desempilhaPilhaEnc(pilhaAux);
		empilhaPilhaEnc(pilha, infoaux);
		empilhaPilhaEnc(pilhaCopia, infoaux);	
	}

	destroiPilhaEnc(pilhaAux);

	return pilhaCopia;
}




