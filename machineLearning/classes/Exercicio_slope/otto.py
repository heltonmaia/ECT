# Cálculo e plotagem da derivada de f(x).

# Importando módulos.

import numpy as np
import matplotlib.pyplot as plt




# Definindo a função principal quadrática f(x).

def f(x) :
    return 3 * x ** 2 - 4 * x




# Definindo a derivada (slope).

def slope(x, h=1, verbose=True):
    """
    Derivada de f(x) previamente definida.
    O parâmetro h começa igual a 1 por padrão.
    O parâmetro verbose imprime informações durante o processamento.
    """
    
    # Checa a convergência para o próximo h = h * 0.1 .
    now = (f(x+h) - f(x)) / h
    nxt = (f(x+(h*.1)) - f(x)) / (h*.1)
    if verbose : print("agora: ", now, ', próxima: ', nxt)
    
    # Checa o se o coeficiente angular está crescendo.
    if abs(f(x+h) - f(x)) > abs(f(x-h) - f(x)) :
        coefAngCresc = True
    else :
        coefAngCresc = False
    if verbose : print('\ncoeficient angular crescendo: ', coefAngCresc, '\n')

    # Condições para continuar a aproximação com h tendendo a 0.
    #
    # A cond1 é para o caso de um coeficiente angular diminuindo
    # (a curvatura da função está se achatando):
    # se a derivada for positiva, a próxima derivada "nxt" com h = h * 0.1
    # converge se for maior que a derivada atual "now" com h = h;
    # se a derivada for negativa, a próxima derivada "nxt" com h = h * 0.1
    # converge se for menor que a derivada atual "now" com h = h;
    #
    # A cond2 é para o caso de um coeficiente angular crescendo
    # (a curvatura da função está se tornando mais íngreme):
    # se a derivada for positiva, a próxima derivada "nxt" com h = h * 0.1
    # converge se for menor que a derivada atual "now" com h = h;
    # se a derivada for negativa, a próxima derivada "nxt" com h = h * 0.1
    # converge se for maior que a derivada atual "now" com h = h;
    #
    cond1 = not coefAngCresc and (now > 0 and now < nxt) or (now < 0 and now > nxt)
    cond2 = coefAngCresc and ((now > 0 and now > nxt) or (now < 0 and now < nxt))
    
    # Condicional para aproximar h de 0
    # ou retornar a derivada no limite da convergência
    # (menor valor de 0 possivel (será?)).
    if cond1 or cond2 :
        h = slope(x, h*.1, verbose)
        return h
    
    else :
        if verbose : print('\nh = ', h, '\n')
        return (f(x+(h)) - f(x)) / (h)




# Definindo o dados para o eixo x.

x = np.linspace(-10, 10, 128)




# Escolhendo os pontos x e y para plotar a linha tangente.

x0 = -7.5
y0 = f(x0)

print('\nFUNÇÃO:\n')
print('f(', x0, ') = ', f(x0), '\n')

print('\nDERIVADA:\n')
print('df(', x0, ') = ', slope(x0), '\n')




# Definindo a função para calcular a linha tangente.

def slopeLine(x, x0, y0) :
    return slope(x0, verbose=False) * (x - x0) + y0




# Formatando em um range a reta tangente para visualização

slopeLineXRange = np.linspace(x0-3, x0+3, 64)




# Plotando figura com o matplotlib

plt.plot(x, f(x), c='black', linewidth=2)
plt.scatter(x0, y0, color='black')
plt.plot(slopeLineXRange, slopeLine(slopeLineXRange, x0, y0), c='r', linewidth=1)
plt.xlabel('x')
plt.ylabel('f(x)')
plt.savefig('save.png')
plt.savefig('save.svg')
