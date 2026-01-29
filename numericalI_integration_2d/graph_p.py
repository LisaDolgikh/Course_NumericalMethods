import matplotlib.pyplot as plt
import numpy as np

p = []

def read_data(file_address):
    massive_logN = []
    massive_logerror = []

    
    with open(file_address, 'r') as file:
        for line in file:
            logN, logerror= line.strip().split()
            massive_logN.append(float(logN))
            massive_logerror.append(float(logerror))

    
    return massive_logN, massive_logerror

#file_address = '//var//home//student//6//res.txt'
file_address = '/users/4/409/Dolgikh_EY/sem7/6/res.txt'
#file_address = 'C:\\msys64\\home\\Елизавета\\sem7\\6\\res.txt'

massive_logN, massive_logerror = read_data(file_address)

k = 9
for n in range(k):
    p.append((massive_logerror[n+1]- massive_logerror[n]) / (massive_logN[n]- massive_logN[n+1]))
res=0
for i in range(k):
    res += p[i]
res /= k

print("Показатель сходимости p = ", res)


x = np.linspace(massive_logN[0] - 1, massive_logN[5] + 1, 1000)

#for n in range(len(massive_lognorm) - 2):
    #p.append((massive_lognorm[n+1]- massive_lognorm[n]) / (massive_logN[n+1]- massive_logN[n]))

fig, axs = plt.subplots(1, figsize=(6, 6))

axs.plot(x, - 4 * x, color='g', label = '$y = -4x$', alpha = 0.8, linewidth = 0.8)
axs.plot(massive_logN, massive_logerror, color = 'blue', label = 'R(f)', marker = '+', markersize = 5, alpha = 0.9, markeredgecolor = 'purple')
axs.set_xlabel('log(N)')
axs.set_ylabel('R^N(f)')
axs.set_title('Погрешность')
axs.grid(alpha=0.2, linestyle = '--')
axs.legend()


fig.tight_layout()
plt.show()