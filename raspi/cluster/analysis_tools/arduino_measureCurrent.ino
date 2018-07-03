//Para dar inicio a leitura, digite '1'. Para terminar, digite '0'.

double corrente = 0;
double leitura = 0;
boolean habilitar = false;
char input;
int medPorSeg = 100;
int auxTime = 1000/medPorSeg;
//Porta digital em que sera mandando o pulso para medir temperatura na Rasp
int sinal = 4;
//Porta analogica em que sao medidos os valores de corrente do sensor
int sensor = A3;
//Valores que o Arduino vai ler de tensao por bit (5V / 1023 bits)
double voltsPorUnidade = 5.00/1023.00;
//Mapeamento de Vout do sensor considerando seus parametros, retornando o valor de tensao de saida normalizado
double mapFloat(int leitura);

void setup(){
  Serial.begin(9600);
  pinMode(sensor, INPUT);
   pinMode(sinal, OUTPUT);
}

void loop(){  
  //Quando ha algo para ser lido na comunicaçao serial
  if(Serial.available() > 0){
    input = Serial.read();
    if(input == '1'){
      //Sinal digital para habilitar leitura de temperatura
      //CUIDADO!! Realizar divisor de tensao para o sinal nao passar de 3.3V na placa Rasp
      digitalWrite(sinal, HIGH);
      //Comunicacao serial para habilitar a execucao do codigo Python
      Serial.println('1');
      //Habilitar o codigo de leitura de corrente
      habilitar = true;
    }
    if(input == '0'){
      //Sinal digital para desabilitar leitura de temperatura
      //CUIDADO!! Realizar divisor de tensao para o sinal nao passar de 3.3V na placa Rasp
      analogWrite(sinal, 123);
      //Comunicacao serial para parar a execucao do codigo Python
      Serial.println('0');
      //Desabilitar o codigo de leitura de corrente
      habilitar = false;
    }
  }
  if(habilitar == true){
    //Encerrando o pulso dado para a placa para medir temperatura
    digitalWrite(sinal, LOW);
    //media de valores de corrente medidos ao longo de 1 segundo
    for(int j = 0; j < medPorSeg; j++){
      //valor lido normalizado
      leitura = mapFloat(analogRead(sensor));
      //somando corrente no tempo, convertendo: (V / (66 mV / 1 A)) = V * ( 1 A / 66 * 10e-3 V) = V * (1000/66)A/V
      corrente+= leitura*(1000.00/66.00);
      delay(auxTime);
    }
    corrente/= medPorSeg;
    if(corrente < 0){
      corrente = -corrente;
    }
    Serial.print(corrente,2);
    Serial.print(',');
    corrente = 0;
  }
}
//Aqui, dependendo de condicoes do ambiente, de temperatura, de tempo de uso, etc., ha momentos em que o valor de 510 deva ser ajustado para 511 ou 512, para proporcionar uma medicao mais eficiente
double mapFloat(int leitura){ 
  return (leitura-510)*voltsPorUnidade;
}
