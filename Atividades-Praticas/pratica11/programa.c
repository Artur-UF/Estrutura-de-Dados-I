#include <stdio.h>
#include "grafo_pla.h"

int main(){
 
   GrafoPLA * grafo = criaGrafoPLA(6);
   
   insereArestaGrafoPLA(grafo, 0, 3, 8);
   insereArestaGrafoPLA(grafo, 0, 1, 2);

   insereArestaGrafoPLA(grafo, 1, 4, 9);
   insereArestaGrafoPLA(grafo, 1, 2, 1);

   insereArestaGrafoPLA(grafo, 2, 5, 1);
   insereArestaGrafoPLA(grafo, 2, 4, 9);
   
   insereArestaGrafoPLA(grafo, 3, 1, 2);

   insereArestaGrafoPLA(grafo, 4, 3, 5);

   insereArestaGrafoPLA(grafo, 5, 4, 3);

   
   //bellmanFordGrafoPLA(grafo, 0);
   
   dijkstraGrafoPLA(grafo, 0, 4);

   imprimeGrafoPLA(grafo);
   imprimeCaminhoMinimoPesadoGrafoPLA(grafo, 0, 4);

   printf("Peso do caminho: %.2f\n", caminhoMinimoPesadoComParadaGrafoPLA(grafo, 0, 4, 3));

   
   //imprimeGrafoPLA(grafo);
   
   // Melhor implementar uma operacao para acessar essa informacao
   //printf("d(%d,%d) = %.2f\n", 0, 5, grafo->vertices[5].distInicio);

   
   destroiGrafoPLA(grafo);

   return 0;
}
