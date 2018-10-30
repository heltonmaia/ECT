#include <bcm2835.h>
#include <time.h>
#include <stdio.h>
#define PIN RPI_GPIO_P1_07 

int main(int argc, char *argv[]) {
	
	//INICIALIZAÇÃO DA BIBLIOTECA
    if(!bcm2835_init()){
        return 1;
    }
	clock_t t1, t2;
	float total = 0;
	int cont = 0;
    //INICIALIZAR A CONFIGURAÇÃO DO PINO COMO SAÍDA
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);

    while(cont != 10) { 
		
        t1 = clock();
        //INICIALIZAR O PINO ALTA (5V)
        bcm2835_gpio_write(PIN, HIGH);
        //INICIALIZAR O PINO BAIXA (0V)
        bcm2835_gpio_write(PIN, LOW);
        t2 = clock();
        
        // REALIZAR A SOMA DO TEMPO DE CADA CICLO EM SEGUNDOS
        total += ((float)(t2-t1)/CLOCKS_PER_SEC);
		cont++;
    }
	
	//EXIBIR A MÉDIA DE TEMPO EM SEGUNDOS DE UM CICLO
	//printf("valor em segundos: %.10f\n", (total/cont));
	printf("valor em segundos: %.10f\n", (total/cont));
	
    return 0;
}