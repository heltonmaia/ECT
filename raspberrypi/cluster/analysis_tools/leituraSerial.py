#Manual de execucao do codigo:
#1 - Compile o codigo do Arduino, com a variavel "porta" atualizada com a porta em que o Arduino esta conectado
#2 - Compile este codigo
#3 - digite '1' no serial monitor do Arduino, fazendo comecar a comunicacao serial e simultaneamente este codigo guarde os valores num arquivo .txt
#4 - dogote '0' no serial monitor do Arduino, fazendo parar a comunicacao serial

import serial
import time
#Necessario atualizar a porta quando executar
porta = '/dev/ttyACM0'
#Atualizacao do nome do arquivo a partir do horario
nome_arquivo = time.strftime('(%l:%M:%S): %d\%m\%Y - ') + 'dadosCorrenteTeste.txt'
#Criando o arquivo com o nome dado e declarado para editar, 'w' - write
arquivo = open('/home/helton/Área de Trabalho/arduino_measureCurrent/' + nome_arquivo,'w')
#Declarando "ser" para comunicacao serial
ser = serial.Serial(port=porta,baudrate=9600,timeout=2)
#Verificando se a comunicacao serial foi iniciada
while(ser.isOpen() == False):
    ser.open()
print("Comunicacao Serial Disponivel")
#Variavel auxiliar para guardar o tempo de execucao
segExec = time.perf_counter()
#Variavel que determina o momento para que comece a serem lidos os valores via serial 
habilitar = False
#Resetando a leitura serial
ser.reset_input_buffer()
ser.reset_output_buffer()
#Verificacao para comecar, timeout = 2, quando o Arduino comunicar um caractere via serial
while habilitar == False:
    if ser.in_waiting:
        segExec = time.perf_counter()
        habilitar = True
        print("Inicio: " + time.strftime('%l:%M:%S'))
        ser.reset_input_buffer()
        ser.reset_output_buffer()
#Pegando os valores a cada 1 segundo no monitor serial
while habilitar == True:
    #Escrevendo os valores no documento criado guardando o tempo de cada leitura
    segExec = time.perf_counter()
    leituraSerial = str(ser.read(size = 5), 'iso-8859-1')
    arquivo.write(time.strftime('(%l:%M:%S): ') + leituraSerial + '\n')
    ser.reset_input_buffer()
    ser.reset_output_buffer()
    #Condicao de parada via serial
    if 2.00 + segExec < time.perf_counter():
        habilitar = False
        print("Fim")

arquivo.close()