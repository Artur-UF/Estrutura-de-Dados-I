/*
Autores: Artur Uhlik Fröhlich e Vitória Tesser Henkes
Programa: Paciência Spider
Trabalho Final da disciplina Estruturas de Dados I

Para compilar em linux:
gcc main.c bibs/*.c -o Paciencia -I/usr/local/include -L/usr/local/lib /usr/local/lib/libraylib.so.4.2.0
*/

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

#include "raylib.h"
#include "bibs/paciencia.h"

int main(void){

	float deckscale = SCREENWIDTH/3000.;
	float backscale = SCREENWIDTH/9605.;
	
	// Inicialização da janela e das texturas das cartas
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Paciencia");
	Image imdeck = LoadImage("imagens/deck.png");
	ImageResize(&imdeck, imdeck.width*deckscale, imdeck.height*deckscale);
	Texture2D deck = LoadTextureFromImage(imdeck);
	Image iback = LoadImage("imagens/back.png");
	ImageResize(&iback, iback.width*backscale, iback.height*backscale);
	Texture2D back = LoadTextureFromImage(iback);
	UnloadImage(imdeck);
	UnloadImage(iback);

	// Geometria da mesa de jogo
	float largcarta = deck.width/13.;
	float altcarta = deck.height/4.;
	float espaco = (SCREENWIDTH - 10*largcarta)/11;
	float geometria[3] = {largcarta, altcarta, espaco};

	// Estruturas para armazenar cartas
	Info cartas[8][13];
	PilhaEnc *monte = criaPilhaEnc();
	PilhaEnc *pilhas[10];
	FilaEnc *filas[10];

	// Variáveis de seleção
	Rectangle selecRec;
	Info cartaSelecionada;
	int cartaSelec, filaSelec;
	bool selecionado = 0;

	// Controle de filas completas
	int filasCompletas = 0;

	// Menu antes do jogo
	bool comecaJogo = 0;
	int nNaipes = 0;
	float meiox = SCREENWIDTH/2.;
	float meioy = SCREENHEIGHT/2.;
	Rectangle escolhas;
    escolhas.width = 300;
	escolhas.height = SCREENHEIGHT/18.;
	escolhas.x = meiox - 150.;
	escolhas.y = meioy - SCREENHEIGHT/4.;

	// Tela final
	int nJogadas;
	char mensagemfinal[20];

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if(!comecaJogo){

        	BeginDrawing();
				nNaipes = fazMenu(nNaipes, &escolhas);
				if(nNaipes > 0){
					criaMatriz(cartas, nNaipes, geometria);
					inicializaJogo(cartas, monte, pilhas, filas, geometria);
					comecaJogo = 1;
				}

			EndDrawing();
        }else{
		    BeginDrawing();

				desenhaCartasSuperiores(back, monte, geometria, filasCompletas);
				desenhaPilhaseFilas(back, deck, monte, pilhas, filas);
				compraCartasDoMonte(monte, pilhas, filas, geometria);
				realizaJogada(pilhas, filas, geometria, &selecionado, filaSelec, cartaSelec, cartaSelecionada, &filasCompletas, &nJogadas);
                selecionaCarta(pilhas, filas, geometria, &selecionado, &filaSelec, &cartaSelec, &cartaSelecionada, &selecRec);

                if(filasCompletas == 8){
					DrawText("PARABENS, VOCE VENCEU!", meiox-150, (meioy/6.)+(2*espaco+altcarta),	40, WHITE);
					sprintf(mensagemfinal, "N° de jogadas: %d", nJogadas);
					DrawText(mensagemfinal, meiox-250, (meioy/3.)+(2*espaco+altcarta), 30, WHITE);
                }

		    EndDrawing();
		}
    }

	UnloadTexture(deck);
	UnloadTexture(back);

    CloseWindow();
    return 0;
}
