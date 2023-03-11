/*
gcc arquivo.c -I/usr/local/include -L/usr/local/lib /usr/local/lib/libraylib.so.4.2.0
*/

#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1080;
    const int screenHeight = 720;
    double cscale = 4;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
	Image imdeck = LoadImage("imagens/deck.png");
	ImageResize(&imdeck, imdeck.width/3., imdeck.height/3.);
	Texture2D deck = LoadTextureFromImage(imdeck);
	UnloadImage(imdeck);
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
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(DARKGREEN);
			DrawTextureRec(deck, deckmtx[0][12], vec, WHITE);
			DrawTextureRec(deck, deckmtx[0][12], vec2, WHITE);
	

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(deck);
    
    
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
