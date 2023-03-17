#include <stdio.h>
#include <stdlib.h>
#include "grafo_ma.h"

// Funcao auxiliar que retorna o indice de um nodo em um grafo
int buscaNodoGrafoMA(GrafoMA *grafo, int chave);

// Funcao que cria um grafo
GrafoMA* criaGrafoMA(int maxVertices){
   int i, j;
   GrafoMA *grafo = (GrafoMA*)malloc(sizeof(GrafoMA));
   grafo->infos = (Info*)malloc(sizeof(Info)*maxVertices);
   grafo->adjacencias = (int**)malloc(sizeof(int*)*maxVertices);
   for (i = 0; i < maxVertices; i++){
      grafo->adjacencias[i] = (int*)malloc(sizeof(int)*maxVertices);
      for (j = 0; j < maxVertices; j++)
         grafo->adjacencias[i][j] = 0;
   }
   grafo->maxVertices = maxVertices;
   grafo->numVertices = 0;
   return grafo;
}

// Funcao que insere um nodo em um grafo
int insereNodoGrafoMA(GrafoMA *grafo, Info info){
   if (grafo->numVertices < grafo->maxVertices && buscaNodoGrafoMA(grafo, info.chave) == -1){
      grafo->infos[grafo->numVertices] = info;
      grafo->numVertices += 1;
      return 1;
   }
   return 0;
}

// Funcao que insere uma aresta em um grafo
int insereArestaGrafoMA(GrafoMA *grafo, int chave1, int chave2){
	if(chave1 == chave2) return 0;
	if(buscaNodoGrafoMA(grafo, chave1) == -1 || buscaNodoGrafoMA(grafo, chave2) == -1) return 0;
	for(int i = 0; i < grafo->numVertices; ++i){
			if(chave1 == grafo->infos[i].chave){
				for(int j = 0; j < grafo->numVertices; ++j){
					if(chave2 == grafo->infos[j].chave){
						if(grafo->adjacencias[i][j] != 0 || grafo->adjacencias[j][i] != 0) return 0;						
						grafo->adjacencias[i][j] += 1;
						grafo->adjacencias[j][i] += 1;
						printf("aresta entre (%d, %d): %d\n", i, j, grafo->adjacencias[i][j]);
						printf("aresta entre (%d, %d): %d\n", j, i, grafo->adjacencias[j][i]);
						return 1;
					}
				}
			}		

	}	
	return 0;
}

// Funcao que remove uma aresta de um grafo
int removeArestaGrafoMA(GrafoMA *grafo, int chave1, int chave2){
	if(buscaNodoGrafoMA(grafo, chave1) == -1 || buscaNodoGrafoMA(grafo, chave2) == -1) return 0;
	for(int i = 0; i < grafo->numVertices; ++i){
			if(chave1 == grafo->infos[i].chave){
				for(int j = 0; j < grafo->numVertices; ++j){
					if(chave2 == grafo->infos[j].chave){
						if(grafo->adjacencias[i][j] == 0 && grafo->adjacencias[j][i] == 0) return 0;
						grafo->adjacencias[i][j] = 0;
						grafo->adjacencias[j][i] = 0;
						return 1;
					}
				}
			}		

	}
   return 0;
}

// Funcao que imprime nodos e arestas de um grafo
void imprimeGrafoMA(GrafoMA *grafo){
	printf("Vértices:\n");	
	for(int i = 0; i < grafo->numVertices; ++i){
		printf("%d | %s (%s)\n", grafo->infos[i].chave
											 , grafo->infos[i].nome
											 , grafo->infos[i].email);
	}
	printf("Arestas:\n");
	for(int i = 0; i < grafo->numVertices; ++i){
		for(int j = i; j >= 0; --j){
			if(grafo->adjacencias[i][j] == 1){
				//printf("aresta entre (%d, %d): %d\n", grafo->infos[i].chave, grafo->infos[j].chave, grafo->adjacencias[i][j]);
				printf("{%d, %d}\n", grafo->infos[i].chave, grafo->infos[j].chave);
			}
		}
	}
}

// Funcao que destroi um grafo
void destroiGrafoMA(GrafoMA *grafo){
   int i;
   for (i = 0; i < grafo->maxVertices; i++)
      free(grafo->adjacencias[i]);
   free(grafo->adjacencias);
   free(grafo->infos);
   free(grafo);
}

// Funcao auxiliar que retorna o indice de um nodo em um grafo
int buscaNodoGrafoMA(GrafoMA *grafo, int chave){
   int i;
   for (i = 0; i < grafo->numVertices; i++)
      if(grafo->infos[i].chave == chave)
         return i;
   return -1;
}

