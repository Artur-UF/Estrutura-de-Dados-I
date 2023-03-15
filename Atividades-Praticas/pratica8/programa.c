#include <stdio.h>
#include "avl.h"

int main(){

   // Aqui seriam chamadas as funcoes de inicializacao de infos
   Info info1 = {.chave = 1, .nome = "Fulano de Tal", .email = "fulano@email.com"};
   Info info2 = {.chave = 2, .nome = "Beltrana de Tal", .email = "beltrana@email.com"};
   Info info3 = {.chave = 3, .nome = "Cicrano de Tal", .email = "cicrano@email.com"};
   Info info4 = {.chave = 4, .nome = "Ciclana de Tal", .email = "ciclana@email.com"};
   Info info5 = {.chave = 5, .nome = "Bla 1", .email = "ciclajoivwsmail.com"};   
   Info info6 = {.chave = 6, .nome = "Bla 2", .email = "ciclana@email.com"};

   AVL *arv;
   arv = criaAVL();
   
   insereAVL(arv, info1);
   insereAVL(arv, info2);
   insereAVL(arv, info3);
   insereAVL(arv, info4);
   insereAVL(arv, info5);
   insereAVL(arv, info6);
   
   imprimeAVL(arv);
//   imprimeAVLParentesesAninhados(arv);
   printf("Tamanho da arvore = %d\n", tamanhoAVL(arv));

//   printf("Retorno da removeInfoAVL = %d\n", removeInfoAVL(arv, 4)); // pensar em como implementar...

   removeInfoAVL(arv, 5);
   printf("Removi o 5\n");
   removeInfoAVL(arv, 6);  
   printf("Removi o 6\n"); 


   imprimeAVL(arv);
//   imprimeAVLParentesesAninhados(arv);
   printf("Tamanho da arvore = %d\n", tamanhoAVL(arv));
   
   destroiAVL(arv);
   return 0;
}
