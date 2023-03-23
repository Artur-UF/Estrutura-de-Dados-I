/*
gcc main.c -I/usr/local/include -L/usr/local/lib /usr/local/lib/libraylib.so.4.2.0
*/

#include "raylib.h"
#include "paciencia.h"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void){
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1500; //((deck.width/13.) + 20)*10;
    const int screenHeight = 720;
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
	
	Carta cartas[4][13];
	Rectangle teste;
	


    
    
	for(int i = 0; i <= 3; i++){
		for(int j = 0; j <= 12; j++){
			teste.x = j*deck.width/13.;
			teste.y = i*deck.height/4.;
			teste.width = deck.width/13.;
			teste.height = deck.height/4.;
			cartas[i][j].tam = teste;
		}
	}
	
	// Retangulo no tabuleiro
	Rectangle base;
	float espaco = (screenWidth - 10*deck.width/13.)/11;


	Vector2 vec = {espaco, 50.};
	cartas[0][12].loc = vec;

	Vector2 vec2 = {espaco, 80.};
	cartas[0][11].loc = vec2;	
	
	// Retangulo da carta selecionada
	Vector2 selecRet;
	Rectangle selecRec;
	
	bool selecionado = 0;
	
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
	Rectangle rec = {0, 0, deck.width/13., deck.height/4.};
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();

            ClearBackground(DARKGREEN);
            for(int i = 2; i < 10; ++i){
            	base.x = (i+1)*espaco + i*deck.width/13.;
            	base.y = 20;
            	base.width = deck.width/13.;
            	base.height = deck.height/4.;
            	DrawRectangleRoundedLines(base, 0.1, 10, 3, WHITE);
            }
            
            DrawTexture(back, espaco, 20, WHITE);
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
