/* Atividade Prática 1
Nome: Artur Uhlik Fröhlich
Data: 08/12/2022
Programa: serve para registrar ponto de trabalho, ele conta o número de horas trabalhadas
ao longo do dia
*/

#include <stdio.h>
#include <math.h>
#include "pontoEletronico.h"

void iniciaPontoEletronico (PontoEletronico *ponto){
	ponto->entrada = 0;
	ponto->tempotrabalho = 0;
}

void registraPonto (PontoEletronico *ponto, int hora, int min){	
	if (ponto->entrada == 0){ // usa "entrada" como flag para saber se o ponto já foi registrado ou não: 0 = não entrou ainda, 1 = já entrou
		ponto->hora = hora;
		ponto->min = min;
		ponto->entrada = 1;
	}else{
		ponto->tempotrabalho += (hora - ponto->hora)*60 + (min - ponto->min); // registra o tempo trabalhado em minutos
		ponto->entrada = 0;
	}
}

PontoEletronico imprimeTotalTrabalhadoDia (PontoEletronico ponto){
	int horas = 0, min, resto = ponto.tempotrabalho;

	horas = (ponto.tempotrabalho - fmod(ponto.tempotrabalho, 60))/60; // calculando o número de horas
	min = ponto.tempotrabalho - horas*60; // tirando o número de horas o resto será os miinutos
	printf("%d:%d\n", horas, min);
}

