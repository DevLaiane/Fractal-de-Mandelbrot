from matplotlib import pyplot as plt
import numpy as np
import os

# Compila o programa C++ (usando g++ pois gcc apresentava problemas)
os.system("g++ fractal.cpp -o fractal")

# Executa o programa fractal com ou sem parâmetros:
# Formato: ./fractal max_iter width height center_real center_imag extent_real extent_imag
# Exemplo: ./fractal 256 256 256 -0.77772 0.00023 3.55 3.44
# Se nenhum argumento for passado, usa valores padrão do código C++
os.system("./fractal")

# Carrega os resultados do arquivo de saída
result = np.loadtxt("MandelMatrix.txt", dtype=int)

# Lê e processa os parâmetros do arquivo
with open("Parameter.txt") as parameter:
    line = parameter.readline().split(';')  # Divide os parâmetros separados por ';'
    
    max_iter = int(line[0])
    width = int(line[1])
    height = int(line[2])
    center = complex(line[3] + 'j')  # Converte string para número complexo
    extent = complex(line[4] + 'j')
    scale = float(line[5])

# Configuração do plot com matplotlib
fig, ax = plt.subplots(1, 1, figsize=(10, 10))

# Calcula a área de visualização no plano complexo
plot_extent = (width + 1j * height) * scale
z1 = center - plot_extent / 2  # Canto inferior esquerdo
z2 = z1 + plot_extent         # Canto superior direito

# Plota o fractal com:
# - result**(1/3) para melhor contraste visual
# - origin='lower' para manter orientação correta
# - extent define os limites do eixo
ax.imshow(result**(1/3), origin='lower', 
          extent=(z1.real, z2.real, z1.imag, z2.imag))

# Rótulos dos eixos usando notação matemática
ax.set_xlabel("$\Re(c)$")  # Parte real
ax.set_ylabel("$\Im(c)$")  # Parte imaginária

plt.show()
