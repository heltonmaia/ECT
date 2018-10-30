# -*- coding: utf-8 -*-
"""
Created on Tue Apr 17 18:49:23 2018

@author: joanderson
"""
import matplotlib.pyplot as plt

import numpy as np


def ExtrairDados(nome_arquivo):
    arq = open(nome_arquivo,'r')
    texto = arq.readlines()
    arq.close()
    dados_horario = []
    dados_temperatura_cpu = []
    dados_temperatura_gpu = []    
    for linha in texto:
        
        divisaoDaLinha = linha.split(", ")
        horarioDaAquisicao =  divisaoDaLinha[0].split(" ")[4] +" "\
        + divisaoDaLinha[0].split(" ")[5];
        
        
        dados_horario.append(horarioDaAquisicao);#inserindo o horario no vetor
        b = divisaoDaLinha[1].split("; ")
        
        temperaturaCPU = float(b[1].split(": ")[1])     
        temperaturaGPU = float( b[2].split(":")[1].split("'")[0])
        
        dados_temperatura_cpu.append(temperaturaCPU)
        dados_temperatura_gpu.append(temperaturaGPU)
        
    return dados_horario,dados_temperatura_cpu,dados_temperatura_gpu


def main():
    
    dados_horario,dados_temperatura_cpu,dados_temperatura_gpu = ExtrairDados(\
    "DadosDaCaptura.txt")
    plt.ylabel("Temperatura(c)")
    plt.title("Temperatura da GPU e CPU")
    plt.xlabel("Tempo(s)")
    x = range(0,len(dados_temperatura_cpu))
    x2 = x;
    y = dados_temperatura_cpu
    y2 = dados_temperatura_gpu
    
    coeficientes = np.polyfit(x,y,100)
    coeficientes2 = np.polyfit(x2,y2,100); 
    polinomeioCPU = np.poly1d(coeficientes)
    polinomeioGPU = np.poly1d(coeficientes2)
    ysCPU = polinomeioCPU(x)
    ysGPU = polinomeioGPU(x2)
    maior = int(max(max(dados_temperatura_cpu),max(dados_temperatura_cpu)))
    menor = int(min(min(dados_temperatura_cpu),min(dados_temperatura_gpu)))
    
    print maior
    
   
    plt.ylim(menor,maior)
    plt.plot(x,ysCPU,'r--',color='red',label = 'CPU',linewidth=3)
    plt.plot(x2,ysGPU,color = 'black',label = 'GPU',linewidth=1)
    plt.legend()
    plt.savefig("GraficoTemperatura.eps")




main()    
