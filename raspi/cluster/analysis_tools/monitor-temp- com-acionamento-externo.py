# -*- coding: utf-8 -*-
import Rpi.GPIO as gpio
import os
import time

num = open('numeroTeste.txt','r')
teste = int(num.readline())
num = open('numeroTeste.txt','w')
num.writelines(str(teste+1))
num.close()

PIN = 18

gpio.setmode(gpio.BCM)
gpio.setup(PIN, gpio.IN, pull_up_down = gpio.PUD_DOWN)
gpio.add_event_detect(PIN, gpio.RISING)


nome_Arquivo = ('dadosTempertatura_Teste_'+str(teste)  +'.txt') 
arquivo = open(nome_Arquivo,'w')


def measure_temp():
    temp = os.popen("vcgencmd measure_temp").readline()
    return (temp.replace("temp=",""))
def temp_cpu():
        
    a =open("/sys/class/thermal/thermal_zone0/temp")
    temp = a.readline()
    a.close()
    return (float (temp.replace("temp=","")))/1000

x = 0
flag = False;
while True :
    if gpio.event_detected(PIN):
        break;
while x<(60):
   if gpio.event_detected(PIN):
       flag = True
       
   
   # now = datetime.now()
   # print now.hour
   # print time.strftime('%l:%M:%S %p %Z on %b %d, %Y')
    arquivo.writelines(time.strftime('Horario da captura: %l:%M:%S %p %Z on %d\
    , %Y; ')+ 'Temperatura na CPU: '+str(temp_cpu())+'; Temperatura na GPU \
    :'+measure_temp())

    time.sleep(1)
    if flag:
        x=x+1
arquivo.close()

