import serial
import subprocess
import time
#subprocess.call(["sudo","chmod","777","/dev/ttyACM1)"])
porta = '/dev/ttyACM0'
baudrate = 9600

def StartTest ():
    ser = serial.Serial(porta,baudrate,timeout=2)
    ser.write(bytes("i","utf-8"))
    VALUE_SERIAL = ser.read()
    print( '\nRetorno da serial: %s' % (VALUE_SERIAL))
    time.sleep(10)
    #subprocess.call(["/opt/hadoop/bin/hadoop","jar","/opt/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-examples-2.7.5.jar","pi","4","2"])
   #time.sleep(60)
    subprocess.call(["uname","-a"])
    ser.write(bytes("t","utf-8"))
    time.sleep(10)
    ser.close()
"""
while(ser.isOpen() == False):
    ser.open()
print("Comunicacao Serial Disponivel")

ser.reset_input_buffer()
ser.reset_output_buffer()
"""
cont = 1
while (cont <= 5):
    StartTest()
    cont = cont + 1
