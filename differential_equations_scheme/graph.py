import matplotlib.pyplot as plt
import numpy as np
import math as m

def read_data(file_address):
    massive_N = []
    massive_y1 = []
    massive_y2 = []
    massive_y3 = []
    massive_y4 = []
    
    with open(file_address, 'r') as file:
        for line in file:
            N, y1, y2, y3, y4 = line.strip().split()
            massive_N.append(float(N))
            massive_y1.append(float(y1))
            massive_y2.append(float(y2))
            massive_y3.append(float(y3))
            massive_y4.append(float(y4))
    
    return massive_N, massive_y1, massive_y2, massive_y3, massive_y4

#file_address = '//var//home//student//1//out.txt'
#file_address = '/users/4/409/Dolgikh_EY/sem8/1/out.txt'
file_address = 'C:\\msys64\\home\\Елизавета\\sem8\\2\\out.txt'

massive_N, massive_y1, massive_y2, massive_y3, massive_y4 = read_data(file_address)

log_massive_N = np.log(massive_N)
log_massive_y1 = np.log(massive_y1)
log_massive_y2 = np.log(massive_y2)
log_massive_y3 = np.log(massive_y3)
log_massive_y4 = np.log(massive_y4)

def angle(x, y, i1, i2):
    return -(y[i2] - y[i1]) / (x[i2] - x[i1])

i1, i2 = 3, 7

alpha_1 = angle(log_massive_N, log_massive_y1, i1, i2)
alpha_2 = angle(log_massive_N, log_massive_y2, i1, i2)
alpha_3 = angle(log_massive_N, log_massive_y3, i1, i2)
alpha_4 = angle(log_massive_N, log_massive_y4, i1, i2)

fig, axs = plt.subplots(2, 2, figsize=(10, 10))


axs[0, 0].plot(log_massive_N, log_massive_y1, color='blue', marker='+', markersize=4, alpha=0.8, linewidth=0.8, markeredgecolor='purple')
axs[0, 0].set_xlabel('log(N)')
axs[0, 0].set_ylabel('log(error)')
axs[0, 0].set_title("1 схема")
axs[0, 0].grid(alpha=0.2, linestyle='--')
axs[0, 0].text(0.05, 0.1, f'Показатель сходимости = {alpha_1:.4f}', transform=axs[0, 0].transAxes)


axs[0, 1].plot(log_massive_N, log_massive_y2, color='blue', marker='+', markersize=4, alpha=0.8, linewidth=0.8, markeredgecolor='purple')
axs[0, 1].set_xlabel('log(N)')
axs[0, 1].set_ylabel('log(error)')
axs[0, 1].set_title("2 схема")
axs[0, 1].grid(alpha=0.2, linestyle='--')
axs[0, 1].text(0.05, 0.1, f'Показатель сходимости = {alpha_2:.4f}', transform=axs[0, 1].transAxes)

axs[1, 0].plot(log_massive_N, log_massive_y3, color='blue', marker='+', markersize=4, alpha=0.8, linewidth=0.8, markeredgecolor='purple')
axs[1, 0].set_xlabel('log(N)')
axs[1, 0].set_ylabel('log(error)')
axs[1, 0].set_title("3 схема")
axs[1, 0].grid(alpha=0.2, linestyle='--')
axs[1, 0].text(0.05, 0.1, f'Показатель сходимости = {alpha_3:.4f}', transform=axs[1, 0].transAxes)

axs[1, 1].plot(log_massive_N, log_massive_y4, color='blue', marker='+', markersize=4, alpha=0.8, linewidth=0.8, markeredgecolor='purple')
axs[1, 1].set_xlabel('log(N)')
axs[1, 1].set_ylabel('log(error)')
axs[1, 1].set_title("4 схема")
axs[1, 1].grid(alpha=0.2, linestyle='--')
axs[1, 1].text(0.05, 0.1, f'Показатель сходимости = {alpha_4:.4f}', transform=axs[1, 1].transAxes)

plt.tight_layout()
plt.savefig("out.pdf")
plt.show()