import serial
import subprocess
import time

porta = '/dev/ttyACM0'

ser = serial.Serial(port=porta,baudrate=9600,timeout=2)

while(ser.isOpen() == False):
    ser.open()
print("Comunicacao Serial Disponivel")

ser.reset_input_buffer()
ser.reset_output_buffer()

ser.write(bytes("i","utf-8"))
time.sleep(60)
subprocess.call(["/opt/hadoop/bin/hadoop","jar","/opt/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-examples-2.7.5.jar","pi","4","2"])
time.sleep(60)
ser.write(bytes("t","utf-8"))