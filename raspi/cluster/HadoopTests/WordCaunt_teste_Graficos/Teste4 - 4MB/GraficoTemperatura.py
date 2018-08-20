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


def GerarGraficos(palavra):
    #palavra = "Node1Temperature_6.04.14_10.08.2018.txt"
    #cores = ["black","red","green", "blue"]
    dados_horario,dados_temperatura_cpu,dados_temperatura_gpu = ExtrairDados(\
    palavra)
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
    maior = int(max(max(dados_temperatura_cpu),max(dados_temperatura_cpu))+1)
    menor = int(min(min(dados_temperatura_cpu),min(dados_temperatura_gpu))-1)
    

    ax = plt.subplot()
    
    plt.ylim(menor,maior)
    plt.xlim(0,len(x))
    plt.plot(x,ysCPU,'r--',color='red',label = 'CPU',linewidth=3)
    plt.plot(x2,ysGPU,color = 'black',label = 'GPU',linewidth=1)
    box = ax.get_position()
    ax.set_position([box.x0, box.y0, box.width * 0.8, box.height])
    ax.legend(loc='center left', bbox_to_anchor=(1, 0.835))        #print(palavra)
    plt.savefig(palavra.split(".txt")[0]+ "GraficoTemperatura.eps")
    plt.close()


def GraficoCPU():
    Nodes = ["Node1","Node2","Node3", "Node4"]
    cores = ["black","red","green", "blue"]    
    X = []
    Y = []
    Coeficientes = []
    PolinomeiosCPU = []    
    YS_CPU = []
    Maior_temperatura = -1
    Menor_temperatura = -1
    horario = ""
    arq = open("nome_arquivos.txt",'r')
    texto = arq.readlines()
    arq.close()  
    for linha in texto:
        linha = linha.split('\n')[0] 
        dados_horario,dados_temperatura_cpu,dados_temperatura_gpu = ExtrairDados(\
        linha)
        GerarGraficos(linha)
        x = range(0,len(dados_temperatura_cpu))
        y = dados_temperatura_cpu
        X.append(x)    
        Y.append(y)
        
        coeficientes = np.polyfit(x,y,100)
        Coeficientes.append(coeficientes)    
    
        polinomeioCPU = np.poly1d(coeficientes)
        PolinomeiosCPU.append(polinomeioCPU)
        ysCPU = polinomeioCPU(x)
        YS_CPU.append(ysCPU)   
    
        maior = float(max(max(dados_temperatura_cpu),max(dados_temperatura_cpu)))
        menor = float(min(min(dados_temperatura_cpu),min(dados_temperatura_gpu)))
        if(Maior_temperatura == -1):
            Maior_temperatura = maior
            horario = (linha.split(".txt")[0]).split('_')
        else:
            if(Maior_temperatura<maior):
                Maior_temperatura = maior
        
        if(Menor_temperatura == -1):
            Menor_temperatura = menor
        else:
            if(Menor_temperatura>menor):
                Menor_temperatura = menor
    
    horario = horario[1]+'_' + horario[2]
    
    ax = plt.subplot()        
    plt.ylabel("Temperatura(c)")
    plt.title("Temperatura da CPU")
    plt.xlabel("Tempo(s)")   
    plt.ylim(Menor_temperatura-1,Maior_temperatura+1)
    plt.xlim(0,len(X[0]))
    #plt.plot(x,ysCPU,'r--',color='red',label = 'CPU',linewidth=3)
    for i in range(0,4):
        plt.plot(X[i],YS_CPU[i],color = cores[i],label = Nodes[i],linewidth=1)
    box = ax.get_position()
    ax.set_position([box.x0, box.y0, box.width * 0.8, box.height])
    ax.legend(loc='center left', bbox_to_anchor=(1, 0.835))    
    plt.savefig("GraficoTemperatura_CPU.eps")
    plt.close()
    
def  main():
    GraficoCPU()  

main()
#main("Node1Temperature_6.04.14_10.08.2018.txt")    
