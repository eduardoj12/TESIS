# -*- coding: utf-8 -*-
"""2.PLS.ipynb

Automatically generated by Colab.

Original file is located at
    https://colab.research.google.com/drive/1MBLcoVnq-tk5AwxhkQF9uHvl3vGUff0L
"""

import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.cross_decomposition import PLSRegression
from sklearn.metrics import mean_squared_error, r2_score
from sklearn.preprocessing import StandardScaler

from google.colab import drive
drive.mount('/content/drive')
# Cargar tu conjunto de datos
data = pd.read_csv("/content/drive/My Drive/Tesis/Dataset/nuevo_dataset_prueba.csv")

# Crear el DataFrame Referencia
y = data['Humedad']
#y=data['CSS BRIX°']
X =data[['NIR_R', 'NIR_S', 'NIR_T', 'NIR_U', 'NIR_V', 'NIR_W', 'Vis_Violet', 'Vis_Blue', 'Vis_Green', 'Vis_Yellow', 'Vis_Orange', 'Vis_Red']]

# Dividir los datos en conjunto de entrenamiento y conjunto de prueba
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.05, random_state=42)

# Definir y entrenar modelo PLS
pls_model = PLSRegression(n_components=5)  # Elige el número de componentes PLS que deseas
pls_model.fit(X_train, y_train)

# Evaluar rendimiento del modelo PLS en conjunto de prueba
y_pred_pls = pls_model.predict(X_test)
mse_pls = mean_squared_error(y_test, y_pred_pls)
r2_pls = r2_score(y_test, y_pred_pls)

print("Rendimiento del modelo de PLS:")
print("MSE:", mse_pls)
print("R-cuadrado:", r2_pls)
print()

print(y_pred_pls)
print(X_test[1:2])

# Calcula las medias manualmente
X_mean = np.mean(X_train, axis=0)
y_mean = np.mean(y_train, axis=0)

# Extrae los coeficientes
coefficients = pls_model.coef_
print("Coefficients:", coefficients)
print("X mean:", X_mean)
print("y mean:", y_mean)

# prompt: colocar en una linea los coeficientes

coefs_string = ', '.join(map(str, coefficients.flatten()))
print("Coeficientes (una línea):")
print(coefs_string)

# Convertir el Pandas Series a una lista antes de unir
MediaX_string = ', '.join(map(str, X_mean.tolist()))  # Cambio aquí
print("Media X (una línea):")  # Etiqueta cambiada para mayor claridad
print(MediaX_string)

# Crear el DataFrame Referencia
y=data['°BRIX']
X =data[['NIR_R', 'NIR_S', 'NIR_T', 'NIR_U', 'NIR_V', 'NIR_W', 'Vis_Violet', 'Vis_Blue', 'Vis_Green', 'Vis_Yellow', 'Vis_Orange', 'Vis_Red']]

# Dividir los datos en conjunto de entrenamiento y conjunto de prueba
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.05, random_state=42)

# Definir y entrenar modelo PLS
pls_model = PLSRegression(n_components=5)  # Elige el número de componentes PLS que deseas
pls_model.fit(X_train, y_train)

# Evaluar rendimiento del modelo PLS en conjunto de prueba
y_pred_pls = pls_model.predict(X_test)
mse_pls = mean_squared_error(y_test, y_pred_pls)
r2_pls = r2_score(y_test, y_pred_pls)
print(y_pred_pls[1])
print("Rendimiento del modelo de PLS:")
print("MSE:", mse_pls)
print("R-cuadrado:", r2_pls)

# Calcula las medias manualmente
X_mean = np.mean(X_train, axis=0)
y_mean = np.mean(y_train, axis=0)

# Extrae los coeficientes
coefficients = pls_model.coef_
print("Coefficients:", coefficients)
print("X mean:", X_mean)
print("y mean:", y_mean)

# prompt: colocar en una linea los coeficientes
coefs_string = ', '.join(map(str, coefficients.flatten()))
print("Coeficientes (una línea):")
print(coefs_string)

# Convertir el Pandas Series a una lista antes de unir
MediaX_string = ', '.join(map(str, X_mean.tolist()))  # Cambio aquí
print("Media X (una línea):")  # Etiqueta cambiada para mayor claridad
print(MediaX_string)

# prompt: Realizar lo anterior pero con variables para pH

