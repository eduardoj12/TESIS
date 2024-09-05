import serial
import csv
import re
import pandas as pd


puerto_serial = 'COM3'  # Cambia esto al puerto que estés utilizando
velocidad_serial = 115200

# Intenta abrir el archivo CSV y obtener el último ID
try:
    data = pd.read_csv('datos_espectrales_final1.csv')
    if not data.empty:
        ultimo_id = data['ID'].iloc[-1]
    else:
        ultimo_id = 0
    nuevo_id = ultimo_id
    print('Nuevo ID:', nuevo_id)
except FileNotFoundError:
    # Si el archivo no existe, asigna el primer ID
    nuevo_id = 1
    print('Nuevo ID:', nuevo_id)
# Convierte el ID en un string antes de enviarlo a Arduino
nuevo_id_str = str(nuevo_id)

# Abre el puerto serial
try:
    ser = serial.Serial(puerto_serial, velocidad_serial)
    print('Puerto serial abierto correctamente.')
except serial.SerialException as e:
    print('Error al abrir el puerto serial:', e)
    raise SystemExit

# Envía el último ID a Arduino a través del puerto serial
try:
    ser.write(nuevo_id_str.encode())
    print('ID enviado correctamente a Arduino.')
except serial.SerialException as e:
    print('Error al enviar ID a Arduino:', e)
# Abre el archivo CSV para escribir
with open('datos_espectrales_final1.csv', mode='a', newline='') as csv_file:
    fieldnames = ['ID','NIR_R', 'NIR_S', 'NIR_T', 'NIR_U', 'NIR_V', 'NIR_W' , 'Vis_Violet', 'Vis_Blue', 'Vis_Green', 'Vis_Yellow', 'Vis_Orange', 'Vis_Red']
    writer = csv.DictWriter(csv_file, fieldnames=fieldnames)

    # Verifica si el archivo CSV está vacío abriéndolo en modo de lectura ('r')
    try:
        # Intenta leer el primer carácter del archivo
        with open('datos_espectrales_final.csv', mode='r') as check_file:
            first_char = check_file.read(1)

    except FileNotFoundError:
        # Si el archivo no existe, establece first_char en None
        first_char = None

    # Si el archivo está vacío o no existe, escribe la cabecera
    if not first_char:
        writer.writeheader()
               
    # Lee e imprime continuamente los datos desde el puerto serial
    while True:
        try:
            # Lee una línea desde el puerto serial
            line = ser.readline().decode('utf-8').strip()

            # Extrae solo los valores numéricos de la línea
            values = [float(num) for num in re.findall(r'-?\d+\.?\d*', line)]

            print("Values:", values)
            
            # Crea un diccionario con los valores
            data = {fieldnames[i]: values[i] for i in range(min(len(fieldnames), len(values)))}

            # Escribe los datos en el archivo CSV
            writer.writerow(data)
        except KeyboardInterrupt:
            # Detiene el bucle si se presiona Ctrl+C
            break

# Cierra el puerto serial
ser.close()