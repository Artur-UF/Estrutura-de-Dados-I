#include "lista_cont.h"
#include <stdio.h>
#include <string.h>

int main(){

   int retorno;
   ListaCont lista, listaB;
   criaListaCont(&lista);
   criaListaCont(&listaB);
   
   Info infoAux;
   // Aqui seriam chamadas as funcoes de inicializacao de nodos
   Info info1 = {1, "Fulano de Tal", "fulano@email.com"};
   Info info2 = {2, "Beltrana de Tal", "beltrana@email.com"};
   Info info3 = {3, "Cicrano de Tal", "cicrano@email.com"};
   Info info4 = {4, "Ciclana de Tal", "ciclana@email.com"};
   Info info5 = {5, "Ciclano de Tal", "ciclano@email.com"};
  
   retorno = inserePosListaCont(&lista, info1, 0); // retorno = 1
   retorno = inserePosListaCont(&lista, info2, 1); // retorno = 1
   retorno = inserePosListaCont(&lista, info3, -1); // retorno = 0
   retorno = inserePosListaCont(&lista, info4, 5); // retorno = 0 
   //retorno = inserePosListaCont(&lista, info4, 0); // retorno = 1   
   retorno = inserePosListaCont(&lista, info5, 2); // retorno = 1
   
   infoAux = buscaPosListaCont(lista, 2); // infoAux = info5   
   infoAux = buscaInfoListaCont(lista, 5); // infoAux = info5
   
   //imprimeListaCont(lista);

   //retorno = tamanhoListaCont(lista); // retorno = 4
      
   retorno = removePosListaCont(&lista, 0); // retorno = 1
   //retorno = removePosListaCont(&lista, 4); // retorno = 0
   
   inverteListaCont(lista, &listaB);

   imprimeListaCont(lista);
   imprimeListaCont(listaB);
   Info auxiliar = removeInfoListaCont(&listaB, 5);
   printf("Info auxiliar: chave = %d\n", auxiliar.chave);
   imprimeListaCont(listaB);
   
   concatenaListaCont(&listaB, lista);
   
   imprimeListaCont(listaB);

   destroiListaCont(&lista);
   destroiListaCont(&listaB);

   //retorno = inserePosListaCont(&lista, info4, 0); // retorno = 1*/
   //imprimeListaCont(lista);
      
   return 0;
}