import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.cross_decomposition import PLSRegression
from sklearn.metrics import mean_squared_error, r2_score
from sklearn.preprocessing import StandardScaler
from google.colab import drive
drive.mount('/content/drive')
# Cargar tu conjunto de datos
data = pd.read_csv("/content/drive/My Drive/Tesis/Dataset/nuevo_dataset_prueba.csv")

# Crear el DataFrame Referencia
y = data['pH']
X =data[['NIR_R', 'NIR_S', 'NIR_T', 'NIR_U', 'NIR_V', 'NIR_W', 'Vis_Violet', 'Vis_Blue', 'Vis_Green', 'Vis_Yellow', 'Vis_Orange', 'Vis_Red']]
# Dividir los datos en conjunto de entrenamiento y conjunto de prueba
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.05, random_state=42)
# Definir y entrenar modelo PLS
pls_model = PLSRegression(n_components=5)  # Elige el número de componentes PLS que deseas
pls_model.fit(X_train, y_train)

# Evaluar rendimiento del modelo PLS en conjunto de prueba
y_pred_pls = pls_model.predict(X_test)
mse_pls = mean_squared_error(y_test, y_pred_pls)
r2_pls = r2_score(y_test, y_pred_pls)

print("Rendimiento del modelo de PLS:")
print("MSE:", mse_pls)
print("R-cuadrado:", r2_pls)
print()

print(y_pred_pls)
print(X_test[1:2])


# Calcula las medias manualmente
X_mean = np.mean(X_train, axis=0)
y_mean = np.mean(y_train, axis=0)

# Extrae los coeficientes
coefficients = pls_model.coef_
print("Coefficients:", coefficients)
print("X mean:", X_mean)
print("y mean:", y_mean)


coefs_string = ', '.join(map(str, coefficients.flatten()))
print("Coeficientes (una línea):")
print(coefs_string)

# Convertir el Pandas Series a una lista antes de unir
MediaX_string = ', '.join(map(str, X_mean.tolist()))  # Cambio aquí
print("Media X (una línea):")  # Etiqueta cambiada para mayor claridad
print(MediaX_string)

# prompt: Realizar lo anterior pero con variables para IM

import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.cross_decomposition import PLSRegression
from sklearn.metrics import mean_squared_error, r2_score
from sklearn.preprocessing import StandardScaler
from google.colab import drive
drive.mount('/content/drive')
# Cargar tu conjunto de datos
data = pd.read_csv("/content/drive/My Drive/Tesis/Dataset/nuevo_dataset_prueba.csv")

# Crear el DataFrame Referencia
y = data['IM']
X =data[['NIR_R', 'NIR_S', 'NIR_T', 'NIR_U', 'NIR_V', 'NIR_W', 'Vis_Violet', 'Vis_Blue', 'Vis_Green', 'Vis_Yellow', 'Vis_Orange', 'Vis_Red']]
# Dividir los datos en conjunto de entrenamiento y conjunto de prueba
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.05, random_state=42)
# Definir y entrenar modelo PLS
pls_model = PLSRegression(n_components=5)  # Elige el número de componentes PLS que deseas
pls_model.fit(X_train, y_train)

# Evaluar rendimiento del modelo PLS en conjunto de prueba
y_pred_pls = pls_model.predict(X_test)
mse_pls = mean_squared_error(y_test, y_pred_pls)
r2_pls = r2_score(y_test, y_pred_pls)

print("Rendimiento del modelo de PLS:")
print("MSE:", mse_pls)
print("R-cuadrado:", r2_pls)
print()

print(y_pred_pls)
print(X_test[1:2])


# Calcula las medias manualmente
X_mean = np.mean(X_train, axis=0)
y_mean = np.mean(y_train, axis=0)

# Extrae los coeficientes
coefficients = pls_model.coef_
print("Coefficients:", coefficients)
print("X mean:", X_mean)
print("y mean:", y_mean)


coefs_string = ', '.join(map(str, coefficients.flatten()))
print("Coeficientes (una línea):")
print(coefs_string)

# Convertir el Pandas Series a una lista antes de unir
MediaX_string = ', '.join(map(str, X_mean.tolist()))  # Cambio aquí
print("Media X (una línea):")  # Etiqueta cambiada para mayor claridad
print(MediaX_string)