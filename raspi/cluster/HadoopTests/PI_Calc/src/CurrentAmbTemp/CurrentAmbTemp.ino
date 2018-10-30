#include <Adafruit_Sensor.h>
#include <virtuabotixRTC.h>
#include <DHT.h>
#include <DHT_U.h>
#include <SPI.h>
#include <SD.h>

#define DHTPIN 2         // Pin which is connected to the DHT sensor.

// Uncomment the type of sensor in use:

#define DHTTYPE  DHT22     // DHT 22 (AM2302)

DHT_Unified dht(DHTPIN, DHTTYPE);

File MyFile;

uint32_t delayMS;

// Creation of the Real Time Clock Object
virtuabotixRTC myRTC(6, 7, 8);

//Para dar inicio a leitura, digite 'i'. Para terminar, digite 't'.

float corrente = 0.0;
float leitura = 0.0;
float tempAux = 0.0;

boolean habilitar = false;
char input;
int medPorSeg = 10;
int auxTime = 1000/medPorSeg;
int contadorAux = 2;

//Porta digital em que sera mandando o pulso para medir temperatura na Rasp
int sinal = 9;
//Porta analogica em que sao medidos os valores de corrente do sensor
int sensorCurrent = A0;
//Valores que o Arduino vai ler de tensao por bit (5V / 1023 bits)
float voltsPorUnidade = 5.00/1023.00;
//Fator de conversao de tensao pra corrente
float fator = 1000.00/66.00;
//Mapeamento de Vout do sensor considerando seus parametros, retornando o valor de tensao de saida normalizado
float mapFloat(int leitura);
String nameFile="";

void setup() {
  Serial.begin(9600); 
  // Initialize device.
  dht.begin();
  Serial.println("Current_AmbTemp Example");
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;

  // Set the current date, and time in the following format:
  // seconds, minutes, hours, day of the week, day of the month, month, year
  //myRTC.setDS1302Time(00, 36, 16, 4, 8, 8, 2018);
  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  
  pinMode(sensorCurrent, INPUT);
  pinMode(sinal, OUTPUT);
}

void loop() {
 
  // Delay between measurements.
  //delay(delayMS);

  // This allows for the update of variables for time or accessing the individual elements.                 
  myRTC.updateTime(); 
  
  
 
  // Get temperature event and print its value.
  sensors_event_t event;  
  dht.temperature().getEvent(&event);
 
  //Quando ha algo para ser lido na comunicaçao serial
  if(Serial.available() > 0){
    
    input = Serial.read();
    
    if(input == 'i'){
      Serial.println("AbrindoLeituras");
      // open the file. note that only one file can be open at a time,
      // so you have to close this one before opening another.
      MyFile = SD.open("leituras.csv", FILE_WRITE);
      nameFile="";
      nameFile.concat("Current_AmbTemp_");
      nameFile.concat(String(myRTC.dayofmonth));
      nameFile.concat( ".");
      nameFile.concat(String(myRTC.month));
      nameFile.concat('.');
      nameFile.concat(String(myRTC.year ));
      nameFile.concat('_'); 
      nameFile.concat(String(myRTC.hours));
      nameFile.concat('.'); 
      nameFile.concat(String(myRTC.minutes));
      nameFile.concat('.'); 
      nameFile.concat(String(myRTC.seconds));
      nameFile.concat(".csv");
      
      MyFile.println(nameFile);
      
      //Sinal digital para habilitar leitura de temperatura
      //CUIDADO!! Realizar divisor de tensao para o sinal nao passar de 3.3V na placa Rasp
      digitalWrite(sinal, HIGH);
      delay(1);
      
      //Comunicacao serial para habilitar a execucao do codigo Python
      //Serial.print('i');
      //Habilitar o codigo de leitura de corrente
      habilitar = true;
      //Encerrando o pulso dado para a placa para medir temperatura
      digitalWrite(sinal, LOW);
    }
    
    if(input == 't'){
      Serial.println("FechandoLeituras");
      //Sinal digital para desabilitar leitura de temperatura
      //CUIDADO!! Realizar divisor de tensao para o sinal nao passar de 3.3V na placa Rasp
      digitalWrite(sinal, HIGH);
      delay(1);
      //Comunicacao serial para parar a execucao do codigo Python
      //Serial.print('t');
      //Desabilitar o codigo de leitura de corrente
      habilitar = false;
      digitalWrite(sinal, LOW);
      MyFile.close();
    }
    if(input == 'l'){
      
      File dataFile = SD.open("leituras.csv");
    
      // if the file is available, write to it:
      if (dataFile) {
        while (dataFile.available()) {
          Serial.write(dataFile.read());
        }
        dataFile.close();
      }
      // if the file isn't open, pop up an error:
      else {
        Serial.println("error opening leituras.csv");
      }
    }
    if(input == 'r'){
      
      SD.remove("leituras.csv");
     }
    
    
    
  }
  
  if(habilitar == true){
    
    if(contadorAux == 2){
      if (isnan(event.temperature)) {
        Serial.println("Error reading temperature!");
      }
      else {
        tempAux = event.temperature;
        contadorAux = 0;
      }
    }
    
    MyFile.print(tempAux);
    MyFile.print(",");
    
    //media de valores de corrente medidos ao longo de 1 segundo
    for(int j = 0; j < medPorSeg; j++){
      //valor lido normalizado
      leitura = mapFloat(analogRead(sensorCurrent));
      //somando corrente no tempo, convertendo: (V / (66 mV / 1 A)) = V * ( 1 A / 66 * 10e-3 V) = V * (1000/66)A/V
      corrente+= leitura*fator;
      delay(auxTime);
    }
    
    corrente/= medPorSeg;
    
    if(corrente < 0){
      corrente = -corrente;
    }
    
    MyFile.println(corrente,2);
    corrente = 0;
    contadorAux++;
    
  }
}

//Aqui, dependendo de condicoes do ambiente, de temperatura, de tempo de uso, etc., ha momentos em que o valor de 510 deva ser ajustado para 511 ou 512, para proporcionar uma medicao mais eficiente
float mapFloat(int leitura){ 
  return (leitura-510)*voltsPorUnidade;
}
