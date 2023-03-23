/*
gcc main.c -I/usr/local/include -L/usr/local/lib /usr/local/lib/libraylib.so.4.2.0
*/

#include "raylib.h"
#include "paciencia.h"
#include "pilha_enc.h"
#include "fila_enc.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void){
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1500; //((largcarta) + 20)*10;
    const int screenHeight = 900;
    double cscale = 4;

    InitWindow(screenWidth, screenHeight, "Paciência");  
	Image imdeck = LoadImage("imagens/deck.png");
	ImageResize(&imdeck, imdeck.width/2., imdeck.height/2.);
	Texture2D deck = LoadTextureFromImage(imdeck);
	Image iback = LoadImage("imagens/back.png");
	ImageResize(&iback, iback.width/6.1, iback.height/6.1);
	Texture2D back = LoadTextureFromImage(iback);
	UnloadImage(imdeck);
	UnloadImage(iback);
	
	float largcarta = deck.width/13.;
	float altcarta = deck.height/4.;
	
	Info cartas[8][13];
	Rectangle teste;
	
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
			cartas[i][j].status = 1;
			
			// Baralho de baixo
			cartas[i+4][j].tam = teste;
			cartas[i+4][j].naipe = i;
			cartas[i+4][j].num = j;
			cartas[i+4][j].status = 1;
		}
	}
	
	// Criar o monte
	PilhaEnc monte = criaPilhaEnc();
	double randnaipe, randnum;
	
	
	while(monte.tamanho < 50){
		randnipe = uniform(0, 7);
		randnum = uniform(0, 12);
		if(cartas[randnipe][randnum].status){
			empilhaPilhaEnc(monte, cartas[randnipe][randnum]);
		}
	}
	
	printf("Tamanho do monte; %d", monte.tamanho);	
	
	
	// Retangulo no tabuleiro
	Rectangle base;
	float espaco = (screenWidth - 10*largcarta)/11;

	// Posicionamento das colunas
	float inicioY = 2*espaco+altcarta;
	
	Vector2 vec = {espaco, inicioY+30.};
	cartas[0][12].loc = vec;

	Vector2 vec2 = {espaco, inicioY+2.*30.};
	cartas[0][11].loc = vec2;	
	
	// Retangulo da carta selecionada
	Vector2 selecRet;
	Rectangle selecRec;
	
	bool selecionado = 0;
	
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
	Rectangle rec = {0, 0, largcarta, altcarta};
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();

            ClearBackground(DARKGREEN);
            for(int i = 2; i < 10; ++i){
            	base.x = (i+1)*espaco + i*largcarta;
            	base.y = 20;
            	base.width = largcarta;
            	base.height = altcarta;
            	DrawRectangleRoundedLines(base, 0.15, 5, 3, WHITE);
            }
            
            DrawTexture(back, espaco, inicioY, WHITE);
			DrawTextureRec(deck, cartas[0][12].tam, vec, WHITE);
			DrawTextureRec(deck, cartas[0][11].tam, vec2, WHITE);
			
			if(GetMouseX() > (int) cartas[0][11].loc.x &&
			   GetMouseX() < (int) cartas[0][11].loc.x + (int) cartas[0][11].tam.width && 
			   GetMouseY() > (int) cartas[0][11].loc.y && 
			   GetMouseY() < (int) cartas[0][11].loc.x + (int) cartas[0][11].tam.height){
			   
				if(IsMouseButtonPressed(0)){
					   if(selecionado) selecionado = 0;
					   else{
						   selecRet.x = cartas[0][11].loc.x;
						   selecRet.y = cartas[0][11].loc.y;
						   selecRec.x = cartas[0][11].loc.x;
						   selecRec.y = cartas[0][11].loc.y;
						   selecRec.width = cartas[0][11].tam.width;
						   selecRec.height = cartas[0][11].tam.height;
						   selecionado = 1;
					   }
				}
			}
			if(selecionado){
				DrawRectangleLinesEx(selecRec, 5, RED);
			}

        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(deck);
    
    
    CloseWindow();       
    return 0;
}
