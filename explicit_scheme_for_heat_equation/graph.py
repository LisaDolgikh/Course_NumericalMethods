import matplotlib.pyplot as plt
import numpy as np
import math as m
from mpl_toolkits.mplot3d import Axes3D

def read_data(file_address):
    massive_x = []
    massive_t = []
    massive_nodes = []
    
    with open(file_address, 'r') as file:
        lines = file.readlines()

    # Извлекаем координаты узлов x
    massive_x = np.array([float(x) for x in lines[0].split()])

    # Извлекаем t и посчитанное u(t, x)
    massive_t = []
    massive_nodes = []
    for line in lines[1:]:
        data = [float(value) for value in line.split()]
        massive_t.append(data[0])
        massive_nodes.append(data[1:])

    return massive_x, massive_t, massive_nodes

#file_address = '//var//home//student//3.1//nodes.txt'
#file_address = '/users/4/409/Dolgikh_EY/sem8/3.1/nodes.txt'
file_address = 'C:\\msys64\\home\\Елизавета\\sem8\\3.1\\nodes.txt'

massive_x, massive_t, massive_nodes = read_data(file_address)

# Преобразуем в массивы numpy
massive_t = np.array(massive_t)
massive_nodes = np.array(massive_nodes)
X, T = np.meshgrid(massive_x, massive_t)

def fun_u(t,x):
    #return (x*x - 2*x) * np.exp(- np.pi * np.pi * t / 4) #1
    #return (x*x*x-3.*x) * np.exp(- t) #2
    #return (np.sin(np.pi*x/2)) * np.exp(- np.pi * np.pi * t / 4) #3
    return x*np.exp(-x)*np.exp(t) #4

massive_u = fun_u(T, X)
massive_error = massive_nodes - massive_u

# Создаем 3D-графики
fig = plt.figure(figsize=(16, 4))

# График посчитанного u(t, x)
ax1 = fig.add_subplot(131, projection='3d')
ax1.plot_surface(T, X, massive_nodes, cmap='viridis')
ax1.set_title('Численное решение')
ax1.set_xlabel('t')
ax1.set_ylabel('x')
ax1.set_zlabel('u(t, x)')

# График точного u*(t, x)
ax2 = fig.add_subplot(132, projection='3d')
ax2.plot_surface(T, X, massive_u, cmap='plasma')
ax2.set_title('Точное решение')
ax2.set_xlabel('t')
ax2.set_ylabel('x')
ax2.set_zlabel('u*(t, x)')

# График разности u(t, x) - u*(t, x)
ax3 = fig.add_subplot(133, projection='3d')
ax3.plot_surface(T, X, massive_error, cmap='coolwarm')
ax3.set_title('Разность')
ax3.set_xlabel('t')
ax3.set_ylabel('x')
#ax3.set_zlabel('u(t, x) - u*(t, x)')

plt.tight_layout()
plt.show()
