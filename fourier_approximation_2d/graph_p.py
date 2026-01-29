import matplotlib.pyplot as plt
import numpy as np
import math as m

p = []

def read_data(file_address):
    massive_N = []
    massive_norm = []
    
    with open(file_address, 'r') as file:
        for line in file:
            N, norm = line.strip().split()
            massive_N.append(float(N))
            massive_norm.append(float(norm))
    
    return massive_N, massive_norm

#file_address = '//var//home//student//2d//pval.txt'
file_address = 'C:\\msys64\\home\\Елизавета\\sem7\\2d\\pval.txt'

massive_N, massive_norm = read_data(file_address)

for n in range(len(massive_norm) - 2):
    p.append(m.log(massive_norm[n] / massive_norm[n+1]) / m.log(massive_N[n+1] / massive_N[n]))

p_res = 0
for i in range(len(massive_norm) - 2):
    p_res += p[i]
p_res /= (len(massive_norm) - 2)


print("Показатель сходимости p = ", p_res)

plt.plot(np.log(massive_N), -np.log(massive_norm), linewidth = 1, color='r', label = '$p(\Delta N)$', marker = 'o')
plt.title(f'Показатель сходимости для функции')
plt.xlabel('ln(N)')
plt.ylabel('ln(norm)')
plt.grid(alpha=0.5, linestyle = '--')
plt.legend()
plt.show()
