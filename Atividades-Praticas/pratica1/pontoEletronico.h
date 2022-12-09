/* Atividade Prática 1
Nome: Artur Uhlik Fröhlich
Data: 08/12/2022
Programa: serve para registrar ponto de trabalho, ele conta o número de horas trabalhadas
ao longo do dia
*/

//pontoEletronico.h

typedef struct {
	int entrada; // flag que indica se o registro é de entrada ou saída
	int hora;
	int min;
	int tempotrabalho; // variavel que conta o número de horas trabalhadas
} PontoEletronico;

/* iniciaPontoEletronico
Inicializa uma variavel que controla a entrada e saida
e outra variavel com o numero de horas trabalhadas como 0,
para ser acumulada ao longo do dia
*/
void iniciaPontoEletronico (PontoEletronico *ponto);

/* registraPonto
Verifica se ja entrou com a variavel "entrada", se não ele registra o horario, 
se sim ele registra o numero de minutos na ariavel "tempotrabalho"
*/
void registraPonto (PontoEletronico *ponto, int hora, int min);

/* imprimeTotalTrabalhadoDia
Ele usa a variavel "tempotrabalho" para contar as horas e minutos do espediente e imprime
*/
PontoEletronico imprimeTotalTrabalhadoDia (PontoEletronico ponto);

