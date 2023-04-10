#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

#include "paciencia.h"
void moveCartas(PilhaEnc **pilhas, FilaEnc **filas, float *geometria, int filaSelec, int cartaSelec, int i);
bool mouseEmFila(PilhaEnc **pilhas, FilaEnc **filas, int *contafila, int *contacarta, float *geometria);
int confereOrdem(FilaEnc *fila);
int confereFilaCompleta(FilaEnc *fila);

//Função que gera um número aleatório em uma distribuição uniforme
double uniform(double min, double max) {
	double random  = ((double) rand()) / RAND_MAX;
	double range = (max - min) * random;
	double n = range + min;

	return n;
}

//Função que desenha o menu e define o número de naipes
int fazMenu(int nNaipes, Rectangle *escolhas){
	float meiox = SCREENWIDTH/2.;
	float meioy = SCREENHEIGHT/2.;

	ClearBackground(RAYWHITE);

	DrawText("By: Artur e Vitoria", 10, 10, 20, BLACK);
	DrawText("Paciencia Spider", meiox-150, meioy/6.,	40, BLACK);
	DrawText("Escolha a dificuldade (n° de naipes):", meiox-250, meioy/3., 30, BLACK);
	for(int i = 0; i < 3; ++i){
		DrawRectangleRoundedLines(*escolhas, 0.1, 5, 4, GRAY);
		if(i == 0){
			DrawText("1 Naipe - Fácil", escolhas->x + 10, escolhas->y + 5, 30, BLACK);
			if(GetMouseX() > escolhas->x &&
				GetMouseX() < escolhas->x + escolhas->width &&
				GetMouseY() > escolhas->y &&
				GetMouseY() < escolhas->y + escolhas->height){
				if(IsMouseButtonPressed(0)) nNaipes = 1;
			}
		}
		else if(i == 1){
			DrawText("2 Naipes - Médio", escolhas->x + 10, escolhas->y + 5, 30, BLACK);
			if(GetMouseX() > escolhas->x &&
				GetMouseX() < escolhas->x + escolhas->width &&
				GetMouseY() > escolhas->y &&
				GetMouseY() < escolhas->y + escolhas->height){
				if(IsMouseButtonPressed(0)) nNaipes = 2;
			}
		}
		else if(i == 2){
			DrawText("4 Naipes - DIFICIL", escolhas->x + 10, escolhas->y + 5, 30, BLACK);
			if(GetMouseX() > escolhas->x &&
				GetMouseX() < escolhas->x + escolhas->width &&
				GetMouseY() > escolhas->y &&
				GetMouseY() < escolhas->y + escolhas->height){
				if(IsMouseButtonPressed(0)) nNaipes = 4;
			}
		}
		escolhas->y += 70;
	}
	escolhas->y = meioy - SCREENHEIGHT/4.;
	return nNaipes;
}

//Função (auxiliar) que confere se uma fila está ordenada
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

//Função (auxiliar) que confere se um fila está completa
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

