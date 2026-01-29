import numpy as np
import math as m
import matplotlib.pyplot as plt

def read_data(file_address):
    nodes = []
    values_Pn = []
    diffs = []
    
    with open(file_address, 'r') as file:
        for line in file:
            node, value_Pn, diff = line.strip().split()
            nodes.append(float(node))
            values_Pn.append(float(value_Pn))
            diffs.append(float(diff))
    
    return nodes, values_Pn, diffs

# Путь к файлу с данными
#file_address = '/var/home/student/4/out.txt'
file_address = '/users/4/409/Dolgikh_EY/sem7/4/out.txt'
#file_address = 'C:\\msys64\\home\\Елизавета\\sem7\\4\\out.txt'

# Чтение данных
nodes, values_Pn, diffs = read_data(file_address)


# Введите номер функции
NUMBER = int(input("Номер функции: "))
a = float(input("Левый конец: "))
b = float(input("Правый конец: "))

x = np.linspace(a, b, 1000)

if(NUMBER == 1):
    y = pow(x,4) + 3 * pow(x,3) + x*x - 10
elif(NUMBER == 2):
    y = np.exp(x)
elif(NUMBER == 3):
    y = 1 / (1 + 25 * x * x) 
elif(NUMBER == 4):
    y = np.fabs(x)
elif(NUMBER == 5):
    #y = 1 * (x < 0.6) * (x > 0.3)
    y = np.exp(-x ** 2)* (np.cos(x))* (np.cos(x))
else:
    y = 0

fig, axs = plt.subplots(2, figsize=(6, 6))
fig.suptitle('|x| , t = 0')

axs[0].plot(x, y, color='g', label = '$y = f(x)$')
axs[0].plot(nodes, values_Pn, color = 'blue', label = 'P_m(x)', marker = '+', markersize = 4, alpha = 0.8, linewidth = 0.8, markeredgecolor = 'purple')
axs[0].set_xlabel('x')
axs[0].set_ylabel('y')
axs[0].set_title('Приближение с помощью алгоритма Валле-Пуссена')
axs[0].grid(alpha=0.2, linestyle = '--')
axs[0].legend()

axs[1].plot(nodes, diffs, color='magenta', label = 'f(x) - P_m(x)', marker = '+', markersize = 4, alpha = 0.8, linewidth = 0.8, markeredgecolor = 'red')
axs[1].set_xlabel('x')
axs[1].set_ylabel('y')
axs[1].set_title('Разность')
axs[1].grid(alpha=0.2, linestyle = '--')
axs[1].legend()

fig.tight_layout()
plt.show()

