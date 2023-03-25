#include <stdio.h>
#include "grafo_la.h"

int main(){
 
   GrafoLA * grafo = criaGrafoLA(6);
   
   insereArestaGrafoLA(grafo, 0, 3);
   insereArestaGrafoLA(grafo, 0, 1);

   insereArestaGrafoLA(grafo, 1, 4);
   insereArestaGrafoLA(grafo, 1, 2);

   insereArestaGrafoLA(grafo, 2, 5);
   insereArestaGrafoLA(grafo, 2, 4);
   
   insereArestaGrafoLA(grafo, 3, 1);

   insereArestaGrafoLA(grafo, 4, 3);

   insereArestaGrafoLA(grafo, 5, 4);

   DFSGrafoLA(grafo, 0);
   

   printf("Antes\n");
   imprimeGrafoLA(grafo);
   
   removeArestaGrafoLA(grafo, 1, 2);

   printf("Depois\n");

   DFSGrafoLA(grafo, 0);

   imprimeGrafoLA(grafo);

   printf("Caminho: %d\n", haCaminhoGrafoLA(grafo, 0, 5));
   
   destroiGrafoLA(grafo);

   return 0;
}
