#include <stdio.h>
#include "lista_cont.h"

// Funcao que cria uma lista
void criaListaCont(ListaCont *lista){
   lista->ini = 0;
   lista->fim = 0;
}

// Funcao que destroi uma lista
void destroiListaCont(ListaCont *lista){
   lista->ini = 0;
   lista->fim = 0;
}

// Funcao que retorna a cardinalidade de uma lista
int tamanhoListaCont(ListaCont lista){
   return lista.fim - lista.ini;  
}

// Funcao que insere um nodo em uma posicao de uma lista
int inserePosListaCont(ListaCont *lista, Info nodo, int pos){
   int indice;
   int tamLista = tamanhoListaCont(*lista);
   
   if (TAM_MAX_LISTA == tamLista) // verifica se a lista esta cheia
      return 0;
      
   if (pos < lista->ini || pos > lista->fim) // verifica se a posicao eh valida
      return 0;

   for (indice = lista->fim-1; indice >= pos; indice--)
      lista->nodos[indice+1] = lista->nodos[indice];
   lista->fim += 1;
   lista->nodos[pos] = nodo;
   
   return 1;
}

// Funcao que remove um nodo em uma posicao de uma lista
int removePosListaCont(ListaCont *lista, int pos){
   int indice;
   
   if (pos < lista->ini || pos >= lista->fim) // verifica se a posicao eh valida
      return 0;

   // Sempre puxa tudo para o comeco
   for (indice = pos; indice < lista->fim; indice++) 
      lista->nodos[indice] = lista->nodos[indice+1];
   lista->fim -= 1;   
   
   return 1;
}

// Funcao que resgata um nodo de uma posicao de uma lista
Info buscaPosListaCont(ListaCont lista, int pos){
   if (pos < lista.ini || pos >= lista.fim){ // verifica se a posicao eh valida
      Info auxiliar;
      auxiliar.status = -1; // um nodo com chave = -1 eh um nodo invalido
      return auxiliar;
   }
   return lista.nodos[pos];
}
/*
// Funcao que resgata um nodo com uma informacao de uma lista
Info buscaInfoListaCont(ListaCont lista, int chave){
   int indice;
   for (indice = lista.ini; indice < lista.fim; indice++)
      if(lista.nodos[indice].chave == chave)
         return lista.nodos[indice];
   Info auxiliar;
   auxiliar.chave = -1; // um nodo com chave = -1 eh um nodo invalido
   return auxiliar;
}*/

// Funcao que imprime todos os nodos de uma lista
void imprimeListaCont(ListaCont lista){
   int i;
   printf("-----------------------------------------\n");
   for (i = lista.ini; i < lista.fim; i++)
      printf("%d | %d | %d |\n", lista.nodos[i].naipe,
                               lista.nodos[i].num,
                               lista.nodos[i].status);
   printf("-----------------------------------------\n");
}

//-*-*-*-*-*-*-*-*-*-*-*Minha parte-*-*-*-*-*-*-*-*-*-*-*-*

/*
Recebe um ponteiro para uma lista na qual vamos copiar de maneira inversa o conteúdo
de outra lista
*/
void inverteListaCont(ListaCont listaA, ListaCont *listaB){
	int tam = tamanhoListaCont(listaA)-1;	
	for(int i = listaA.ini; i < listaA.fim; ++i){
		listaB->nodos[tam-i] = listaA.nodos[i]; // aqui é atribuido inversamente as infos
		listaB->fim += 1;  // atualização do fim da listaB
	}
}
/*
//Busca por chave qual Info será removida da lista e retorna a mesma info
Info removeInfoListaCont(ListaCont *lista, int chave){
	int indice;
	Info auxiliar;	
	for (indice = lista->ini; indice < lista->fim; indice++)  // for para procurar a chave
		if(lista->nodos[indice].chave == chave){
			auxiliar = lista->nodos[indice];  // inicializo a Info que será retornada
			removePosListaCont(lista, indice);  // remove a Info da lista
			return auxiliar;
		}
	auxiliar.chave = -1; // um nodo com chave = -1 eh um nodo invalido
	return auxiliar;
}


// INCOMPLETA
int concatenaListaCont(ListaCont *listaA, ListaCont listaB){
	if (tamanhoListaCont(*listaA) + tamanhoListaCont(listaB) > TAM_MAX_LISTA){
		return 0;
	}
	int tamA = listaA->fim, tamTotal = listaA->fim + tamanhoListaCont(listaB);
	for (int i = listaA->fim; i < tamTotal; ++i){
		listaA->nodos[i] = listaB.nodos[i - tamA];
		listaA->fim += 1;
	}
	return 1;
}*/
   

