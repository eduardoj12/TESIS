from google.colab import drive
import pandas as pd
drive.mount('/content/drive')

# Cargar tu conjunto de datos
data = pd.read_csv("/content/drive/My Drive/Tesis/Dataset/datos_espectrales_con_media_final1.csv")
X = data[['NIR_R', 'NIR_S', 'NIR_T', 'NIR_U', 'NIR_V', 'NIR_W', 'Vis_Violet', 'Vis_Blue', 'Vis_Green', 'Vis_Yellow', 'Vis_Orange', 'Vis_Red']]
data = X[::-1]

%%%%%%%%%%%%%%%%%%%%%%%%%%% PARA GRADOS °BRIX %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
import numpy as np

# Parámetros
media_1 = 7.16
media_2 = 7.41
media_3 = 8
media_4 = 8.25
media_5 = 8.75
media_6 = 9.5
media_7 = 10
desviacion_estandar = 0.05
cantidad_valores = 14
cantidad_valores_1=15

# Generar valores
valores_1 = np.random.normal(media_1, desviacion_estandar,cantidad_valores)
valores_2 = np.random.normal(media_2, desviacion_estandar, cantidad_valores)
valores_3 = np.random.normal(media_3, desviacion_estandar, cantidad_valores)
valores_4 = np.random.normal(media_4, desviacion_estandar, cantidad_valores)
valores_5 = np.random.normal(media_5, desviacion_estandar, cantidad_valores)
valores_6 = np.random.normal(media_6, desviacion_estandar, cantidad_valores_1)
valores_7 = np.random.normal(media_7, desviacion_estandar, cantidad_valores_1)

# Concatenar los valores
valores_totales = np.concatenate((valores_1, valores_2,valores_3,valores_4,valores_5,valores_6,valores_7))
data['°BRIX'] = valores_totales

import matplotlib.pyplot as plt
import numpy as np
# Definir la cantidad de valores para cada grupo
cantidad_valores = 14
cantidad_valores_1 = 15

# Crear la figura y los ejes
fig, ax = plt.subplots(figsize=(10, 6))

# Graficar el primer grupo de valores con color verde
ax.plot(range(cantidad_valores), valores_1, marker='o', linestyle='none', color='g', label='Muy Verde')

# Graficar el segundo grupo de valores con color azul
ax.plot(range(cantidad_valores, cantidad_valores*2), valores_2, marker='o', linestyle='none', color='b', label='Verde')

# Graficar el tercer grupo de valores con color negro
ax.plot(range(cantidad_valores*2, cantidad_valores*3), valores_3, marker='o', linestyle='none', color='k', label='Verde-Pinton')

# Graficar el cuarto grupo de valores con color cyan
ax.plot(range(cantidad_valores*3, cantidad_valores*4), valores_4, marker='o', linestyle='none', color='c', label='Pinton')

# Graficar el quinto grupo de valores con color magenta
ax.plot(range(cantidad_valores*4, cantidad_valores*5), valores_5, marker='o', linestyle='none', color='m', label='Pinton-Maduro')

# Graficar el sexto grupo de valores con color amarillo
ax.plot(range(cantidad_valores*5, cantidad_valores*5 + cantidad_valores_1), valores_6, marker='o', linestyle='none', color='y', label='Maduro')

# Graficar el séptimo grupo de valores con color rojo
ax.plot(range(cantidad_valores*5 + cantidad_valores_1, cantidad_valores*5 + cantidad_valores_1 * 2), valores_7, marker='o', linestyle='none', color='r', label='Sobre-Maduro')

# Configurar las etiquetas y el título
ax.set_xlabel('Muestras')
ax.set_ylabel('SST o °BRIX (%)')
ax.set_title('°BRIX vs Muestras')

# Mostrar la grilla
ax.grid(True)

# Ajustar los límites del eje x
ax.set_xticks(np.arange(0, cantidad_valores * 5 + cantidad_valores_1 * 2, 14))
ax.set_xlim(0, cantidad_valores * 5 + cantidad_valores_1 * 2)

# Agregar la leyenda
ax.legend()

# Guardar la figura en formato EPS
plt.savefig("brix_vs_muestras.eps", format='eps')

# Mostrar la gráfica
plt.show()
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% PARA HUMEDAD %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

import matplotlib.pyplot as plt
import numpy as np
# Parámetros
media_1 = 62.84
media_2 = 55.08
media_3 = 54.34
media_4 = 49.43
media_5 = 50.08
media_6 = 52.49
media_7 = 45.33
desviacion_estandar = 0.1
cantidad_valores = 14
cantidad_valores_1=15

# Generar valores
valores_1 = np.random.normal(media_1, desviacion_estandar,cantidad_valores)
valores_2 = np.random.normal(media_2, desviacion_estandar, cantidad_valores)
valores_3 = np.random.normal(media_3, desviacion_estandar, cantidad_valores)
valores_4 = np.random.normal(media_4, desviacion_estandar, cantidad_valores)
valores_5 = np.random.normal(media_5, desviacion_estandar, cantidad_valores)
valores_6 = np.random.normal(media_6, desviacion_estandar, cantidad_valores_1)
valores_7 = np.random.normal(media_7, desviacion_estandar, cantidad_valores_1)

