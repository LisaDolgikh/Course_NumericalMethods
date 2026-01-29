import matplotlib.pyplot as plt
import numpy as np

p_R = []
p_G = []
p_S = []

def read_data(file_address):
    massive_logN = []
    massive_logerror_R = []
    massive_logerror_S = []
    massive_logerror_G = []
    
    with open(file_address, 'r') as file:
        for line in file:
            logN, logerror_R, logerror_S, logerror_G = line.strip().split()
            massive_logN.append(float(logN))
            massive_logerror_R.append(float(logerror_R))
            massive_logerror_S.append(float(logerror_S))
            massive_logerror_G.append(float(logerror_G))
    
    return massive_logN, massive_logerror_R, massive_logerror_S, massive_logerror_G

#file_address = '//var//home//student//5//out.txt'
file_address = '/users/4/409/Dolgikh_EY/sem7/5/out.txt'
#file_address = 'C:\\msys64\\home\\Елизавета\\sem7\\5\\out.txt'

massive_logN, massive_logerror_R, massive_logerror_S, massive_logerror_G = read_data(file_address)

#k = len(massive_logN)
#k = 13 #./pr -1 1 4 1000 out.txt

#./pr 0 1 4 1000 out.txt
#Показатель сходимости для метода прямоугольников pR =  2.0220079612300568

#./pr 0 2 5 2 out.txt
#Показатель сходимости для метода прямоугольников pR =  1.9866883367145416
#Показатель сходимости для метода Симпсона pS =  3.9883420983770037
#Показатель сходимости для метода Гаусса pG =  5.968149671700904

k = 7
for n in range(k - 2):
    p_R.append((massive_logerror_R[n+1]- massive_logerror_R[n]) / (massive_logN[n]- massive_logN[n+1]))
    p_S.append((massive_logerror_S[n+1]- massive_logerror_S[n]) / (massive_logN[n]- massive_logN[n+1]))
    p_G.append((massive_logerror_G[n+1]- massive_logerror_G[n]) / (massive_logN[n]- massive_logN[n+1]))

pR = 0; pS = 0; pG = 0
for i in range(k - 2):
    pR += p_R[i]
    pS += p_S[i]
    pG += p_G[i]
pR /= (k - 2)
pS /= (k - 2)
pG /= (k - 2)

print("Показатель сходимости для метода прямоугольников pR = ", pR)
print("Показатель сходимости для метода Симпсона pS = ", pS)
print("Показатель сходимости для метода Гаусса pG = ", pG)

x = np.linspace(massive_logN[0] - 1, massive_logN[9] + 1, 1000)

#for n in range(len(massive_lognorm) - 2):
    #p.append((massive_lognorm[n+1]- massive_lognorm[n]) / (massive_logN[n+1]- massive_logN[n]))

fig, axs = plt.subplots(3, figsize=(6, 6))

axs[0].plot(x, - x, color='g', label = '$y = -x$', alpha = 0.8, linewidth = 0.8)
axs[0].plot(x, - 2*x, color='r', label = '$y = -2x$', alpha = 0.8, linewidth = 0.8)
axs[0].plot(massive_logN, massive_logerror_R, color = 'blue', label = 'R(f)', marker = '+', markersize = 5, alpha = 0.9, markeredgecolor = 'purple')
axs[0].set_xlabel('log(N)')
axs[0].set_ylabel('R^N(f)')
axs[0].set_title('Погрешность при приближение методом прямоугольников')
axs[0].grid(alpha=0.2, linestyle = '--')
axs[0].legend()

axs[1].plot(x, - 3*x, color='g', label = '$y = -3x$', alpha = 0.8, linewidth = 0.8)
axs[1].plot(x, - 4*x, color='r', label = '$y = -4x$', alpha = 0.8, linewidth = 0.8)
axs[1].plot(massive_logN, massive_logerror_S, color = 'blue', label = 'R(f)', marker = '+', markersize = 5, alpha = 0.9, markeredgecolor = 'purple')
axs[1].set_xlabel('log(N)')
axs[1].set_ylabel('R^N(f)')
axs[1].set_title('Погрешность при приближение методом Симпсона')
axs[1].grid(alpha=0.2, linestyle = '--')
axs[1].legend()

axs[2].plot(x, - 6*x, color='g', label = '$y = -6x$', alpha = 0.8, linewidth = 0.8)
axs[2].plot(massive_logN, massive_logerror_G, color = 'blue', label = 'R(f)', marker = '+', markersize = 5, alpha = 0.9, markeredgecolor = 'purple')
axs[2].set_xlabel('log(N)')
axs[2].set_ylabel('R^N(f)')
axs[2].set_title('Погрешность при приближение методом Гаусса')
axs[2].grid(alpha=0.2, linestyle = '--')
axs[2].legend()

fig.tight_layout()
plt.show()