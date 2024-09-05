import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error, r2_score, mean_absolute_error
from sklearn.linear_model import LinearRegression
import tensorflow as tf
import numpy as np

from google.colab import drive
drive.mount('/content/drive')
# Cargar tu conjunto de datos
data = pd.read_csv("/content/drive/My Drive/Tesis/Dataset/nuevo_dataset_prueba.csv")

# Crear el DataFrame Referencia
y = data['Humedad']
#y = data['CSS BRIX°']
X =data[['NIR_R', 'NIR_S', 'NIR_T', 'NIR_U', 'NIR_V', 'NIR_W', 'Vis_Violet', 'Vis_Blue', 'Vis_Green', 'Vis_Yellow', 'Vis_Orange', 'Vis_Red']]


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% PARA HUMEDAD %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Dividir datos en conjuntos de entrenamiento y prueba (80% entrenamiento, 20% prueba)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Definir y entrenar modelo de regresión lineal estándar
model= LinearRegression()
model.fit(X_train, y_train)

# Exportar los coeficientes y el intercepto
coefficients = model.coef_
intercept = model.intercept_

print("Coeficientes:", coefficients)
print("Intercepto:", intercept)

coefs_string = ', '.join(map(str, coefficients.flatten()))
print("Coeficientes (una línea):")
print(coefs_string)

# Evaluar rendimiento del modelo de regresión lineal estándar en conjunto de prueba
y_pred = model.predict(X_test)

mse_lr = mean_squared_error(y_test, y_pred)
r2_lr = r2_score(y_test, y_pred)
mae_lr = mean_absolute_error(y_test, y_pred)
rmse_lr = np.sqrt(mse_lr)

print("Rendimiento del modelo de regresión lineal estándar:")
print("MSE:", mse_lr)
print("R-cuadrado:", r2_lr)
print("Error absoluto medio (MAE):", mae_lr)
print("Raíz del error cuadrático medio (RMSE):", rmse_lr)
print()
print(y_pred)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% PARA °BRIX %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error, r2_score, mean_absolute_error
from sklearn.linear_model import LinearRegression
import tensorflow as tf
import numpy as np
from google.colab import drive

drive.mount('/content/drive')
# Cargar tu conjunto de datos
data = pd.read_csv("/content/drive/My Drive/Tesis/Dataset/nuevo_dataset_prueba.csv")
# Crear el DataFrame Referencia
#y = data['Humedad']
y = data['°BRIX']
X =data[['NIR_R', 'NIR_S', 'NIR_T', 'NIR_U', 'NIR_V', 'NIR_W', 'Vis_Violet', 'Vis_Blue', 'Vis_Green', 'Vis_Yellow', 'Vis_Orange', 'Vis_Red']]

# # Para Contenido de Agua
# Dividir datos en conjuntos de entrenamiento y prueba (80% entrenamiento, 20% prueba)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Definir y entrenar modelo de regresión lineal estándar
model= LinearRegression()
model.fit(X_train, y_train)

# Exportar los coeficientes y el intercepto
coefficients = model.coef_
intercept = model.intercept_

print("Coeficientes:", coefficients)
print("Intercepto:", intercept)

coefs_string = ', '.join(map(str, coefficients.flatten()))
print("Coeficientes (una línea):")
print(coefs_string)
# Evaluar rendimiento del modelo de regresión lineal estándar en conjunto de prueba
y_pred = model.predict(X_test)

mse_lr = mean_squared_error(y_test, y_pred)
r2_lr = r2_score(y_test, y_pred)
mae_lr = mean_absolute_error(y_test, y_pred)
rmse_lr = np.sqrt(mse_lr)

print("Rendimiento del modelo de regresión lineal estándar:")
print("MSE:", mse_lr)
print("R-cuadrado:", r2_lr)
print("Error absoluto medio (MAE):", mae_lr)
print("Raíz del error cuadrático medio (RMSE):", rmse_lr)
print()
print(y_pred)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% PARA PH %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Crear el DataFrame Referencia
y = data['pH']
X =data[['NIR_R', 'NIR_S', 'NIR_T', 'NIR_U', 'NIR_V', 'NIR_W', 'Vis_Violet', 'Vis_Blue', 'Vis_Green', 'Vis_Yellow', 'Vis_Orange', 'Vis_Red']]

# Dividir datos en conjuntos de entrenamiento y prueba (80% entrenamiento, 20% prueba)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Definir y entrenar modelo de regresión lineal estándar
model= LinearRegression()
model.fit(X_train, y_train)
# Exportar los coeficientes y el intercepto
coefficients = model.coef_
intercept = model.intercept_

print("Intercepto:", intercept)
coefs_string = ', '.join(map(str, coefficients.flatten()))
print("Coeficientes (una línea):")
print(coefs_string)
# Evaluar rendimiento del modelo de regresión lineal estándar en conjunto de prueba
y_pred = model.predict(X_test)

mse_lr = mean_squared_error(y_test, y_pred)
r2_lr = r2_score(y_test, y_pred)
mae_lr = mean_absolute_error(y_test, y_pred)
rmse_lr = np.sqrt(mse_lr)

print("Rendimiento del modelo de regresión lineal estándar:")
print("MSE:", mse_lr)
print("R-cuadrado:", r2_lr)
print("Error absoluto medio (MAE):", mae_lr)
print("Raíz del error cuadrático medio (RMSE):", rmse_lr)
print()
print(y_pred)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% PARA IM %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Crear el DataFrame Referencia
y = data['IM']
X =data[['NIR_R', 'NIR_S', 'NIR_T', 'NIR_U', 'NIR_V', 'NIR_W', 'Vis_Violet', 'Vis_Blue', 'Vis_Green', 'Vis_Yellow', 'Vis_Orange', 'Vis_Red']]

# Dividir datos en conjuntos de entrenamiento y prueba (80% entrenamiento, 20% prueba)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Definir y entrenar modelo de regresión lineal estándar
model= LinearRegression()
model.fit(X_train, y_train)
# Exportar los coeficientes y el intercepto
coefficients = model.coef_
intercept = model.intercept_

print("Intercepto:", intercept)
coefs_string = ', '.join(map(str, coefficients.flatten()))
print("Coeficientes (una línea):")
print(coefs_string)
# Evaluar rendimiento del modelo de regresión lineal estándar en conjunto de prueba
y_pred = model.predict(X_test)

mse_lr = mean_squared_error(y_test, y_pred)
r2_lr = r2_score(y_test, y_pred)
mae_lr = mean_absolute_error(y_test, y_pred)
rmse_lr = np.sqrt(mse_lr)

print("Rendimiento del modelo de regresión lineal estándar:")
print("MSE:", mse_lr)
print("R-cuadrado:", r2_lr)
print("Error absoluto medio (MAE):", mae_lr)
print("Raíz del error cuadrático medio (RMSE):", rmse_lr)
print()
print(y_pred)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

