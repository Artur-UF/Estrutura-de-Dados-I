#include <stdio.h>
#include <stdlib.h>
#include "grafo_la.h"
#include "fila_enc.h"

// Funcao que cria um grafo 
GrafoLA *criaGrafoLA(int numVertices){
   int chave;
   GrafoLA * grafo = (GrafoLA*)malloc(sizeof(GrafoLA));
   grafo->vertices = (NoGrafo*)malloc(sizeof(NoGrafo)*numVertices);
   for (chave = 0; chave < numVertices; chave++)
      grafo->vertices[chave].lista = NULL;
   grafo->numVertices = numVertices;
   return grafo;
}

// Funcao que insere uma aresta em um grafo
void insereArestaGrafoLA(GrafoLA *grafo, int chave1, int chave2){
   ArestaGrafo *arestaAux = (ArestaGrafo*)malloc(sizeof(ArestaGrafo));
   arestaAux->chaveDest = chave2; 
   arestaAux->prox = grafo->vertices[chave1].lista;
   grafo->vertices[chave1].lista = arestaAux;
   // Em grafos nao-direcionados, ha a insercao da aresta simetrica
}

// Funcao que imprime vertices e arcos
void imprimeGrafoLA(GrafoLA *grafo){
   int chave;
   for (chave = 0; chave < grafo->numVertices; chave++){
      printf("%d [%d/%d]\n", chave, grafo->vertices[chave].tEntrada, grafo->vertices[chave].tSaida);
      // Mostra distInicio no resultado do BFS
      // printf("%d [%d/%d] %d\n", chave, grafo->vertices[chave].tEntrada, grafo->vertices[chave].tSaida, grafo->vertices[chave].distInicio); 
   }
   for (chave = 0; chave < grafo->numVertices; chave++){
      for (ArestaGrafo *arestaAux = grafo->vertices[chave].lista; 
           arestaAux != NULL; arestaAux = arestaAux->prox){
           printf("(%d,%d) : %d\n", chave, arestaAux->chaveDest, arestaAux->tipo);
      }     
   }
}

// Funcao que destroi um grafo
void destroiGrafoLA(GrafoLA *grafo){
   int chave;
   for (chave = 0; chave < grafo->numVertices; chave++) {
      ArestaGrafo *arestaAux = grafo->vertices[chave].lista;
      while(arestaAux != NULL){
         ArestaGrafo *arestaTmp = arestaAux->prox;
         free(arestaAux); 
         arestaAux = arestaTmp;
      }
   }
   free(grafo->vertices);
   free(grafo);
}

// Funcao auxiliar para Algs. de Caminhamento
void inicializaCaminhamentoGrafoLA(GrafoLA *grafo){
   int chave;
   grafo->timestamp = 0;
   for (chave = 0; chave < grafo->numVertices; chave++){
      grafo->vertices[chave].cor = BRANCO;
      grafo->vertices[chave].tEntrada = -1; 
      grafo->vertices[chave].tSaida = -1; 
      grafo->vertices[chave].pai = -1; 
   }
   for (chave = 0; chave < grafo->numVertices; chave++)
      for (ArestaGrafo *arestaAux = grafo->vertices[chave].lista; 
           arestaAux != NULL; arestaAux = arestaAux->prox){
           arestaAux->tipo = OUTRA;
      }
}

// Funcao auxiliar recursiva para o Caminhamento em Profundidade
void visitaNodoDFSGrafoLA(GrafoLA *grafo, int chave){
   grafo->vertices[chave].cor = CINZA;
   grafo->vertices[chave].tEntrada = grafo->timestamp++; 
   for(ArestaGrafo *arestaAux = grafo->vertices[chave].lista;
       arestaAux != NULL; arestaAux = arestaAux->prox){
       int chaveAux = arestaAux->chaveDest;
       if(grafo->vertices[chaveAux].cor == BRANCO){
          grafo->vertices[chaveAux].pai = chave; 
          arestaAux->tipo = EXPLORATORIA; 
          visitaNodoDFSGrafoLA(grafo, chaveAux);     
       }
   }
   grafo->vertices[chave].cor = PRETO;
   grafo->vertices[chave].tSaida = grafo->timestamp++; 
}

// Alg. para Caminhamento em Profundidade
void DFSGrafoLA(GrafoLA *grafo, int chaveInicial){
   inicializaCaminhamentoGrafoLA(grafo);
   visitaNodoDFSGrafoLA(grafo, chaveInicial); 
}

// Alg. para Caminhamento em Amplitude
void BFSGrafoLA(GrafoLA *grafo, int chaveInicial){
   inicializaCaminhamentoGrafoLA(grafo);
   FilaEnc *fila = criaFila();
   enfileiraFila(fila, chaveInicial); 
   grafo->vertices[chaveInicial].tEntrada = grafo->timestamp++;
   grafo->vertices[chaveInicial].cor = CINZA;
   grafo->vertices[chaveInicial].distInicio = 0;
   while(!vaziaFila(fila)){
      int chave1 = desenfileiraFila(fila);
      for(ArestaGrafo *arestaAux = grafo->vertices[chave1].lista;
          arestaAux != NULL; arestaAux = arestaAux->prox){
          int chave2 = arestaAux->chaveDest;
          if(grafo->vertices[chave2].cor == BRANCO){
             grafo->vertices[chave2].pai = chave1;
             grafo->vertices[chave2].distInicio = grafo->vertices[chave1].distInicio + 1;
             grafo->vertices[chave2].tEntrada = grafo->timestamp++;
             grafo->vertices[chave2].cor = CINZA;
             arestaAux->tipo = EXPLORATORIA;
             enfileiraFila(fila, chave2); 
          }
      }
      grafo->vertices[chave1].cor = PRETO;
      grafo->vertices[chave1].tSaida = grafo->timestamp++;
   }
   destroiFila(fila);
}


int removeArestaGrafoLA(GrafoLA *grafo, int chOrig, int chDest){
	if(chOrig >= grafo->numVertices || chOrig < 0 || chDest >= grafo->numVertices || chDest < 0) return 0;

	ArestaGrafo *arestaAux0 = grafo->vertices[chOrig].lista;

	if(arestaAux0->chaveDest == chDest){
		grafo->vertices[chOrig].lista = arestaAux0->prox;
		free(arestaAux0);
		return 1;
	}	

	for (ArestaGrafo *arestaAux = grafo->vertices[chOrig].lista->prox; arestaAux != NULL; arestaAux = arestaAux->prox){		
		if(arestaAux->chaveDest == chDest){
			arestaAux0->prox = arestaAux->prox;
			free(arestaAux);
			return 1;
		}
		arestaAux0 = arestaAux;
	}
	return 0;
}


int haCaminhoGrafoLA(GrafoLA *grafo, int chOrig, int chDest){
	if(chOrig >= grafo->numVertices || chOrig < 0 || chDest >= grafo->numVertices || chDest < 0) return 0;

	BFSGrafoLA(grafo, chOrig);

	NoGrafo nodoAux = grafo->vertices[chDest];
	while(nodoAux->pai != grafo->vertices[chOrig] && nodoAux->pai != NULL){
		nodoAux = nodoAux->pai;
	}
	
	if(nodoAux->pai == NULL) return 0;
	if(nodoAux->pai == grafo->vertices[chOrig]) return 1;

}























