#ifndef _PACIENCIA_H_
#define _PACIENCIA_H_
#include "defs.h"
#include "fila_enc.h"
#include "pilha_enc.h"

double uniform(double min, double max);
void seleciona(bool *selecionado, Info *carta, Rectangle *selecRec);
int confereOrdem(FilaEnc *fila);
bool mouseEmFila(FilaEnc **filas, PilhaEnc **pilhas, int *contafila, int *contacarta, float *geometria);
int confereFilaCompleta(FilaEnc *fila);

#endif
