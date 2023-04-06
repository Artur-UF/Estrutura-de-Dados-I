/*
Para compilar em linux:

gcc main.c bibs/fila_enc.c bibs/pilha_enc.c bibs/paciencia.c bibs/lista_cont.c -I/usr/local/include -L/usr/local/lib /usr/local/lib/libraylib.so.4.2.0

*/
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

#include "raylib.h"
#include "bibs/defs.h"
#include "bibs/paciencia.h"
#include "bibs/pilha_enc.h"
#include "bibs/fila_enc.h"
#include "bibs/lista_cont.h"


//------------------------------------------------------------------------------------
// Program main entry point
//-----------------------------------------------------------------------------------
int main(void){
    // Initialization
    //--------------------------------------------------------------------------------------
	float deckscale = SCREENWIDTH/3000.;
	float backscale = SCREENWIDTH/9600.;

    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Paciencia");
	Image imdeck = LoadImage("imagens/deck.png");
	ImageResize(&imdeck, imdeck.width*deckscale, imdeck.height*deckscale);
	Texture2D deck = LoadTextureFromImage(imdeck);
	Image iback = LoadImage("imagens/back.png");
	ImageResize(&iback, iback.width*backscale, iback.height*backscale);
	Texture2D back = LoadTextureFromImage(iback);
	UnloadImage(imdeck);
	UnloadImage(iback);

	float largcarta = deck.width/13.;
	float altcarta = deck.height/4.;

	float espaco = (SCREENWIDTH - 10*largcarta)/11;

	float geometria[3] = {largcarta, altcarta, espaco};

	// 4 naipes
	Info cartas4[8][13];
	Rectangle teste4;
	
	
	for(int i = 0; i <= 3; i++){
		for(int j = 0; j <= 12; j++){
			teste4.x = j*largcarta;
			teste4.y = i*altcarta;
			teste4.width = largcarta;
			teste4.height = altcarta;

			// Baralho de cima
			cartas4[i][j].tam = teste4;
			cartas4[i][j].naipe = i;
			cartas4[i][j].num = j;
			cartas4[i][j].status = 0;

			// Baralho de baixo
			cartas4[i+4][j].tam = teste4;
			cartas4[i+4][j].naipe = i;
			cartas4[i+4][j].num = j;
			cartas4[i+4][j].status = 0;
		}
	}
	
	// 1 naipe
	Info cartas1[8][13];
	Rectangle teste1;
	
	
	for(int i = 0; i < 8; i++){
		for(int j = 0; j <= 12; j++){
			teste1.x = j*largcarta;
			teste1.y = 0;
			teste1.width = largcarta;
			teste1.height = altcarta;

			// Baralho de cima
			cartas1[i][j].tam = teste1;
			cartas1[i][j].naipe = 0;
			cartas1[i][j].num = j;
			cartas1[i][j].status = 0;
		}
	}
	
	/*
	// 2 naipes
	Info cartas2[8][13];
	Rectangle teste2;
	
	
	for(int i = 0; i < 2; i++){
		for(int j = 0; j <= 12; j++){
			teste2.x = j*largcarta;
			teste2.y = i*altcarta;
			teste2.width = largcarta;
			teste2.height = altcarta;

			// Baralho de cima
			cartas2[i][j].tam = teste2;
			cartas2[i][j].naipe = i;
			cartas2[i][j].num = j;
			cartas2[i][j].status = 0;

			// Baralho de baixo
			cartas2[i+4][j].tam = teste2;
			cartas2[i+4][j].naipe = i;
			cartas2[i+4][j].num = j;
			cartas2[i+4][j].status = 0;
		}
	}*/	

	// Cria uma lista para auxiliar na criação de outras coisas
	ListaCont baralhos;
	criaListaCont(&baralhos);
	for(int i = 0; i <= 7; i++){
		for(int j = 0; j <= 12; j++){
			inserePosListaCont(&baralhos, cartas1[i][j], 0);
		}
	}

	printf("\n***Tamanho a lista baralhos: %d***\n\n", tamanhoListaCont(baralhos));

	// Criar o monte
	PilhaEnc *monte = criaPilhaEnc();
	int randint;

	while(monte->tamanho < 50){
		randint = (int) uniform(0, tamanhoListaCont(baralhos));
		empilhaPilhaEnc(monte, baralhos.nodos[randint]);
		removePosListaCont(&baralhos, randint);
	}


	// Criando as Pilhas
	PilhaEnc *pilhas[10];
	PilhaEnc *pilhasAux[10];

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

	// Criando as filas
	FilaEnc *filas[10];
	for(int i = 0; i < 10; ++i){
		filas[i] = criaFilaEnc();
		enfileiraFilaEnc(filas[i], desempilhaPilhaEnc(pilhas[i]));
		filas[i]->fim->info.status = 1;
	}

	FilaEnc *filasAux[10];
	Info cartaAux, cartaSelecionada, cartaAux2;

	// Destroi a lista de baralhos que ajudou ali
	destroiListaCont(&baralhos);

	printf("\n***Tamanho do monte: %d***\n\n", monte->tamanho);


	// Loop que imprime informações do monte
	Info infoAux;

	// Retangulo no tabuleiro
	Rectangle base;


	// Posicionamento das colunas
	float inicioY = 2*espaco+altcarta;
	int tamanhoPilha;

	// Retangulo da carta selecionada
	Rectangle selecRec;

	int i, j, k;
	int contacarta, contafila, cartaSelec, filaSelec;
	bool cartavalida = 0;
	bool sequenciavalida = 0;
	bool selecionado = 0;
	bool retSelec = 0;
	bool monteVazio = 0;

	// Controle de filas completas
	int filasCompletas = 0;

	// Retanculos brancos
	Rectangle rec = {0, 0, largcarta, altcarta};

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();

			// Desenha os retangulos brancos
            ClearBackground(DARKGREEN);
            for(i = 2; i < 10; ++i){
            	base.x = (i+1)*espaco + i*largcarta;
            	base.y = espaco;
            	base.width = largcarta;
            	base.height = altcarta;
            	if(i >= 2+filasCompletas){
	            	DrawRectangleRoundedLines(base, 0.15, 5, 3, WHITE);
            	}else{
            		DrawTexture(back, base.x, espaco, WHITE);
            	}
            }

			// Desenha o monte
			if(!monteVazio) DrawTexture(back, espaco, espaco, WHITE);

			// Faz a compra
			if(GetMouseX() > (int) espaco &&
			   GetMouseX() < (int) espaco + largcarta &&
			   GetMouseY() > (int) espaco &&
			   GetMouseY() < (int) espaco + altcarta){
				if(IsMouseButtonPressed(0)){
					if(!vaziaPilhaEnc(monte)){
						for(i = 0; i < 10; ++i){
							cartaAux = desempilhaPilhaEnc(monte);
							cartaAux.loc.x = espaco + i*(espaco + largcarta);
							cartaAux.loc.y = 2*espaco + altcarta + pilhas[i]->tamanho*(altcarta/5.) + filas[i]->tamanho*(altcarta/5.);
							enfileiraFilaEnc(filas[i], cartaAux);
						}
					}
					if(vaziaPilhaEnc(monte)) monteVazio = 1;
				}
			}

			// Desenha as pilhas viradas para baixo
			for(i = 0; i < 10; ++i){
				if(!vaziaPilhaEnc(pilhas[i])){
					pilhasAux[i] = copiaPilhaEnc(pilhas[i]);
					invertePilhaEnc(pilhasAux[i]);
					for(j = 0; j < pilhas[i]->tamanho; ++j){
						cartaAux = desempilhaPilhaEnc(pilhasAux[i]);
						DrawTexture(back, cartaAux.loc.x, cartaAux.loc.y, WHITE);
					}
				}
			}

			// Desenha filas
			for(i = 0; i < 10; ++i){
				if(vaziaFilaEnc(filas[i]) && !vaziaPilhaEnc(pilhas[i])){
					enfileiraFilaEnc(filas[i], desempilhaPilhaEnc(pilhas[i]));
				}else if(!vaziaFilaEnc(filas[i])){
					filasAux[i] = copiaFilaEnc(filas[i]);
					for(j = 0; j < filas[i]->tamanho; ++j){
						cartaAux = desenfileiraFilaEnc(filasAux[i]);
						DrawTextureRec(deck, cartaAux.tam, cartaAux.loc, WHITE);
					}
				}
			}
			
			// Faz jogada
			if(selecionado){
				if(IsMouseButtonPressed(0)){
					for(i = 0; i < 10; ++i){
						if(!vaziaFilaEnc(filas[i])){
							if(GetMouseX() > espaco + i*(largcarta + espaco) &&
								GetMouseX() < espaco + i*(largcarta + espaco) + largcarta &&
								GetMouseY() > 2*espaco + altcarta && 
								GetMouseY() < 2*espaco + altcarta + pilhas[i]->tamanho*(altcarta/5.) + filas[i]->tamanho*(altcarta/5.) + 	
												(4./5.)*altcarta){
								if(filas[i]->fim->info.num == 1 + cartaSelecionada.num){
									destroiFilaEnc(filasAux[filaSelec]);
									filasAux[filaSelec] = copiaFilaEnc(filas[filaSelec]);
									destroiFilaEnc(filas[filaSelec]);
									criaFilaEnc(filas[filaSelec]);
									j = 0;
									while(!vaziaFilaEnc(filasAux[filaSelec])){
										if(j < cartaSelec){
											enfileiraFilaEnc(filas[filaSelec], desenfileiraFilaEnc(filasAux[filaSelec]));
										}else{
											cartaAux2 = desenfileiraFilaEnc(filasAux[filaSelec]);
											cartaAux2.loc.x = espaco + i*(espaco + largcarta);
											cartaAux2.loc.y = 2*espaco + altcarta + pilhas[i]->tamanho*(altcarta/5.) + 
																filas[i]->tamanho*(altcarta/5.);
											enfileiraFilaEnc(filas[i], cartaAux2);
										}
										++j;
									}
									filasCompletas += confereFilaCompleta(filas[i]);
								}
							}
						}
					}
				selecionado = 0;
				}
			}
			
			// Seleciona carta
			cartavalida = mouseEmFila(filas, pilhas, &contafila, &contacarta, geometria);
			
			if(cartavalida){
				filasAux[contafila] = copiaFilaEnc(filas[contafila]);
				for(i = 0; i < contacarta; ++i){
					desenfileiraFilaEnc(filasAux[contafila]);
				}
				sequenciavalida = confereOrdem(filasAux[contafila]);
				cartaAux = filasAux[contafila]->ini->info;
				if(sequenciavalida && IsMouseButtonPressed(0)){
					cartaSelecionada = cartaAux;
					selecRec.x = espaco + contafila*(espaco + largcarta);
					selecRec.y = cartaSelecionada.loc.y;
					selecRec.height = altcarta + (filasAux[contafila]->tamanho - 1)*(altcarta/5.);
					selecRec.width = largcarta;
					selecionado = 1;
					cartaSelec = contacarta;
					filaSelec = contafila;
				}
				cartavalida = 0;
			}
			
//			seleciona(&selecionado, )

			if(selecionado){
				DrawRectangleRoundedLines(selecRec, 0.1, 5, 7, RED);
			}

        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(deck);


    CloseWindow();
    return 0;
}
