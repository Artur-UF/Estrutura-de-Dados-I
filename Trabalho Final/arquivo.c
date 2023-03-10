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


	Image card = LoadImage("imagens/king_of_hearts2.png");
	
	ImageResize(&card, card.width/cscale, card.height/cscale);
	Texture2D copasK = LoadTextureFromImage(card);
	
	card = LoadImage("imagens/queen_of_hearts2.png");
	ImageResize(&card, card.width/cscale, card.height/cscale);
	Texture2D copasQ = LoadTextureFromImage(card);
	
	card = LoadImage("imagens/jack_of_hearts2.png");
	ImageResize(&card, card.width/cscale, card.height/cscale);
	Texture2D copasJ = LoadTextureFromImage(card);
	
	card = LoadImage("imagens/10_of_hearts.png");
	ImageResize(&card, card.width/cscale, card.height/cscale);
	Texture2D copas10 = LoadTextureFromImage(card);
	
	card = LoadImage("imagens/9_of_hearts.png");
	ImageResize(&card, card.width/cscale, card.height/cscale);
	Texture2D copas9 = LoadTextureFromImage(card);
	
	card = LoadImage("imagens/8_of_hearts.png");
	ImageResize(&card, card.width/cscale, card.height/cscale);
	Texture2D copas8 = LoadTextureFromImage(card);
	
	card = LoadImage("imagens/7_of_hearts.png");
	ImageResize(&card, card.width/cscale, card.height/cscale);
	Texture2D copas7 = LoadTextureFromImage(card);
	
	card = LoadImage("imagens/6_of_hearts.png");
	ImageResize(&card, card.width/cscale, card.height/cscale);
	Texture2D copas6 = LoadTextureFromImage(card);
	
	card = LoadImage("imagens/5_of_hearts.png");
	ImageResize(&card, card.width/cscale, card.height/cscale);
	Texture2D copas5 = LoadTextureFromImage(card);
	
	card = LoadImage("imagens/4_of_hearts.png");
	ImageResize(&card, card.width/cscale, card.height/cscale);
	Texture2D copas4 = LoadTextureFromImage(card);
	
	card = LoadImage("imagens/3_of_hearts.png");
	ImageResize(&card, card.width/cscale, card.height/cscale);
	Texture2D copas3 = LoadTextureFromImage(card);
	
	card = LoadImage("imagens/2_of_hearts.png");
	ImageResize(&card, card.width/cscale, card.height/cscale);
	Texture2D copas2 = LoadTextureFromImage(card);
	
	card = LoadImage("imagens/ace_of_hearts.png");
	ImageResize(&card, card.width/cscale, card.height/cscale);
	Texture2D copasA = LoadTextureFromImage(card);	
	
	UnloadImage(card);
	
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

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
			DrawTexture(copasK, 50, 50, WHITE);
			DrawTexture(copasQ, 50, 50+1*40, WHITE);
			DrawTexture(copasJ, 50, 50+2*40, WHITE);
			DrawTexture(copas10, 50, 50+3*40, WHITE);
			DrawTexture(copas9, 50, 50+4*40, WHITE);
			DrawTexture(copas8, 50, 50+5*40, WHITE);
			DrawTexture(copas7, 50, 50+6*40, WHITE);
			DrawTexture(copas6, 50, 50+7*40, WHITE);
			DrawTexture(copas5, 50, 50+8*40, WHITE);
			DrawTexture(copas4, 50, 50+9*40, WHITE);
			DrawTexture(copas3, 50, 50+10*40, WHITE);
			DrawTexture(copas2, 50, 50+11*40, WHITE);
			DrawTexture(copasA, 50, 50+12*40, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(copasK);
    UnloadTexture(copasQ);
    UnloadTexture(copasJ);
    UnloadTexture(copas10);
    UnloadTexture(copas9);
    UnloadTexture(copas8);
    UnloadTexture(copas7);
    UnloadTexture(copas6);
    UnloadTexture(copas5);
    UnloadTexture(copas4);
    UnloadTexture(copas3);
    UnloadTexture(copas2);
    UnloadTexture(copasA);
    
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
