/*
Para compilar em linux:

gcc main.c bibs/*.c -o Paciencia -I/usr/local/include -L/usr/local/lib /usr/local/lib/libraylib.so.4.2.0

*/
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

#include "raylib.h"
#include "bibs/defs.h"
#include "bibs/paciencia.h"



//------------------------------------------------------------------------------------
// Program main entry point
//-----------------------------------------------------------------------------------
int main(void){
    // Initialization
    //--------------------------------------------------------------------------------------
	float deckscale = SCREENWIDTH/3000.;
	float backscale = SCREENWIDTH/9605.;

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

	// Cria a matriz de cartas
	Info cartas[8][13];
	criaMatriz(cartas, 1, geometria);
	
	// VERIFICAR UTILIDADE DE STATUS NO TAD
	
	// Cria e inicializa as filas pilhas e monte
	PilhaEnc *monte = criaPilhaEnc();
	PilhaEnc *pilhas[10];
	FilaEnc *filas[10];
	inicializaJogo(cartas, monte, pilhas, filas, geometria);
	
	PilhaEnc *pilhasAux[10];
	FilaEnc *filasAux[10];
	Info cartaAux, cartaSelecionada, cartaAux2;

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

	// Menu antes do jogo
	bool comecaJogo = 0;
		
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
    	// OI VITORIA, TAVA TESTANDO UM MENU AQUI :)
        if(!comecaJogo){
        	BeginDrawing();
        		
        		ClearBackground(RAYWHITE);
        		
        		DrawText("Paciencia", SCREENWIDTH/2., SCREENHEIGHT/7., 	40, BLACK);
        		if(IsMouseButtonPressed(0)) comecaJogo = 1;

			EndDrawing();        	
        }else{
		    BeginDrawing();

				// Desenha os retangulos brancos
		        ClearBackground(DARKGREEN);
		        
		        desenhaCartasSuperiores(back, monte, geometria, filasCompletas);

				compraCartasDoMonte(monte, pilhas, filas, geometria);

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
							}else{
								if(GetMouseX() > espaco + i*(largcarta + espaco) &&
									GetMouseX() < espaco + i*(largcarta + espaco) + largcarta &&
									GetMouseY() > 2*espaco + altcarta && 
									GetMouseY() < 2*espaco + 2*altcarta){
									
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
											cartaAux2.loc.y = 2*espaco + altcarta +	filas[i]->tamanho*(altcarta/5.);
											enfileiraFilaEnc(filas[i],
											 cartaAux2);
										}
										++j;
									}
									filasCompletas += confereFilaCompleta(filas[i]);
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
				
				if(selecionado){
					DrawRectangleRoundedLines(selecRec, 0.1, 5, 7, RED);
				}

		    EndDrawing();
		}
    }

	// De-Initialization
	UnloadTexture(deck);
	UnloadTexture(back);


    CloseWindow();
    return 0;
}
