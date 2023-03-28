#ifndef _FILA_ENC_H_
#define _FILA_ENC_H_
#include "paciencia.h"

typedef NodoLEnc NodoFEnc;

typedef struct FilaEnc{
   NodoFEnc *ini;
   NodoFEnc *fim;
   int tamanho;
} FilaEnc;

// Funcao que cria uma fila
FilaEnc* criaFilaEnc();

// Funcao que destroi uma fila
void destroiFilaEnc(FilaEnc *fila);

// Funcao que insere um elemento na fila
void enfileiraFilaEnc(FilaEnc *fila, Info info);

// Funcao que remove um elemento da fila
Info desenfileiraFilaEnc(FilaEnc *fila);

// Funcao que determina se uma fila eh vazia
int vaziaFilaEnc(FilaEnc* fila);

// Retorna a cópia de uma fila invertida
FilaEnc* copiaInvertidaFilaEnc(FilaEnc *fila);

// Retorna uma cópia de uma fila
FilaEnc* copiaFilaEnc(FilaEnc *fila);

#endif