# Concatenar los valores
valores_totales = np.concatenate((valores_1, valores_2,valores_3,valores_4,valores_5,valores_6,valores_7))

# Mostrar valores
print(valores_totales)
data['Humedad'] = valores_totales

print(data)

# Definir la cantidad de valores para cada grupo
cantidad_valores = 14
cantidad_valores_1 = 15

# Crear la figura y los ejes
fig, ax = plt.subplots(figsize=(10, 6))

# Graficar el primer grupo de valores con color verde
ax.plot(range(cantidad_valores), valores_1, marker='o', linestyle='none', color='g', label='Muy Verde')

# Graficar el segundo grupo de valores con color azul
ax.plot(range(cantidad_valores, cantidad_valores*2), valores_2, marker='o', linestyle='none', color='b', label='Verde')

# Graficar el tercer grupo de valores con color negro
ax.plot(range(cantidad_valores*2, cantidad_valores*3), valores_3, marker='o', linestyle='none', color='k', label='Verde-Pinton')

# Graficar el cuarto grupo de valores con color cyan
ax.plot(range(cantidad_valores*3, cantidad_valores*4), valores_4, marker='o', linestyle='none', color='c', label='Pinton')

# Graficar el quinto grupo de valores con color magenta
ax.plot(range(cantidad_valores*4, cantidad_valores*5), valores_5, marker='o', linestyle='none', color='m', label='Pinton-Maduro')

# Graficar el sexto grupo de valores con color amarillo
ax.plot(range(cantidad_valores*5, cantidad_valores*5 + cantidad_valores_1), valores_6, marker='o', linestyle='none', color='y', label='Maduro')

# Graficar el séptimo grupo de valores con color rojo
ax.plot(range(cantidad_valores*5 + cantidad_valores_1, cantidad_valores*5 + cantidad_valores_1 * 2), valores_7, marker='o', linestyle='none', color='r', label='Sobre-Maduro')

# Configurar las etiquetas y el título
ax.set_xlabel('Muestras')
ax.set_ylabel('Humedad (%)')
ax.set_title('Humedad vs Muestras')

# Mostrar la grilla
ax.grid(True)

# Ajustar los límites del eje x
ax.set_xticks(np.arange(0, cantidad_valores * 5 + cantidad_valores_1 * 2, 14))
ax.set_xlim(0, cantidad_valores * 5 + cantidad_valores_1 * 2)

# Agregar la leyenda
ax.legend()

# Mostrar la gráfica
plt.show()
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% PARA pH %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

import matplotlib.pyplot as plt
import numpy as np
# Parámetros
media_1 = 6.16
media_2 = 6.41
media_3 = 6.48
media_4 = 6.48
media_5 = 6.56
media_6 = 6.65
media_7 = 6.68
desviacion_estandar = 0.05
cantidad_valores = 14
cantidad_valores_1=15

# Generar valores
valores_1 = np.random.normal(media_1, desviacion_estandar,cantidad_valores)
valores_2 = np.random.normal(media_2, desviacion_estandar, cantidad_valores)
valores_3 = np.random.normal(media_3, desviacion_estandar, cantidad_valores)
valores_4 = np.random.normal(media_4, desviacion_estandar, cantidad_valores)
valores_5 = np.random.normal(media_5, desviacion_estandar, cantidad_valores)
valores_6 = np.random.normal(media_6, desviacion_estandar, cantidad_valores_1)
valores_7 = np.random.normal(media_7, desviacion_estandar, cantidad_valores_1)

# Concatenar los valores
valores_totales = np.concatenate((valores_1, valores_2,valores_3,valores_4,valores_5,valores_6,valores_7))

# Mostrar valores
print(valores_totales)
data['pH'] = valores_totales

print(data)

# Definir la cantidad de valores para cada grupo
cantidad_valores = 14
cantidad_valores_1 = 15

# Crear la figura y los ejes
fig, ax = plt.subplots(figsize=(10, 6))

# Graficar el primer grupo de valores con color verde
ax.plot(range(cantidad_valores), valores_1, marker='o', linestyle='none', color='g', label='Muy Verde')

# Graficar el segundo grupo de valores con color azul
ax.plot(range(cantidad_valores, cantidad_valores*2), valores_2, marker='o', linestyle='none', color='b', label='Verde')

# Graficar el tercer grupo de valores con color negro
ax.plot(range(cantidad_valores*2, cantidad_valores*3), valores_3, marker='o', linestyle='none', color='k', label='Verde-Pinton')

# Graficar el cuarto grupo de valores con color cyan
ax.plot(range(cantidad_valores*3, cantidad_valores*4), valores_4, marker='o', linestyle='none', color='c', label='Pinton')

# Graficar el quinto grupo de valores con color magenta
ax.plot(range(cantidad_valores*4, cantidad_valores*5), valores_5, marker='o', linestyle='none', color='m', label='Pinton-Maduro')

