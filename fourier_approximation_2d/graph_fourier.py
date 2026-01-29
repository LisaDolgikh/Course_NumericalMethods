import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D

# НОМЕР ФУНКЦИИ
NUMBER = 2
def f(x,y, NUMBER):
    if(NUMBER == 1):
        return  np.sin(np.pi * x / 2) * np.sin(np.pi * y / 2)
    elif(NUMBER == 2):
        return (x*x - 2*x) * (y*y - 2*y)
    elif(NUMBER == 3):
        return (x*x*x - 3*x) * (y*y*y - 3*y)
    elif(NUMBER == 4):
        return (1 - np.cos(np.pi * x)) * (1 - np.cos(np.pi * y))
    elif(NUMBER == 5):
        return (np.exp(x) - np.exp(1)*x - 1)*(np.log(1 + x*x) - 2*np.log(1 + x))*(x*x - 2*x)*(np.exp(y) - np.exp(1)*y - 1)*(np.log(1 + y*y) - 2*np.log(1 + y))*(y*y - 2*y)
    elif(NUMBER == 6):
        return x*y
    else:
        return x*y

def read_data(file_address):
    with open(file_address, 'r') as file:
        coef = np.loadtxt(file)
    return coef

def u(x, y, coef):
    n = coef.shape[0]
    u = 0
    for i in range(1,n):
        for j in range(1,n):
            u += coef[i, j] * np.sin((i - 0.5) * np.pi * x) * np.sin((j - 0.5) * np.pi * y)
    return u


#file_address = '//var//home//student//2d//out.txt'
file_address = 'C:\\msys64\\home\\Елизавета\\sem7\\2d\\out.txt'

coef = read_data(file_address)

N = 2*coef.shape[0]

x = np.linspace(0, 1, N)
y = np.linspace(0, 1, N)
X, Y = np.meshgrid(x, y)
    
# Вычисляем f(x, y)
Z_f = f(X, Y, NUMBER)
    
# Вычисляем u(x, y)
Z_u = np.zeros_like(Z_f)
for i in range(len(x)):
    for j in range(len(y)):
        Z_u[i, j] = u(x[i], y[j], coef)
    
# Вычисляем разность f(x, y) - u(x, y)
Z_diff = Z_f - Z_u

fig = plt.figure('''figsize=(8, 8), dpi = 300''')
ax = fig.add_subplot(1, 2, 1, projection='3d')

ax.plot_surface(X, Y, Z_u, cmap = 'coolwarm', edgecolor='blue', alpha=0.7)

ax.plot_wireframe(X, Y, Z_f, color='black', label = 'Исходная функция', linestyle = '--', linewidth = 0.3)
ax.set_title('Исходная и восстановленная функция')
ax.set_xlabel('$x$')
ax.set_ylabel('$y$')
ax.set_zlabel('$f(x, y)$')
ax.legend()

ax = fig.add_subplot(1, 2, 2, projection='3d')

df = ax.plot_surface(X, Y, Z_diff, cmap='coolwarm', edgecolor='black', linewidth = 0.1, linestyle = '--')

ax.set_title('График погрешности')
ax.set_xlabel('$x$')
ax.set_ylabel('$y$')

plt.tight_layout()
plt.show()