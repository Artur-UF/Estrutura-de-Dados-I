// COMENTE SEU CÓDIGO

#include <stdio.h>
#include <string.h>
#include "fila_enc.h"
#include "pilha_enc.h"

int main(){
   PilhaEnc *pilha;
   pilha = criaPilhaEnc();

   PilhaEnc *pilhacopia;
   pilhacopia = criaPilhaEnc();

   FilaEnc *fila;
   fila = criaFilaEnc();

   FilaEnc *filaInv;
   filaInv = criaFilaEnc();
   
   Info info1 = {1, "Fulano de Tal", "fulano@email.com"};
   Info info2 = {2, "Beltrana de Tal", "beltrana@email.com"};
   Info info3 = {3, "Cicrano de Tal", "cicrano@email.com"};
   Info info4 = {4, "Ciclana de Tal", "ciclana@email.com"};
   Info info5 = {5, "Ciclano de Tal", "ciclano@email.com"};
   Info infoAux;
     
   empilhaPilhaEnc(pilha, info1); 
   empilhaPilhaEnc(pilha, info2); 
   empilhaPilhaEnc(pilha, info3); 
   empilhaPilhaEnc(pilha, info4); 
   empilhaPilhaEnc(pilha, info5);


   pilhacopia = copiaPilhaEnc(pilha);
   
   printf("\nPilha original.\n");   
   while (!vaziaPilhaEnc(pilha)){
      infoAux = desempilhaPilhaEnc(pilha);
      printf("%d | %s (%s)\n", infoAux.matricula, infoAux.nome, infoAux.email);   
   }
   
   printf("\nPilha copia.\n");   
   while (!vaziaPilhaEnc(pilhacopia)){
      infoAux = desempilhaPilhaEnc(pilhacopia);
      printf("%d | %s (%s)\n", infoAux.matricula, infoAux.nome, infoAux.email);   
   }

   
/*
   empilhaPilhaEnc(pilha, info1); 
   empilhaPilhaEnc(pilha, info2); 
   empilhaPilhaEnc(pilha, info3); 
   empilhaPilhaEnc(pilha, info4); 
   empilhaPilhaEnc(pilha, info5);

   invertePilhaEncBonus(pilha);

   printf("\nPilha invertida.\n");

   while (!vaziaPilhaEnc(pilha)){
      infoAux = desempilhaPilhaEnc(pilha);
      printf("%d | %s (%s)\n", infoAux.matricula, infoAux.nome, infoAux.email);   
   }


   printf("cabou\n");


   destroiPilhaEnc(pilha);
   printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
   printf("Fila Original\n");
   
   enfileiraFilaEnc(fila, info1); 
   enfileiraFilaEnc(fila, info2); 
   enfileiraFilaEnc(fila, info3); 
   enfileiraFilaEnc(fila, info4); 
   enfileiraFilaEnc(fila, info5); 

   while (!vaziaFilaEnc(fila)){
      infoAux = desenfileiraFilaEnc(fila);
      printf("%d | %s (%s)\n", infoAux.matricula, infoAux.nome, infoAux.email);   
   }

   printf("Fila invertida\n");

   enfileiraFilaEnc(fila, info1); 
   enfileiraFilaEnc(fila, info2); 
   enfileiraFilaEnc(fila, info3); 
   enfileiraFilaEnc(fila, info4); 
   enfileiraFilaEnc(fila, info5);

   filaInv = copiaInvertidaFilaEnc(fila);

   while (!vaziaFilaEnc(filaInv)){
      infoAux = desenfileiraFilaEnc(filaInv);
      printf("%d | %s (%s)\n", infoAux.matricula, infoAux.nome, infoAux.email);   
   }
   
*/
   printf("cabou\n");
   
   destroiFilaEnc(fila);
   destroiFilaEnc(filaInv);
   
   return 0;
}
