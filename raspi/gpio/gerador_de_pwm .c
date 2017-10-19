#include "wiringPi.h"
#include "time.h"

//Autor: Hemerson Rafael
//Data: 28/07/17

//Função que calcular o período a partir da frequência (Hz)
float Period(float frequency){

    return (1.00/frequency);

}

//Função responsável pela geração de sinais PWM, possui os seguintes parâmetros frequência (Hz), duty cycle (%), pino de saída e tempo de execução (s).
void SignalGenerator(float frequency, float duty_cycle, int pin_out, float time_execution){

    float time_on, time_off, time_stop;
    if((duty_cycle >= 0) && (duty_cycle <= 100) && (time_execution > 0)){
        // cálculo do tempo do pulso em baixa
        time_off = Period(frequency) - time_on;

        // cálculo do tempo do pulso em alta (de acordo com valor do ciclo ativo )
        float time_on = Period(frequency) * (duty_cycle/100.00);

        clock_t t1, t2;
        //Salva o número de clock inicial
        t1 = clock();

        // Loop para controle do tempo de execução
        do{
            // função da biblioteca wiringPi que instruir GPIO que mantenha o nível lógico do pin_out em alta (HIGH ou 1)
            digitalWhite(pin_out, 1);
            //Tempo em que o sinal estará em alta
            delay(time_on);
            // função da biblioteca wiringPi que instruir GPIO que mantenha o nível lógico do pin_out em baixa (LOW ou 0)
            digitalWhite(pin_out, 0);
            //Tempo em que o sinal estará em baixa
            delay(time_off);
            //Salva o número de clock inicial
            t2 = clock();

            //Cálculo do tempo de execução em segundos
            time_stop = (float)(t2 - t1)/CLOCKS_PER_SEC;
        //While para testa se o tempo de parada foi atingido e finalizar o laço
        }while(time_stop < time_execution);
    }

}

int main(){

}
