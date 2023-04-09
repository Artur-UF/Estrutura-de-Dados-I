#ifndef _PACIENCIA_H_
#define _PACIENCIA_H_
#include "defs.h"
#include "fila_enc.h"
#include "pilha_enc.h"
#include "lista_cont.h"

double uniform(double min, double max);
void seleciona(bool *selecionado, Info *carta, Rectangle *selecRec);
int confereOrdem(FilaEnc *fila);
bool mouseEmFila(FilaEnc **filas, PilhaEnc **pilhas, int *contafila, int *contacarta, float *geometria);
int confereFilaCompleta(FilaEnc *fila);
void criaMatriz(Info cartas[8][13], int nNaipes, float *geometria);
void inicializaJogo(Info cartas[8][13], PilhaEnc *monte, PilhaEnc *pilhas[10], FilaEnc *filas[10], float *geometria);
void desenhaCartasSuperiores(Texture2D back, PilhaEnc *monte, float *geometria, int filasCompletas);
void desenhaPilhaseFilas(Texture2D back, Texture2D deck, PilhaEnc **pilhas, FilaEnc **filas);
void compraCartasDoMonte(PilhaEnc *monte, PilhaEnc **pilhas, FilaEnc **filas, float *geometria);
void selecionaCarta(PilhaEnc **pilhas, FilaEnc **filas, float *geometria, bool *selecionado, int *filaSelec, int *cartaSelec, Info *cartaSelecionada, Rectangle *selecRec);

#endif
