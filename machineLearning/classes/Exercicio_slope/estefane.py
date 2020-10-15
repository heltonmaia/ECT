import numpy as np
import matplotlib.pyplot as plt

# Definindo a função principal quadrática f(x)
def f(x):
  return 3*x**2-4*x

# Definindo sua derivada (slope)
def slope(x,h):
  return (f(x+h)-f(x))/h

# Definindo o dados para o eixo x. 
x = np.linspace(-10,10,100)

# Escolhendo os pontos x e y para plotar a linha tangente
x1=5
y1=f(x1)

# função para calcular a linha tangente
def linha(x,x1,y1):
  a = slope(x1,0.01)
  return y1+a*(x-x1)

# Formatando em um range a reta tangente para visualização
r = np.linspace(x1-3,x1+3,20) 

# Plotando figura com o matplotlib
plt.plot(r,linha(r,x1,y1))
plt.plot(x,f(x))
plt.scatter(x1,y1,color='r')
plt.show()
