/* Atividade Prática 1
Nome: Artur Uhlik Fröhlich
Data: 08/12/2022
Programa: serve para registrar ponto de trabalho, ele conta o número de horas trabalhadas
ao longo do dia
*/

#include <stdio.h>
#include "pontoEletronico.h"

int main(){
	PontoEletronico pEletronico;
	iniciaPontoEletronico(&pEletronico);

	registraPonto(&pEletronico, 8, 10); // Chegada ao trabalho
	registraPonto(&pEletronico, 12, 0); // Intervalo para almoco
	
	registraPonto(&pEletronico, 13, 10); // Volta do almoco
	registraPonto(&pEletronico, 17, 20); // Saida do trabalho

	imprimeTotalTrabalhadoDia(pEletronico); // Deve imprimir 8:0
	
	return 0;
}

