#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

#include "paciencia.h"


double uniform(double min, double max) {
	/*
	Função que gera um número aleatório em uma distribuição uniforme
	*/
	double random  = ((double) rand()) / RAND_MAX;
	double range = (max - min) * random;
	double n = range + min;

	return n;
}


void criaMatriz(Info cartas[8][13], int nNaipes, float *geometria){
	float largcarta = geometria[0];
	float altcarta = geometria[1];
	float espaco = geometria[2];
	Rectangle teste;
	if(nNaipes == 1){
		for(int i = 0; i < 8; i++){
			for(int j = 0; j <= 12; j++){
				teste.x = j*largcarta;
				teste.y = 0;
				teste.width = largcarta;
				teste.height = altcarta;

				cartas[i][j].tam = teste;
				cartas[i][j].naipe = 0;
				cartas[i][j].num = j;
				cartas[i][j].status = 0;
			}
		}		
	}else if(nNaipes == 2){
		for(int i = 0; i < 2; i++){
			for(int j = 0; j <= 12; j++){
				teste.x = j*largcarta;
				teste.y = i*altcarta;
				teste.width = largcarta;
				teste.height = altcarta;

				cartas[0+(4*i)][j].tam = teste;
				cartas[0+(4*i)][j].naipe = i;
				cartas[0+(4*i)][j].num = j;
				cartas[0+(4*i)][j].status = 0;
				
				cartas[1+(4*i)][j].tam = teste;
				cartas[1+(4*i)][j].naipe = i;
				cartas[1+(4*i)][j].num = j;
				cartas[1+(4*i)][j].status = 0;

				cartas[2+(4*i)][j].tam = teste;
				cartas[2+(4*i)][j].naipe = i;
				cartas[2+(4*i)][j].num = j;
				cartas[2+(4*i)][j].status = 0;
				
				cartas[3+(4*i)][j].tam = teste;
				cartas[3+(4*i)][j].naipe = i;
				cartas[3+(4*i)][j].num = j;
				cartas[3+(4*i)][j].status = 0;			
				
			}
		}	
	}else if(nNaipes == 4){
		for(int i = 0; i <= 3; i++){
			for(int j = 0; j <= 12; j++){
				teste.x = j*largcarta;
				teste.y = i*altcarta;
				teste.width = largcarta;
				teste.height = altcarta;

				// Baralho de cima
				cartas[i][j].tam = teste;
				cartas[i][j].naipe = i;
				cartas[i][j].num = j;
				cartas[i][j].status = 0;

				// Baralho de baixo
				cartas[i+4][j].tam = teste;
				cartas[i+4][j].naipe = i;
				cartas[i+4][j].num = j;
				cartas[i+4][j].status = 0;
			}
		}
	}
		
}

void inicializaJogo(Info cartas[8][13], PilhaEnc *monte, PilhaEnc *pilhas[10], FilaEnc *filas[10], float *geometria){
	float largcarta = geometria[0];
	float altcarta = geometria[1];
	float espaco = geometria[2];
	int i, j, randint;

	// Cria uma lista contigua com todas as cartas da matriz
	ListaCont baralhos;
	criaListaCont(&baralhos);
	for(int i = 0; i <= 7; i++){
		for(int j = 0; j <= 12; j++){
			inserePosListaCont(&baralhos, cartas[i][j], 0);
		}
	}
	
	// Gera o monte
	while(monte->tamanho < 50){
		randint = (int) uniform(0, tamanhoListaCont(baralhos));
		empilhaPilhaEnc(monte, baralhos.nodos[randint]);
		removePosListaCont(&baralhos, randint);
	}
	
	// Gera as pilhas
	for(int i = 0; i < 10; ++i){
		pilhas[i] = criaPilhaEnc();
		if(i < 4){
			for(int j = 0; j < 6; ++j){
				randint = (int) uniform(0, tamanhoListaCont(baralhos));
				baralhos.nodos[randint].loc.x = espaco + i*(espaco+largcarta);
				baralhos.nodos[randint].loc.y = 2*espaco + altcarta + j*(altcarta/5.);
				empilhaPilhaEnc(pilhas[i], baralhos.nodos[randint]);
				removePosListaCont(&baralhos, randint);
			}
		}
		if(i >= 4){
			for(int j = 0; j < 5; ++j){
				randint = (int) uniform(0, tamanhoListaCont(baralhos));
				baralhos.nodos[randint].loc.x = espaco + i*(espaco+largcarta);
				baralhos.nodos[randint].loc.y = 2*espaco + altcarta + j*(altcarta/5.);
				empilhaPilhaEnc(pilhas[i], baralhos.nodos[randint]);
				removePosListaCont(&baralhos, randint);
			}
		}
	}
	
	// Gera as filas
	for(int i = 0; i < 10; ++i){
		filas[i] = criaFilaEnc();
		enfileiraFilaEnc(filas[i], desempilhaPilhaEnc(pilhas[i]));
		filas[i]->fim->info.status = 1;
	}
}

