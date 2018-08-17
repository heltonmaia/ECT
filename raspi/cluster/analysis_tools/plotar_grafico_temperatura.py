#Developed by Gilvandro Cesar

import matplotlib.pyplot as plt
import numpy as np
import csv
from scipy.signal import savgol_filter

arquivo = "CurrentAmbTemp_10.8.2018_18.5.15"
leituras = csv.reader(open(arquivo + ".csv",'r'))
leituras = list(leituras)
del leituras[0]
#Evitando problema de linhas vazias no fim do arquivo .csv
if leituras[len(leituras)-1] == []:
        del leituras[len(leituras)-1]

time_max = len(leituras)
dados = np.array(leituras)
temperature = dados[:,0]
temperature = temperature.astype(np.float)
time = np.array(range(0, time_max))

#Grafico Temperatura
plt.ylabel("Temperatura (c)")
plt.title("Grafico de Temperatura Ambiente")
plt.xlabel("Tempo(s)")
plt.xlim(0, 200)
plt.ylim(22, 26)
x = time
y = savgol_filter(temperature, 51, 10)
plt.plot(x,y,color = 'black',linewidth=1)
plt.savefig("GraficoTemperatura_" + arquivo + ".eps")