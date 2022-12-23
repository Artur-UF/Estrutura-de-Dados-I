#include <stdio.h>
#include <string.h>
#include "lista_enc.h"

int main(){
   int retorno;
   ListaEnc *lista;
   ListaEnc *listaB;
   ListaEnc *listaC;
   lista = criaListaEnc();
   listaB = criaListaEnc();
   listaC = criaListaEnc();

   
   // Aqui seriam chamadas as funcoes de inicializacao de nodos
   Info info1 = {1, "Fulano de Tal", "fulano@email.com"};
   Info info2 = {2, "Beltrana de Tal", "beltrana@email.com"};
   Info info3 = {3, "Cicrano de Tal", "cicrano@email.com"};
   Info info4 = {4, "Ciclana de Tal", "ciclana@email.com"};
   Info info5 = {5, "Ciclano de Tal", "ciclano@email.com"};
   
   retorno = insereInicioListaEnc(lista, info1); // retorno = 1
   retorno = insereInicioListaEnc(lista, info2); // retorno = 1
   retorno = insereInicioListaEnc(lista, info3); // retorno = 1
   retorno = insereInicioListaEnc(lista, info4); // retorno = 1
   retorno = insereInicioListaEnc(lista, info5); // retorno = 1
   
   retorno = insereInicioListaEnc(listaB, info1); // retorno = 1
   retorno = insereInicioListaEnc(listaB, info2); // retorno = 1
   retorno = insereInicioListaEnc(listaB, info3); // retorno = 1


   NodoLEnc *nodoAux;
   nodoAux = buscaInfoListaEnc(lista, 2); // nodoAux = info2
   retorno = removeInfoListaEnc(lista, 2); // retorno = 1
   retorno = removeInfoListaEnc(lista, 50); // retorno = 0
   retorno = removeInfoListaEnc(lista, 1); // retorno = 1
   nodoAux = buscaInfoListaEnc(lista, 2); // nodoAux = NULL


   printf("Lista A:\n");
   imprimeListaEnc(lista);

   printf("Lista B:\n");
   imprimeListaEnc(listaB);
   
   printf("Lista vazia C concatenada com lista B:\n");
   retorno = concatenaListaEnc(listaC, listaB);
   imprimeListaEnc(listaC);
   
   printf("Concatenadas\n");
   retorno = concatenaListaEnc(lista, listaB);

   imprimeListaEnc(lista);
   destroiListaEnc(lista);

   return 0;
}
