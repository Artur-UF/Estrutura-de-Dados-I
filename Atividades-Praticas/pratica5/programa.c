#include <stdio.h>
#include <string.h>
#include "lista_enc_dupla.h"

int main(){
   int retorno;
   ListaEnc2 *lista;
   lista = criaListaEnc2();
	
   
   // Aqui seriam chamadas as funcoes de inicializacao de nodos
   Info info1 = {1, "Fulano de Tal", "fulano@email.com"};
   Info info2 = {2, "Beltrana de Tal", "beltrana@email.com"};
   Info info3 = {3, "Cicrano de Tal", "cicrano@email.com"};
   Info info4 = {4, "Ciclana de Tal", "ciclana@email.com"};
   Info info5 = {5, "Ciclano de Tal", "ciclano@email.com"};

   

   retorno = insereInicioListaEnc2(lista, info1); // retorno = 1
   retorno = insereInicioListaEnc2(lista, info2); // retorno = 1
   retorno = insereInicioListaEnc2(lista, info3); // retorno = 1
   retorno = insereInicioListaEnc2(lista, info4); // retorno = 1
   retorno = insereInicioListaEnc2(lista, info5); // retorno = 1


   inserePosListaEnc2(lista, info5, 4);

   printf("Lista original\n");
   imprimeListaEnc2(lista);

   printf("Copia\n");
   ListaEnc2 *copia;
   copia = copiaListaEnc2(lista);
   imprimeListaEnc2(copia);
   
   destroiListaEnc2(lista);
   destroiListaEnc2(copia);

   return 0;
}
