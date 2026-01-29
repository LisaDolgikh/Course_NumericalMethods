import matplotlib.pyplot as plt
import numpy as np

def read_data(file_address):
    massive_k = []
    massive_resid = []
    massive_theoretical_resid = []

    
    with open(file_address, 'r') as file:
        for line in file:
            k, resid, theoretical_resid= line.strip().split()
            massive_k.append(float(k))
            massive_resid.append(float(resid))
            massive_theoretical_resid.append(float(theoretical_resid))

    
    return massive_k, massive_resid, massive_theoretical_resid

#file_address = '//var//home//student//7//out.txt'
#file_address = '/users/4/409/Dolgikh_EY/sem7/7/out.txt'
file_address = 'C:\\msys64\\home\\Елизавета\\sem7\\7\\out.txt'

massive_k, massive_resid, massive_theoretical_resid= read_data(file_address)

fig, axs = plt.subplots(1, figsize=(6, 6))

axs.plot(massive_k, massive_resid, color='g', label = '$Residual$', marker = '+', markersize = 3, alpha = 0.8, linewidth = 0.8, markeredgecolor = 'red')
axs.plot(massive_k, massive_theoretical_resid, color = 'blue', label = 'Theoretical residual', marker = '+', markersize = 2, alpha = 0.7, markeredgecolor = 'purple')
axs.set_xlabel('iter')
axs.set_ylabel('Resid')
axs.set_title('Погрешность')
axs.grid(alpha=0.2, linestyle = '--')
axs.legend()


fig.tight_layout()
plt.show()