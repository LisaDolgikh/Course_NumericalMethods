import matplotlib.pyplot as plt
import numpy as np

p = []

def read_data(file_address):
    massive_lognorm = []
    massive_logN = []
    
    with open(file_address, 'r') as file:
        for line in file:
            lognorm, logN = line.strip().split()
            massive_lognorm.append(float(lognorm))
            massive_logN.append(float(logN))
    
    return massive_lognorm, massive_logN

file_address = '//var//home//student//1d//out.txt'
#file_address = 'C:\\msys64\\home\\Елизавета\\sem7\\1d\\out.txt'

massive_lognorm, massive_logN = read_data(file_address)

for n in range(len(massive_lognorm) - 2):
    p.append((massive_lognorm[n+1]- massive_lognorm[n]) / (massive_logN[n+1]- massive_logN[n]))

p_res = 0
for i in range(len(massive_lognorm) - 2):
    p_res += p[i]
p_res /= (len(massive_lognorm) - 2)


print("Показатель сходимости p = ", p_res)

plt.plot(massive_logN, massive_lognorm, linewidth = 1, color='r', label = '$p(\Delta N)$', marker = 'o')
plt.title(f'Показатель сходимости для функции')
plt.xlabel('ln(N)')
plt.ylabel('-ln(err)')
plt.grid(alpha=0.5, linestyle = '--')
plt.legend()
plt.show()