# Graficar el sexto grupo de valores con color amarillo
ax.plot(range(cantidad_valores*5, cantidad_valores*5 + cantidad_valores_1), valores_6, marker='o', linestyle='none', color='y', label='Maduro')

# Graficar el séptimo grupo de valores con color rojo
ax.plot(range(cantidad_valores*5 + cantidad_valores_1, cantidad_valores*5 + cantidad_valores_1 * 2), valores_7, marker='o', linestyle='none', color='r', label='Sobre-Maduro')

# Configurar las etiquetas y el título
ax.set_xlabel('Muestras')
ax.set_ylabel('pH')
ax.set_title('pH vs Muestras')

# Mostrar la grilla
ax.grid(True)

# Ajustar los límites del eje x
ax.set_xticks(np.arange(0, cantidad_valores * 5 + cantidad_valores_1 * 2, 14))
ax.set_xlim(0, cantidad_valores * 5 + cantidad_valores_1 * 2)

# Agregar la leyenda
ax.legend()

# Mostrar la gráfica
plt.show()
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% PARA IM %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
import matplotlib.pyplot as plt
import numpy as np
# # IM (Indice de Maduracion)

# Parámetros
media_1 = 37.2
media_2 = 35.02
media_3 = 38
media_4 = 42.02
media_5 = 51.09
media_6 = 49.05
media_7 = 65.16
desviacion_estandar = 0.5
cantidad_valores = 14
cantidad_valores_1=15

# Generar valores
valores_1 = np.random.normal(media_1, desviacion_estandar,cantidad_valores)
valores_2 = np.random.normal(media_2, desviacion_estandar, cantidad_valores)
valores_3 = np.random.normal(media_3, desviacion_estandar, cantidad_valores)
valores_4 = np.random.normal(media_4, desviacion_estandar, cantidad_valores)
valores_5 = np.random.normal(media_5, desviacion_estandar, cantidad_valores)
valores_6 = np.random.normal(media_6, desviacion_estandar, cantidad_valores_1)
valores_7 = np.random.normal(media_7, desviacion_estandar, cantidad_valores_1)

# Concatenar los valores
valores_totales = np.concatenate((valores_1, valores_2,valores_3,valores_4,valores_5,valores_6,valores_7))

# Mostrar valores
print(valores_totales)
data['IM'] = valores_totales

print(data)

# Definir la cantidad de valores para cada grupo
cantidad_valores = 14
cantidad_valores_1 = 15

# Crear la figura y los ejes
fig, ax = plt.subplots(figsize=(10, 6))

# Graficar el primer grupo de valores con color verde
ax.plot(range(cantidad_valores), valores_1, marker='o', linestyle='none', color='g', label='Muy Verde')

# Graficar el segundo grupo de valores con color azul
ax.plot(range(cantidad_valores, cantidad_valores*2), valores_2, marker='o', linestyle='none', color='b', label='Verde')

# Graficar el tercer grupo de valores con color negro
ax.plot(range(cantidad_valores*2, cantidad_valores*3), valores_3, marker='o', linestyle='none', color='k', label='Verde-Pinton')

# Graficar el cuarto grupo de valores con color cyan
ax.plot(range(cantidad_valores*3, cantidad_valores*4), valores_4, marker='o', linestyle='none', color='c', label='Pinton')

# Graficar el quinto grupo de valores con color magenta
ax.plot(range(cantidad_valores*4, cantidad_valores*5), valores_5, marker='o', linestyle='none', color='m', label='Pinton-Maduro')

# Graficar el sexto grupo de valores con color amarillo
ax.plot(range(cantidad_valores*5, cantidad_valores*5 + cantidad_valores_1), valores_6, marker='o', linestyle='none', color='y', label='Maduro')

# Graficar el séptimo grupo de valores con color rojo
ax.plot(range(cantidad_valores*5 + cantidad_valores_1, cantidad_valores*5 + cantidad_valores_1 * 2), valores_7, marker='o', linestyle='none', color='r', label='Sobre-Maduro')

# Configurar las etiquetas y el título
ax.set_xlabel('Muestras')
ax.set_ylabel('IM')
ax.set_title('IM vs Muestras')

# Mostrar la grilla
ax.grid(True)

# Ajustar los límites del eje x
ax.set_xticks(np.arange(0, cantidad_valores * 5 + cantidad_valores_1 * 2, 14))
ax.set_xlim(0, cantidad_valores * 5 + cantidad_valores_1 * 2)

# Agregar la leyenda
ax.legend()

# Mostrar la gráfica
plt.show()
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%% PARA CARBOHIDRATOS Y PROTEINAS (MODELO CLASIFICACION) %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Crear etiquetas (0 para rojo, 1 para amarillo)
data['Clase (R=0,A=1)'] = [1]*40 + [0]*60
print(data)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

# prompt: guardar el nuevo DataFrame en Drive
from google.colab import files
data.to_csv('/content/drive/My Drive/Tesis/Dataset/nuevo_dataset_prueba.csv', index=False)
