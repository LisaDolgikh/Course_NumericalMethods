import numpy as np
import math as m
import matplotlib.pyplot as plt

def read_data(file_address):
    nodes = []
    values_Ln = []
    values_Pn = []
    funcs = []
    
    with open(file_address, 'r') as file:
        for line in file:
            node, value_Ln, value_Pn, func = line.strip().split()
            nodes.append(float(node))
            values_Ln.append(float(value_Ln))
            values_Pn.append(float(value_Pn))
            funcs.append(float(func))
    
    return nodes, values_Ln, values_Pn, funcs

# Путь к файлу с данными
#file_address = '/var/home/student/3/out.txt'
#file_address = '/users/4/409/Dolgikh_EY/sem7/3/out.txt'
file_address = 'C:\\msys64\\home\\Елизавета\\sem7\\3\\out.txt'

# Чтение данных
nodes, values_Ln, values_Pn, funcs = read_data(file_address)


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
    y = 1*(x < 0.6) * (x > 0.3)
else:
    y = 0

diff1 = []
diff2 = []
nodes2 = []

for i in range(len(nodes)):
    nodes2.append(nodes[i])

for i in range(len(funcs)):
    diff1.append(funcs[i] - values_Ln[i])
    diff2.append(funcs[i] - values_Pn[i])

fig, axs = plt.subplots(2, figsize=(6, 6))
fig.suptitle('1/(1+25x^2), t = 1')

axs[0].plot(x, y, color='g', label = '$y = f(x)$')
axs[0].plot(nodes, values_Ln, color = 'blue', label = 'L_N(x)', marker = '+', markersize = 4, alpha = 0.8, linewidth = 0.8, markeredgecolor = 'purple')
axs[0].set_xlabel('x')
axs[0].set_ylabel('y')
axs[0].set_title('Приближение с помощью многочлена Лагранжа')
axs[0].grid(alpha=0.2, linestyle = '--')
axs[0].legend()

axs[1].plot(x, y, color='g', label = '$y = f(x)$')
axs[1].plot(nodes, values_Pn, color='magenta', label = 'P_(N-1)(x)', marker = '+', markersize = 4, alpha = 0.8, linewidth = 0.8, markeredgecolor = 'red')
axs[1].set_xlabel('x')
axs[1].set_ylabel('y')
axs[1].set_title('Приближение с помощью решение системы методом Гаусса')
axs[1].grid(alpha=0.2, linestyle = '--')
axs[1].legend()

'''
axs[2].plot(nodes, diff1, color = 'blue', label = '$error_L$', marker = '+', markersize = 4, alpha = 0.6, linewidth = 0.8, markeredgecolor = 'purple')
axs[2].set_xlabel('x')
axs[2].set_ylabel('y')
axs[2].set_title('Разность при Лагранже')

axs[3].plot(nodes, diff2, color = 'magenta', label = '$error_P$', marker = '+', markersize = 4, alpha = 0.6, linewidth = 0.8, markeredgecolor = 'red')
axs[3].set_xlabel('x')
axs[3].set_ylabel('y')
axs[3].set_title('Разность при решении СЛУ')
'''
fig.tight_layout()
plt.show()

