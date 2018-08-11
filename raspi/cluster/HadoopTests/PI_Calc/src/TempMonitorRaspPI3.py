import RPi.GPIO as gpio
import os
import time

PIN = 18

gpio.setmode(gpio.BCM)
gpio.setup(PIN, gpio.IN, pull_up_down = gpio.PUD_DOWN)
gpio.add_event_detect(PIN, gpio.RISING)

nome_Arquivo =  'dadosTempertatura_Teste'+time.strftime('%l.%M.%S.%d.%m.%Y')+'.txt'
arquivo = open(nome_Arquivo,'w')

def measure_temp():
    temp = os.popen("sudo vcgencmd measure_temp").readline()
    return (temp.replace("temp=",""))
def temp_cpu():
        
    a =open("/sys/class/thermal/thermal_zone0/temp")
    temp = a.readline()
    a.close()
    return (float (temp.replace("temp=","")))/1000

while True :
    if gpio.event_detected(PIN):
        break;
while True:
    if gpio.event_detected(PIN):
       break
       
    arquivo.writelines(time.strftime('Horario da captura: %l:%M:%S %p %Z on %d \
    , %Y; ')+ 'Temperatura na CPU: '+str(temp_cpu())+'; Temperatura na GPU \
    :'+measure_temp())

    time.sleep(1)

arquivo.close()
