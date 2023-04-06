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