//Função que cria matriz de cartas
void criaMatriz(Info cartas[8][13], int nNaipes, float *geometria){
	float largcarta = geometria[0];
	float altcarta = geometria[1];

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

//Função que inicializa as pilhas e filas
void inicializaJogo(Info cartas[8][13], PilhaEnc *monte, PilhaEnc **pilhas, FilaEnc **filas, float *geometria){
	float largcarta = geometria[0];
	float altcarta = geometria[1];
	float espaco = geometria[2];
	int randint;

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

//Função que desenha o monte e os espaços para filas completas
void desenhaCartasSuperiores(Texture2D back, PilhaEnc *monte, float *geometria, int filasCompletas){
	float largcarta = geometria[0];
	float altcarta = geometria[1];
	float espaco = geometria[2];

	Rectangle base;
    ClearBackground(DARKGREEN);

    // Desenha os retangulos brancos e as filas completas
    for(int i = 2; i < 10; ++i){
        base.x = (i+1)*espaco + i*largcarta;
        base.y = espaco;
        base.width = largcarta;
        base.height = altcarta;
        if(i >= 2 + filasCompletas)
            DrawRectangleRoundedLines(base, 0.15, 5, 3, WHITE);
        else
            DrawTexture(back, base.x, espaco, WHITE);
    }

    // Desenha o monte
    if(!vaziaPilhaEnc(monte)) DrawTexture(back, espaco, espaco, WHITE);
}

//Função que desenha as pilhas de cartas viradas para baixo e as filas de cartas viradas para cima
void desenhaPilhaseFilas(Texture2D back, Texture2D deck, PilhaEnc *monte, PilhaEnc **pilhas, FilaEnc **filas){
    Info cartaAux;
    PilhaEnc *pilhaAux;
    FilaEnc *filaAux;

    // Desenha as pilhas (cartas viradas para baixo)
    for(int i = 0; i < 10; ++i){
        if(!vaziaPilhaEnc(pilhas[i])){
            pilhaAux = copiaPilhaEnc(pilhas[i]);
            invertePilhaEnc(pilhaAux);
            for(int j = 0; j < pilhas[i]->tamanho; ++j){
                cartaAux = desempilhaPilhaEnc(pilhaAux);
                DrawTexture(back, cartaAux.loc.x, cartaAux.loc.y, WHITE);
            }
        }
    }

    // Desenha as filas (cartas viradas para cima)
    for(int i = 0; i < 10; ++i){
        if(vaziaFilaEnc(filas[i]) && !vaziaPilhaEnc(pilhas[i])){
            enfileiraFilaEnc(filas[i], desempilhaPilhaEnc(pilhas[i]));
        }else if(!vaziaFilaEnc(filas[i])){
            filaAux = copiaFilaEnc(filas[i]);
            for(int j = 0; j < filas[i]->tamanho; ++j){
                cartaAux = desenfileiraFilaEnc(filaAux);
                DrawTextureRec(deck, cartaAux.tam, cartaAux.loc, WHITE);
            }
        }
    }

    //destroiFilaEnc(filaAux);
    //destroiPilhaEnc(pilhaAux);
}

//Função que realiza a compra de cartas
void compraCartasDoMonte(PilhaEnc *monte, PilhaEnc **pilhas, FilaEnc **filas, float *geometria){
	float largcarta = geometria[0];
	float altcarta = geometria[1];
	float espaco = geometria[2];

	Info cartaAux;

    if(GetMouseX() > espaco &&
       GetMouseX() < espaco + largcarta &&
       GetMouseY() > espaco &&
       GetMouseY() < espaco + altcarta){
        if(IsMouseButtonPressed(0)){
            if(!vaziaPilhaEnc(monte)){
                for(int i = 0; i < 10; ++i){
                    cartaAux = desempilhaPilhaEnc(monte);
                    cartaAux.loc.x = espaco + i*(espaco + largcarta);
                    cartaAux.loc.y = 2*espaco + altcarta + pilhas[i]->tamanho*(altcarta/5.) + filas[i]->tamanho*(altcarta/5.);
                    enfileiraFilaEnc(filas[i], cartaAux);
                }
            }
        }
    }
}

//Função (auxiliar) que efetivamente move as cartas
void moveCartas(PilhaEnc **pilhas, FilaEnc **filas, float *geometria, int filaSelec, int cartaSelec, int i){
    float largcarta = geometria[0];
	float altcarta = geometria[1];
	float espaco = geometria[2];

    FilaEnc *filaAux;
    Info cartaAux;

    filaAux = copiaFilaEnc(filas[filaSelec]);
    while(!vaziaFilaEnc(filas[filaSelec])) desenfileiraFilaEnc(filas[filaSelec]);
    int j = 0;
    while(!vaziaFilaEnc(filaAux)){
        if(j < cartaSelec){
            enfileiraFilaEnc(filas[filaSelec], desenfileiraFilaEnc(filaAux));
        }else{
            cartaAux = desenfileiraFilaEnc(filaAux);
            cartaAux.loc.x = espaco + i*(espaco + largcarta);
            cartaAux.loc.y = 2*espaco + altcarta + pilhas[i]->tamanho*(altcarta/5.) +
                                filas[i]->tamanho*(altcarta/5.);
            enfileiraFilaEnc(filas[i], cartaAux);
        }
        ++j;
    }
}

//Função que move cartas de uma fila a outra se permitido
void realizaJogada(PilhaEnc **pilhas, FilaEnc **filas, float *geometria, bool *selecionado, int filaSelec, int cartaSelec, Info cartaSelecionada, int *filasCompletas, int *nJogadas){
    float largcarta = geometria[0];
	float altcarta = geometria[1];
	float espaco = geometria[2];

    if(*selecionado){
        if(IsMouseButtonPressed(0)){
            for(int i = 0; i < 10; ++i){
                if(!vaziaFilaEnc(filas[i])){
                    if(GetMouseX() > espaco + i*(largcarta + espaco) &&
                        GetMouseX() < espaco + i*(largcarta + espaco) + largcarta &&
                        GetMouseY() > 2*espaco + altcarta &&
                        GetMouseY() < 2*espaco + altcarta + pilhas[i]->tamanho*(altcarta/5.) + filas[i]->tamanho*(altcarta/5.) +
                                        (4./5.)*altcarta){
                        if(filas[i]->fim->info.num == 1 + cartaSelecionada.num){
                            moveCartas(pilhas, filas, geometria, filaSelec, cartaSelec, i);
                            *filasCompletas += confereFilaCompleta(filas[i]);
                            *nJogadas += 1;
                        }
                    }
                }else{ //Pilha vazia
                    if(GetMouseX() > espaco + i*(largcarta + espaco) &&
                        GetMouseX() < espaco + i*(largcarta + espaco) + largcarta &&
                        GetMouseY() > 2*espaco + altcarta &&
                        GetMouseY() < 2*espaco + 2*altcarta){
                        moveCartas(pilhas, filas, geometria, filaSelec, cartaSelec, i);
                        *filasCompletas += confereFilaCompleta(filas[i]);
                    	*nJogadas += 1;
                    }
                }
            }
        *selecionado = 0;
        }
    }
}

//Função (auxiliar) que verifica se mouse está em uma carta virada para cima
bool mouseEmFila(PilhaEnc **pilhas, FilaEnc **filas, int *contafila, int *contacarta, float *geometria){
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

//Função que seleciona uma carta
void selecionaCarta(PilhaEnc **pilhas, FilaEnc **filas, float *geometria, bool *selecionado, int *filaSelec, int *cartaSelec, Info *cartaSelecionada, Rectangle *selecRec){
    float largcarta = geometria[0];
	float altcarta = geometria[1];
	float espaco = geometria[2];

    FilaEnc *filaAux;
    int contafila, contacarta;
    bool sequenciaValida;
    bool cartaValida = mouseEmFila(pilhas, filas, &contafila, &contacarta, geometria);

    if(cartaValida){
        filaAux = copiaFilaEnc(filas[contafila]);
        for(int i = 0; i < contacarta; ++i) desenfileiraFilaEnc(filaAux);
        sequenciaValida = confereOrdem(filaAux);
        if(sequenciaValida && IsMouseButtonPressed(0)){
            *cartaSelecionada = filaAux->ini->info;
            selecRec->x = espaco + contafila*(espaco + largcarta);
            selecRec->y = cartaSelecionada->loc.y;
            selecRec->height = altcarta + (filaAux->tamanho - 1)*(altcarta/5.);
            selecRec->width = largcarta;
            *selecionado = 1;
            *cartaSelec = contacarta;
            *filaSelec = contafila;
            /*printf("--- selecionaCarta ---\n");
            printf("Naipe: %d | num: %d | fila: %d\n", cartaSelecionada->naipe, cartaSelecionada->num, *filaSelec);
            printf("*-*-*-*-*-*-*-*-*-*-*-**-*-*-*-*-*\n");*/

        }
    }
}




