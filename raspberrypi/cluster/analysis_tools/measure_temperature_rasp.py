# -*- coding: utf-8 -*-
"""
Created on Wed Aug  8 11:28:24 2018

@author: joanderson
"""

import RPi.GPIO as gpio
import os
import time
import subprocess



def measure_temp():
    temp = os.popen("sudo vcgencmd measure_temp").readline()
    return (temp.replace("temp=",""))
def temp_cpu():
        
    a =open("/sys/class/thermal/thermal_zone0/temp")
    temp = a.readline()
    a.close()
    return (float (temp.replace("temp=","")))/1000

def main():
    PIN = 18

    gpio.setmode(gpio.BCM)
    gpio.setup(PIN, gpio.IN, pull_up_down = gpio.PUD_DOWN)
    gpio.add_event_detect(PIN, gpio.RISING)
    
    node= os.popen("uname -n").readline()
    node = node.split('\n')[0] 
    nome_Arquivo =  node + 'Tempertatura_'+ \
                    time.strftime('_%l.%M.%S_%d.%m.%Y')+'.txt'
    arquivo = open(nome_Arquivo,'w')

    while True :
        if gpio.event_detected(PIN):
            break;
    while True:
        if gpio.event_detected(PIN):
           break;       
        arquivo.writelines(time.strftime('Horario da captura: %l:%M:%S %p %Z on %d \
        , %Y; ')+ 'Temperatura na CPU: '+str(temp_cpu())+'; Temperatura na GPU \
        :'+measure_temp())
        time.sleep(1)
    arquivo.close()
    diretorio = "hduser@master:/home/hduser/HadoopDados"
    subprocess.call(["scp",nome_Arquivo,diretorio])
main()