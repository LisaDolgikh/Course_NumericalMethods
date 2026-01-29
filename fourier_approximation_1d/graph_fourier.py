import matplotlib.pyplot as plt
import numpy as np

def read_data(file_address):
    massive_point = []
    massive_value = []
    massive_func = []
    
    with open(file_address, 'r') as file:
        for line in file:
            point, value, func = line.strip().split()
            massive_point.append(float(point))
            massive_value.append(float(value))
            massive_func.append(float(func))
    
    return massive_point, massive_value, massive_func

file_address = '//var//home//student//1d//out.txt'
#file_address = 'C:\\msys64\\home\\Елизавета\\sem7\\1d\\out.txt'

massive_point, massive_value, massive_func = read_data(file_address)


# Построение точечного графика
x = np.linspace(0, 1, 100)

plt.plot(massive_point, massive_value, color = 'magenta', label = 'Fourier', marker = '+', markersize = 4, alpha = 0.6, linewidth = 0.8, markeredgecolor = 'red')

#plt.plot(massive_point, massive_func, linewidth = 1, color='g', label = '$y = u(x)$')

# НОМЕР ФУНКЦИИ
NUMBER = 1

if(NUMBER == 1):
    y = x*x - 2*x
elif(NUMBER == 2):
    y = x*x*x - 3*x
elif(NUMBER == 3):
    y = np.sin(np.pi * x / 2)
elif(NUMBER == 4):
    y = 1 / (1 + 25 * (x-1) * (x-1)) - 1/26
elif(NUMBER == 5):
    x = [0, 0.3999, 0.40000001, 0.599999, 0.6, 1]
    y = [0, 0, 1, 1, 0, 0]
else:
    y = x

'''match NUMBER:
    case 1:
        y = x*x - 2*x
    case 2:
        y = x*x*x - 3*x
    case 3:
        y = np.sin(np.pi * x / 2)
    case 4:
        y = 1 / (1 + 25 * (x-1) * (x-1)) - 1/26
    case 5:
        x = [0, 0.3999, 0.40000001, 0.599999, 0.6, 1]
        y = [0, 0, 1, 1, 0, 0]
        #y = 1 if ((x > 0.4) and (x < 0.6)) else 0
    case _:
        y = x
'''
plt.plot(x, y, linewidth = 1, color='blue', alpha = 0.6, label = '$y = u(x)$')#(x-1)*(x-1) - 1)#np.sin(np.pi *0.5 * x))
plt.title('График функции N')
plt.xlabel('x')
plt.ylabel('y')
plt.grid(alpha=0.5, linestyle = '--')
plt.legend()
plt.show()
