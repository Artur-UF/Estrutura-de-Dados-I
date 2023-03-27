#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

#include "raylib.h"
#include "paciencia.h"
#include "pilha_enc.h"
#include "fila_enc.h"

double uniform(double min, double max) {
	/*
	Função que gera um número aleatório em uma distribuição uniforme
	*/
	double random  = ((double) rand()) / RAND_MAX;
	double range = (max - min) * random;
	double n = range + min;	
	
	return n;
}

void seleciona(bool *selecionado, Info *carta, Rectangle *selecRec){
	if(GetMouseX() > (int) carta->loc.x &&
	   GetMouseX() < (int) carta->loc.x + (int) carta->tam.width && 
	   GetMouseY() > (int) carta->loc.y && 
	   GetMouseY() < (int) carta->loc.x + (int) carta->tam.height){
		if(IsMouseButtonPressed(0)){
			if(selecionado) selecionado = 0;
			else{
				selecRec->x = carta->loc.x;
				selecRec->y = carta->loc.y;
				selecRec->x = carta->loc.x;
				selecRec->y = carta->loc.y;
				selecRec->width = carta->tam.width;
				selecRec->height = carta->tam.height;
				*selecionado = 1;
			}
		}
	}
}

/*
Aqui vou guardar a função pq vou testar a nova e não quero perder a antiga

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

*/




