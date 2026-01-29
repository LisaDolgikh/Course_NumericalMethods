import numpy as np
import matplotlib.pyplot as plt


def read_data(file_address):
    massive_M = []
    massive_error = []

    with open(file_address, 'r') as file:
        for line in file:
            parts = line.split()
            if len(parts) == 2:
                try:
                    N = int(parts[0])
                    error = float(parts[1])
                    if N > 0 and error > 0:
                        massive_M.append(N)
                        massive_error.append(error)
                except ValueError:
                    continue
    return massive_M, massive_error
    
#file_address = '//var//home//student//3.1//out.txt'
#file_address = '/users/4/409/Dolgikh_EY/sem8/3.1/out.txt'
file_address = 'C:\\msys64\\home\\Елизавета\\sem8\\3.1\\out.txt'

massive_M, massive_error = read_data(file_address)

# Преобразование в массивы numpy
massive_M = np.array(massive_M)
massive_error = np.array(massive_error)

# Построение графика
plt.figure(figsize=(8, 6))
plt.plot(np.log(1 / massive_M), np.log(massive_error), 'o-', label="ln(error) ( ln(1/M))")
x_min = min(np.log(1 / massive_M))
x_max = max(np.log(1 / massive_M))
x_line = np.linspace(x_min, x_max, 100)
plt.plot(x_line, 2 * x_line, 'r--', label="y = 2x", alpha=0.7)

plt.xlabel("ln(1/M)")
plt.ylabel("ln(error)")
plt.title("График зависимости ln(error) от ln(1/M)")

plt.legend()
plt.grid()
plt.show()