void seleciona(bool *selecionado, Info *carta, Rectangle *selecRec){
	if(GetMouseX() > (int) carta->loc.x &&
	   GetMouseX() < (int) carta->loc.x + (int) carta->tam.width &&
	   GetMouseY() > (int) carta->loc.y &&
	   GetMouseY() < (int) carta->loc.x + (int) carta->tam.height){
		if(IsMouseButtonPressed(0)){
			if(selecionado) selecionado = 0;
			else{
				selecRec->x = carta->loc.x;
				selecRec->y = carta->loc.y;
				selecRec->x = carta->loc.x;
				selecRec->y = carta->loc.y;
				selecRec->width = carta->tam.width;
				selecRec->height = carta->tam.height;
				*selecionado = 1;
			}
		}
	}
}

int confereOrdem(FilaEnc *fila){
    FilaEnc *filaConfere = copiaFilaEnc(fila);
    Carta cartaAux1 = desenfileiraFilaEnc(filaConfere);
    Carta cartaAux2;
    while(filaConfere->tamanho > 0){
        cartaAux2 = desenfileiraFilaEnc(filaConfere);
        if(cartaAux2.naipe != cartaAux1.naipe || cartaAux2.num != cartaAux1.num-1){
            destroiFilaEnc(filaConfere);
            return 0;
        }
        cartaAux1 = cartaAux2;
    }
    destroiFilaEnc(filaConfere);
    return 1;
}

int confereFilaCompleta(FilaEnc *fila){
    FilaEnc *filaConfere = copiaFilaEnc(fila);
    bool confere = 0;
    while(filaConfere->tamanho > 0){
		if(confereOrdem(filaConfere) && filaConfere->tamanho == 13){
			confere = 1;
			break;
		}
		desenfileiraFilaEnc(filaConfere);
    }
	if(confere){
		int tamanhoNovaFila = fila->tamanho - filaConfere->tamanho;
		FilaEnc *filaCopia = copiaFilaEnc(fila);
		while(!vaziaFilaEnc(fila)) desenfileiraFilaEnc(fila);
		for(int i = 0; i < tamanhoNovaFila; ++i){
			enfileiraFilaEnc(fila, desenfileiraFilaEnc(filaCopia));
		}
		return 1;
	}
	return 0;
} 


bool mouseEmFila(FilaEnc **filas, PilhaEnc **pilhas, int *contafila, int *contacarta, float *geometria){
	// Seleçao de carta
	float largcarta = geometria[0];
	float altcarta = geometria[1];
	float espaco = geometria[2];
	int i, j;
	for(i = 0; i < 10; ++i){
		// Seleciona qual fila verificar
		if(GetMouseX() > espaco + i*(espaco + largcarta) &&
			GetMouseX() < espaco + i*(espaco + largcarta) + largcarta &&
			GetMouseY() > 2*espaco + altcarta){
			for(j = 0; j < filas[i]->tamanho; ++j){
				// Se a fila tiver uma carta ele olha a altura de uma carta inteira
				if(filas[i]->tamanho == 1){
					if(GetMouseY() > 2*espaco + altcarta + pilhas[i]->tamanho*(altcarta/5.) &&
						GetMouseY() < 2*espaco + altcarta + pilhas[i]->tamanho*(altcarta/5.) + altcarta){
						*contacarta = 0;
						*contafila = i;
						return 1;
					}
				}
				// Se for a ultima carta da fila ele olha a carta inteira tmb
				else if(j > 0 && j == filas[i]->tamanho-1){
					if(GetMouseY() > 2*espaco + altcarta + pilhas[i]->tamanho*(altcarta/5.) + j*(altcarta/5.) &&
						GetMouseY() < 2*espaco + altcarta + pilhas[i]->tamanho*(altcarta/5.) + j*(altcarta/5.) + altcarta){
						*contacarta = j;
						*contafila = i;
						return 1;
					}
				}
				// Se for qualquer uma no meio ele olha só a janelinha
				else{
					if(GetMouseY() > 2*espaco + altcarta + pilhas[i]->tamanho*(altcarta/5.) + j*(altcarta/5.) &&
						GetMouseY() < 2*espaco + altcarta + pilhas[i]->tamanho*(altcarta/5.) + (j+1)*(altcarta/5.)){
						*contacarta = j;
						*contafila = i;
						return 1;
					}
				}
			}
		}
	}
	return 0;
}






