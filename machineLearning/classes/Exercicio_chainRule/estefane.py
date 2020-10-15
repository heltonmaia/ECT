from sympy import *
import numpy as np
import matplotlib.pyplot as plt

# Definindo a função principal e sua derivada usando variáveis simbólicas
x = symbols('x')
y = (3*x**2-5*x+2)**6
dy = diff(y,'x')

# Escolhendo os pontos x e y para plotar a reta tangente
x1 = -8
y1 = y.subs(x,x1)

# função para calcular a reta tangente usando variáveis simbólicas
r = y1+dy.subs(x,x1)*(x-x1)

# Formatando em um range a função principal e reta tangente para visualização
ax = np.linspace(-10,10,100)
bx = np.linspace(x1-3,x1+3,20) 

# uso de "list comprehension" para obter os pontos da função e da reta
ay = [y.subs(x,v) for v in ax] 
by = [r.subs(x,v) for v in bx] 

# Plotando a figura com o matplotlib
plt.plot(ax,ay)
plt.plot(bx,by)
plt.scatter(x1,y1,color='r')
plt.show()
