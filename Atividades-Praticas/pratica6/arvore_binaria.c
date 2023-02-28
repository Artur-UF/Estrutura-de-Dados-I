#include "arvore_binaria.h"
#include <stdlib.h>
#include <stdio.h>

// Funcao que cria uma arvore
ArvBinaria* criaArvBinaria(){
   ArvBinaria * arv = (ArvBinaria*)malloc(sizeof(ArvBinaria));
   if (arv)
      arv->raiz = NULL;
   return arv;
}

// Funcao auxiliar para imprimir uma arvore
void imprimeNodoArvBinaria(NodoABin *raiz){
   if(raiz != NULL){
      printf("%d | %s (%s)\n", raiz->info.chave,
                               raiz->info.nome,
                               raiz->info.email);
      imprimeNodoArvBinaria(raiz->esq);
      imprimeNodoArvBinaria(raiz->dir);
   }   
}

// Funcao que imprime uma arvore
void imprimeArvBinaria(ArvBinaria *arv){
   printf("-----------------------------------------\n");
   imprimeNodoArvBinaria(arv->raiz);
   printf("-----------------------------------------\n");
}

// Funcao que auxiliar para inserir um elemento na arvore
NodoABin* insereNodoArvBinaria(NodoABin *raiz, Info info){
   if(raiz == NULL){
      raiz = (NodoABin*)malloc(sizeof(NodoABin));
      if(raiz){ 
         raiz->info = info;
         raiz->esq = NULL;
         raiz->dir = NULL;
      }
      return raiz;
   }
   else if(rand()%2) //Escolha arbitraria (?)
      raiz->esq = insereNodoArvBinaria(raiz->esq, info);
   else 
      raiz->dir = insereNodoArvBinaria(raiz->dir, info);
   return raiz;
}

// Funcao que insere um elemento na arvore
void insereArvBinaria(ArvBinaria *arv, Info info){
   arv->raiz = insereNodoArvBinaria(arv->raiz, info);
}

// Funcao auxiliar para buscar uma informacao na arvore
Info buscaInfoNodoArvBinaria(NodoABin *raiz, int chave){
   if (raiz == NULL){
      Info infoAux = {.chave = -1, .nome = "", .email = ""};
      return infoAux;
   }else if (raiz->info.chave == chave) 
      return raiz->info;
   else{
      Info infoAux = buscaInfoNodoArvBinaria(raiz->esq, chave);
      if (infoAux.chave != -1)
        return infoAux;
      else 
        return buscaInfoNodoArvBinaria(raiz->dir, chave);
   }
}

// Funcao que busca uma informacao na arvore
Info buscaInfoArvBinaria(ArvBinaria *arv, int chave){
   return buscaInfoNodoArvBinaria(arv->raiz, chave);
}

// Funcao auxiliar para remover uma informacao da arvore
NodoABin* removeInfoNodoArvBinaria(NodoABin *raiz, int chave){
   if (raiz == NULL)
      return NULL;
   else if (raiz->info.chave == chave){
      if (raiz->esq == NULL && raiz->dir == NULL){
         free(raiz);
         return NULL;
      }
      else
         return raiz;
   }
   else{
      raiz->esq = removeInfoNodoArvBinaria(raiz->esq, chave);
      raiz->dir = removeInfoNodoArvBinaria(raiz->dir, chave);
   }
   return raiz;
}

// Funcao que remove uma informacao da arvore
void removeInfoArvBinaria(ArvBinaria *arv, int chave){
   arv->raiz = removeInfoNodoArvBinaria(arv->raiz, chave);
}

// Funcao auxiliar para destroir uma arvore
void destroiNodoArvBinaria(NodoABin *raiz){
   if(raiz != NULL){
      destroiNodoArvBinaria(raiz->esq);
      destroiNodoArvBinaria(raiz->dir);
      free(raiz);
   }
}

// Funcao que destroi uma arvore
void destroiArvBinaria(ArvBinaria *arv){
   destroiNodoArvBinaria(arv->raiz);
   free(arv);
}


// Funcao auxiliar para imprimir uma arvore
void imprimeNodoIndentado(NodoABin *raiz, int contnivel){
	if(raiz != NULL){
		printf("%d\n", raiz->info.chave);
		
		if(raiz->esq != NULL) contnivel++;	
		
		for(int i = contnivel; i > 0; i--) printf("|");

		imprimeNodoIndentado(raiz->esq, contnivel);

		if(raiz->dir != NULL) contnivel--;

		imprimeNodoIndentado(raiz->dir, contnivel);
	}
/*else{
		printf("N\n");
		for(int i = contnivel+1; i > 0; i--) printf("|");
		
	}*/
}


// Imprime indentada
void imprimeIndentadoArvBinaria(ArvBinaria *arv){
	int contnivel = 0;
	printf("-----------------------------------------\n");
	imprimeNodoIndentado(arv->raiz, contnivel);
	printf("-----------------------------------------\n");	
}





