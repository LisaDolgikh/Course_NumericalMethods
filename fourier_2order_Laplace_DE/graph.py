import matplotlib.pyplot as plt
import numpy as np
import math as m

def read_data(file_address):
    massive_x = []
    massive_error = []
    
    with open(file_address, 'r') as file:
        for line in file:
            x, error= line.strip().split()
            massive_x.append(float(x))
            massive_error.append(float(error))
    
    return massive_x, massive_error

#file_address = '//var//home//student//1//out.txt'
#file_address = '/users/4/409/Dolgikh_EY/sem8/1/out.txt'
file_address = 'C:\\msys64\\home\\Елизавета\\sem8\\1\\out.txt'

massive_x, massive_error = read_data(file_address)

h = 1 / (len(massive_x) - 1.5)
net = np.linspace(0, 1 + h / 2, len(massive_x))
x = np.linspace(0, 1 + h / 2, 1000)

#y = - x * (x - 2) / 2

def y(x):
    C = - 1 / ((np.exp(1))**2 + 1)
    return C * np.exp(x) + C * np.exp(1) * np.exp(1) * np.exp(- x) + 1

fig, axs = plt.subplots(2, figsize=(6, 6))

axs[0].plot(x, y(x), color='g', label=r"Теоретическое решение:  $y = C e^x + C e^2 e^{-x} + 1$, где $C = -\frac{1}{ 1 + e^2}$")
'''
fig, axs = plt.subplots(2, figsize=(6, 6))

axs[0].plot(x, y, color='g', label=r"Теоретическое решение: $y = \frac{-x(x-2)}{2}$")
'''
axs[0].plot(net, massive_x, color = 'blue', label="Результат работы программы", marker = '+', markersize = 4, alpha = 0.8, linewidth = 0.8, markeredgecolor = 'purple')
axs[0].set_xlabel('x')
axs[0].set_ylabel('u(x)')
#axs[0].set_title(r"Метод Фурье, задача $-y'' = 1, \quad y(0) = y'(1) = 0$")
axs[0].set_title(r"Метод Фурье, задача $-y'' + y = 1, \quad y(0) = y'(1) = 0$")
axs[0].grid(alpha=0.2, linestyle = '--')
axs[0].legend()

axs[1].plot(net, massive_error, color='magenta', label="Разность теоретического и численного решений", marker = '+', markersize = 4, alpha = 0.8, linewidth = 0.8, markeredgecolor = 'red')
axs[1].set_xlabel('x')
axs[1].set_ylabel('|u(x) - u_theor(x)|')
axs[1].set_title(r"Ошибка при решении")
axs[1].grid(alpha=0.2, linestyle = '--')
axs[1].legend()

plt.savefig("out.pdf")
plt.show()
