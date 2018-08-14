# -*- coding: utf-8 -*-
"""
Created on Wed Aug  8 11:34:46 2018

@author: joanderson
"""

import Adafruit_BBIO.GPIO as GPIO
import time
import os

#initialize the pin as an INPUT


def temp_cpu():
    a = open("/sys/class/hwmon/hwmon0/device/temp1_input")
    temp = a.readline()
    a.close()
    return (float (temp.replace("temp=","")))/1000
    

def main():    
    PIR = "P8_11"
    GPIO.setup(PIR, GPIO.IN)
    GPIO.add_event_detect(PIR, GPIO.RISING)
    
    node= os.popen("uname -n").readline()
    node = node.split('\n')[0] 
    nome_Arquivo =  'dadosTempertatura_Teste_'+ node +\
                    time.strftime('_%l.%M.%S_%d.%m.%Y')+'.txt'    
    arquivo = open(nome_Arquivo,'w')
    while True:
        if GPIO.event_detected(PIR):
            break;
    
    while True:
        if GPIO.event_detected(PIR):
            break;
        arquivo.writelines(time.strftime('Horario da captura: %l:%M:%S %p %Z on %d\
        , %Y; ')+ 'Temperatura na CPU: '+str(temp_cpu())+'; Temperatura na GPU \
        :'+ '0')
        time.sleep(1)
        
    arquivo.close()

main()
