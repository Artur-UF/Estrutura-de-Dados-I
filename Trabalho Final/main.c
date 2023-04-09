/*
Para compilar em linux:

gcc main.c bibs/*.c -o Paciencia -I/usr/local/include -L/usr/local/lib /usr/local/lib/libraylib.so.4.2.0


Na última pilha a sumir ele quebra
Verifica moveCartas
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

	// Retangulo da carta selecionada
	Rectangle selecRec;

	Info cartaSelecionada;
	int cartaSelec, filaSelec;
	bool selecionado = 0;

	// Controle de filas completas
	int filasCompletas = 0;

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

				desenhaCartasSuperiores(back, monte, geometria, filasCompletas);
				desenhaPilhaseFilas(back, deck, monte, pilhas, filas);
				compraCartasDoMonte(monte, pilhas, filas, geometria);
				realizaJogada(pilhas, filas, geometria, &selecionado, filaSelec, cartaSelec, cartaSelecionada, &filasCompletas);
                selecionaCarta(pilhas, filas, geometria, &selecionado, &filaSelec, &cartaSelec, &cartaSelecionada, &selecRec);
                if(selecionado) DrawRectangleRoundedLines(selecRec, 0.1, 5, 7, RED);

		    EndDrawing();
		}
    }

	// De-Initialization
	UnloadTexture(deck);
	UnloadTexture(back);

    CloseWindow();
    return 0;
}
