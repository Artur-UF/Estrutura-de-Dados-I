#ifndef _PACIENCIA_H_
#define _PACIENCIA_H_
#include "definicoes.h"
#include "fila_enc.h"
#include "pilha_enc.h"
#include "lista_cont.h"

//Fun��o que gera um n�mero aleat�rio em uma distribui��o uniforme
double uniform(double min, double max);

//Fun��o que desenha o menu e define o n�mero de naipes
int fazMenu(int nNaipes, Rectangle *escolhas);

//Fun��o que cria matriz de cartas
void criaMatriz(Info cartas[8][13], int nNaipes, float *geometria);

//Fun��o que inicializa as pilhas e filas
void inicializaJogo(Info cartas[8][13], PilhaEnc *monte, PilhaEnc **pilhas, FilaEnc **filas, float *geometria);

//Fun��o que desenha o monte e os espa�os para filas completas
void desenhaCartasSuperiores(Texture2D back, PilhaEnc *monte, float *geometria, int filasCompletas);

//Fun��o que desenha as pilhas de cartas viradas para baixo e as filas de cartas viradas para cima
void desenhaPilhaseFilas(Texture2D back, Texture2D deck, PilhaEnc *monte, PilhaEnc **pilhas, FilaEnc **filas);

//Fun��o que realiza a compra de cartas
void compraCartasDoMonte(PilhaEnc *monte, PilhaEnc **pilhas, FilaEnc **filas, float *geometria);

//Fun��o que move cartas de uma fila a outra se permitido
void realizaJogada(PilhaEnc **pilhas, FilaEnc **filas, float *geometria, bool *selecionado, int filaSelec, int cartaSelec, Info cartaSelecionada, int *filasCompletas, int *nJogadas);

//Fun��o que seleciona uma carta
void selecionaCarta(PilhaEnc **pilhas, FilaEnc **filas, float *geometria, bool *selecionado, int *filaSelec, int *cartaSelec, Info *cartaSelecionada, Rectangle *selecRec);

#endif
