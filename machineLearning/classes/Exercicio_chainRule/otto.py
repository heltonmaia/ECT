# Cálculo para Machine Learning. ==============================================
# ECT2703 - TÓPICOS AVANÇADOS EM INFORMÁTICA II.
# Otto Braga de Oliveira.

# Módulos. ====================================================================

import numpy as np
import matplotlib.pyplot as plt
import sympy as sp


# Definição de derivada. ======================================================

print('\n________ Definicao de derivada.\n')

# Definindo a função principal quadrática f(x).

def f(x) :
    return 3 * x ** 2 - 4 * x

# Definindo a derivada (Df).

def Df(x, h=10**(-8)):
   return (f(x+h) - f(x)) / h

# Escolhendo os pontos x e y para plotar a linha tangente.

x0 = -7.5
y0 = f(x0)

print('\nFUNÇÃO:\n')
print('f(', x0, ') = ', f(x0), '\n')

print('\nDERIVADA:\n')
print('Df(', x0, ') = ', Df(x0), '\n')

# Definindo o dados para o eixo x.

x = np.linspace(-10, 10, 128)

# Definindo a função para calcular a linha tangente.

def slopeLine(x, x0, y0) :
    return Df(x0) * (x - x0) + y0

# Formatando em um range a reta tangente para visualização.

slopeLineXRange = np.linspace(x0-3, x0+3, 64)

# Plotando figura.

plt.plot(x, f(x), c='black', linewidth=2)
plt.scatter(x0, y0, color='black')
plt.plot(slopeLineXRange, slopeLine(slopeLineXRange, x0, y0), c='r', linewidth=1)
plt.xlabel('x')
plt.ylabel('f(x)')
plt.savefig('fig_00.png')
plt.savefig('fig_00.svg')
plt.clf()




# SymPy. ======================================================================

print('\n________ SymPy.\n')

x, y = sp.symbols('x y')
f_xy = x**2 + 2 * y + y**3
print("f(x,y) = {} ".format(f_xy))

# Usando o sympy.Derivative() method 
Dxf_xy = sp.diff(f_xy, x)
Dyf_xy = sp.diff(f_xy, y)

print("Dxf(x, y) = {}".format(Dxf_xy))
print("Dyf(x, y) = {}".format(Dyf_xy))




# Exercício. ==================================================================

print('\n________ Exercício.\n')

# Definindo f(x) e calculando Df(x).

x = sp.symbols('x')

f_x = (3*x**2 - 5*x + 2)**6
print('f(x) = ', f_x)

Df_x = sp.diff(f_x, x)
print('Df(x) = ', Df_x)

# Expressão algébrica da linha tangente.

x_0 = sp.symbols('x_0')
y_0 = sp.symbols('y_0')

Df_xLine = Df_x * (x - x_0) + y_0
print('Expressao da linha tangente: ', Df_xLine)

# Redefinindo f(x) e calculando Df(x) (função derivada definida anteriormente).

def f(x):
    return (3*x**2 - 5*x + 2)**6

x = 40

print('f(', x, ') = ', f(x))
print('Df(', x, ') = ', Df(x))

# Definindo o intervalo de x que constitui o domínio de f(x).

xRange = np.linspace(-50, 50, 2048)

# Definindo intervalo de x para calcular os pontos da linha tangente.

DfLineXRange = np.linspace(x-10, x+10, 512)

# Definindo nova função para calcular os pontos da linha tangente.

def DfLine(x_0, x_1):
    return Df(x_0) * (x_1 - x_0) + f(x_0)

# Plotando para vários valores de x.

numberOfPlots = 7
xValues = [-49, -45, -40, 0, 40, 45, 49]

fig, axis = plt.subplots(nrows = numberOfPlots, ncols = 1)

fig.set_size_inches(10,25)
fig.set_facecolor('w')
fig.tight_layout()

for i, j in zip(xValues, range(numberOfPlots)) :

    axis[j].plot(xRange, f(xRange), c='black', linewidth=2)

    x = i
    axis[j].scatter(x, f(x), c='black')

    DfLineXRange = np.linspace(x-5, x+5, 512)
    axis[j].plot(DfLineXRange, DfLine(x, DfLineXRange), c='r', linewidth=1)

    axis[j].set_xlabel('x')
    axis[j].set_ylabel('f(x)')

plt.savefig('fig_01.png')
plt.savefig('fig_01.svg')
plt.clf()

