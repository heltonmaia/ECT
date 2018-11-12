#include <fstream>
#include<time.h>
#include <iostream>
#include<wiringPi.h>
#include<unistd.h>
#include<chrono>
#include<cmath>
#define PRECISAO 1000000 //Precisao da funcao de espera "usleep"
#define NANO 1000000000

using namespace std;

int gravar(float frequencia, float tempo, int interacoes,float timeon, float timeoff){ //Funcao que grava os dados no arquivo .txt
        ofstream out;
        out.open("DC_GPIO.txt");
        if(!out.is_open()){
            return -1;
        }
        out<<"Frequencia:  "<<frequencia<<endl<<"Tempo de execuчуo:  "<<tempo<<endl<<"Numero de interacoes:  "<<interacoes<<endl<<"TIME ON: " << timeon<<endl<<"TIME OFF:  " <<timeoff;
        out.close();
        return 0;
}

void gerador(float frequencia,float tempoExec, float DC ) //Funcao que gera os sinais nas portas da placa e calcula a frequencias e o tempo de execucao 
{
    float timeOn, timeOff, timeStop, periodo= PRECISAO/frequencia,timeStopON=0,timeStopOFF=0;
    int it=0;
    wiringPiSetup(); //Inicializa a WiringPi
    pinMode(0,OUTPUT); //Ativa o gpio 17 (pino 11) para output
    if((DC>=0)&&(DC<=100)&&(tempoExec>=0)){ // Verifica se o DC esta em um intervalo valido
        timeOn=periodo*(DC/100);
        timeOff=periodo-timeOn;

            auto begin = std::chrono::high_resolution_clock::now(); //Capta o tempo  inicial

        do{
	    auto beginON = std::chrono::high_resolution_clock::now(); //Inicializa a contagem do tempo da porta ligada
            digitalWrite(0,HIGH); //Liga a porta
            usleep(timeOn); //Espera o tempo designado para deixar a porta ligada
	     auto endON = std::chrono::high_resolution_clock::now(); //Finaliza a contagem do tempo ligada
            auto durationON = std::chrono::duration_cast<std::chrono::nanoseconds>(endON-beginON).count(); //Calcula a variacao do tempo
	    timeStopON+=durationON/(double)NANO; //Converte a variacao do tempo de nanosegundos para segundos
	    auto beginOFF = std::chrono::high_resolution_clock::now(); //Inicializa a contagem do tempo da porta desligada
            digitalWrite(0,LOW); //Desliga a porta
            usleep(timeOff); //Espera o tempo designado para deixa a porta desligada
	    auto endOFF = std::chrono::high_resolution_clock::now(); //Finaliza a contagem do tempo desligada 
            auto durationOFF = std::chrono::duration_cast<std::chrono::nanoseconds>(endOFF-beginOFF).count(); //Calcula a variacao do tempo
	    timeStopOFF+=durationOFF/(double)NANO; //Converte a variacao do tempo de nanosegundos para segundos
	    auto end = std::chrono::high_resolution_clock::now(); //Capta o tempo final
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count(); //Calcula a variacao do tempo total
	    timeStop=duration/(double)NANO; //Converte a variacao do tempo total de nanosegundos para segundos
	    it++; //Incrementa o numero de iteracoes
        }while(timeStop<tempoExec); //Condicao de parada e o tempo de execucao

    }
    gravar(it/timeStop,timeStop,it,timeStopON,timeStopOFF);
}
int main() //Funcao principal
{
    float frequencia, DC, tempoExec;
    //Solicita ao usuario os valores da frequencia, tempo de execucao e porcentagem do tempo ON do DC (tempo OFF e subentendido pelo programa)
    cout<<"Frequencia: ";
    cin>>frequencia;
    cout<<"Tempo de execucao: ";
    cin>>tempoExec;
    cout<<"Duty cicle: ";
    cin>>DC;
    gerador(frequencia,tempoExec,DC);

    return 0;
}
