#include <wiringPi.h>
#include <time.h>
#include <stdio.h>
#define IN_PIN  0 //DECLARO O PINO 0 COMO ENTRADA
#define OUT_PIN 1 //DECLARO O PINO 1 COMO SAÍDA


int main(){
	//INICIALIZAÇÃO DA BIBLIOTECA
	wiringPiSetup();
	//INICIALIZAR A CONFIGURAÇÃO DE CADA PINO COMO SAÍDA E ENTRADA
	pinMode(OUT_PIN, OUTPUT);
	pinMode(IN_PIN, INPUT);

	clock_t t1, t2;
	float total = 0;
	int cont = 0;
	
	while(cont != 10000) {
		//INICIALIZAR O PINO ALTA (5V)
		digitalWrite(OUT_PIN, 1);
		//TESTA SE O PINO 1 FOI INICIALIZADO EM ALTA (5V) PARA PEGAR O TEMPO DE PROCESSAMENTO INICIAL
		if(digitalRead(IN_PIN) == 1){

			t1 = clock();
		}
		//INICIALIZAR O PINO BAIXA (0V)
		digitalWrite(OUT_PIN, 0);
		//TESTA SE O PINO 1 FOI INICIALIZADO EM BAIXA(0V) PARA PEGAR O TEMPO DE PROCESSAMENTO FINAL
		if(digitalRead(IN_PIN ) == 0){

            t2 = clock();
		}
		// REALIZAR A SOMA DO TEMPO DE CADA CICLO EM SEGUNDOS
		total += ((float)(t2-t1)/CLOCKS_PER_SEC);
		cont++;
	}
	//EXIBIR A MÉDIA DE TEMPO EM SEGUNDOS DE UM CICLO
	printf("valor em segundos: %f \n", total/10000);

	return (0);

}