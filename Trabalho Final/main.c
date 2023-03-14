/*
gcc main.c -I/usr/local/include -L/usr/local/lib /usr/local/lib/libraylib.so.4.2.0
*/

#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void){
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1080;
    const int screenHeight = 720;
    double cscale = 4;

    InitWindow(screenWidth, screenHeight, "Paciência");
	Image imdeck = LoadImage("imagens/deck.png");
	ImageResize(&imdeck, imdeck.width/3., imdeck.height/3.);
	Texture2D deck = LoadTextureFromImage(imdeck);
	Image iback = LoadImage("imagens/back.png");
	ImageResize(&iback, iback.width/9.1, iback.height/9.1);
	Texture2D back = LoadTextureFromImage(iback);
	UnloadImage(imdeck);
	UnloadImage(iback);
	
	Rectangle deckmtx[4][13];
	
	for(int i = 0; i <= 3; i++){
		for(int j = 0; j <= 12; j++){
			deckmtx[i][j].x = j*deck.width/13.;
			deckmtx[i][j].y = i*deck.height/4.;
			deckmtx[i][j].width = deck.width/13.;
			deckmtx[i][j].height = deck.height/4.;
		}
	}
	
	Vector2 vec = {50., 50.};
	Vector2 vec2 = {50., 80.};
	
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
	Rectangle rec = {0, 0, deck.width/13., deck.height/4.};
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();

            ClearBackground(DARKGREEN);
            DrawTexture(back, 50, 20, WHITE);
			DrawTextureRec(deck, deckmtx[0][12], vec, WHITE);
			DrawTextureRec(deck, deckmtx[0][12], vec2, WHITE);
	

        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(deck);
    
    
    CloseWindow();       
    return 0;
}
