#include <Wire.h>
#include <AS726X.h>
#include <TCA9548A.h>
#include "Adafruit_SSD1306.h"
#include <ESP32Servo.h>

#include <TensorFlowLite.h>
#include "modelAgua.h" // Modelo de contenido de agua
#include "modelBrix.h" // Modelo de °Brix
#include "modelph.h" // Modelo de pH
#include "modelim.h" // Modelo de IM
#include "modelClasificacion.h" // Modelo de IM

#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define WIRE Wire
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &WIRE);

TCA9548A multiplexer;
AS726X sensorNIR;  // Sensor AS7263 en el canal 1
AS726X sensorVIS;  // Sensor AS7262 en el canal 2

int contadorMediciones = 0;
const int pulsador1 = 16;
const int pulsador2 = 4;

int lectura1 = 0;
int lectura2 = 0;

float R=0, S=0, T=0, U=0, V=0, W=0, Violet= 0, Blue = 0, Green = 0, Yellow = 0, Orange = 0, Red = 0;
float sumR_NIR = 0, sumS_NIR = 0, sumT_NIR = 0, sumU_NIR = 0, sumV_NIR = 0, sumW_NIR = 0;
float sumViolet_VIS = 0, sumBlue_VIS = 0, sumGreen_VIS = 0, sumYellow_VIS = 0, sumOrange_VIS = 0, sumRed_VIS = 0;

Servo servo;
int pinServo=15;
float resultAgua =0, resultBrix = 0, resultPH = 0, resultIM = 0;

// Declaración de variables globales para los modelos
const tflite::Model* modelAgua = nullptr;
tflite::MicroInterpreter* interpreterAgua = nullptr;
TfLiteTensor* inputAgua = nullptr;
TfLiteTensor* outputAgua = nullptr;

const tflite::Model* modelBrix = nullptr;
tflite::MicroInterpreter* interpreterBrix = nullptr;
TfLiteTensor* inputBrix = nullptr;
TfLiteTensor* outputBrix = nullptr;

const tflite::Model* modelPH = nullptr;
tflite::MicroInterpreter* interpreterPH = nullptr;
TfLiteTensor* inputPH = nullptr;
TfLiteTensor* outputPH = nullptr;

const tflite::Model* modelIM = nullptr;
tflite::MicroInterpreter* interpreterIM = nullptr;
TfLiteTensor* inputIM = nullptr;
TfLiteTensor* outputIM = nullptr;

// Declaración de variables globales para los modelos
const tflite::Model* modelClasificacion = nullptr;
tflite::MicroInterpreter* interpreterClasificacion = nullptr;
TfLiteTensor* inputClasificacion = nullptr;
TfLiteTensor* outputClasificacion = nullptr;

constexpr int kTensorArenaSizeAgua = 4096;
alignas(16) uint8_t tensor_arena_agua[kTensorArenaSizeAgua];

constexpr int kTensorArenaSizeBrix = 4096;
alignas(16) uint8_t tensor_arena_brix[kTensorArenaSizeBrix];

constexpr int kTensorArenaSizePH = 4096;
alignas(16) uint8_t tensor_arena_ph[kTensorArenaSizePH];

constexpr int kTensorArenaSizeIM = 4096;
alignas(16) uint8_t tensor_arena_im[kTensorArenaSizeIM];

constexpr int kTensorArenaSizeClas = 4096;
alignas(16) uint8_t tensor_arena_clas[kTensorArenaSizeClas];

// Definir la media y la desviación estándar para escalado
float mediaX[] = {2891.44013, 806.28984, 227.34889, 128.13471, 192.4063, 110.21605 ,522.89596, 458.25495, 1335.20657, 1719.79216, 1974.7694, 1428.86665};
float desviacionEstandarX[] = {1336.83140523, 324.26844997, 79.50581074, 44.53816924, 83.44942931, 46.96958707, 196.87900009, 223.75305904, 1015.48326058, 1003.87712041, 995.10313129, 522.24981666};

float mediaYAgua = 52.72427709;
float desviacionEstandarYAgua = 5.13504083;

float mediaYBrix = 8.468136; 
float desviacionEstandarYBrix = 0.97278095; 

float mediaYPH = 6.48703875; 
float desviacionEstandarYPH = 0.17194595; 

float mediaYIM = 45.622798; 
float desviacionEstandarYIM = 9.99609017;


void setup() {
  pinMode(pulsador1, INPUT);
  pinMode(pulsador2, INPUT);
  Serial.begin(115200);
  while (!Serial);

  servo.attach(pinServo, 500, 2500);
  // Inicializar el multiplexor
  Wire.begin();
  multiplexer.begin();

  // Inicializar el sensor AS7263 (NIR) en el canal 5
  selectI2CChannel(1);
  sensorNIR.begin();

  // Inicializar el sensor AS7262 (VIS) en el canal 1
  selectI2CChannel(2);
  sensorVIS.begin();

  // Inicializar la pantalla OLED
  selectI2CChannel(7);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("No se pudo inicializar la pantalla OLED"));
    while (1);
  }

  // Limpiar la pantalla
  display.clearDisplay();
  display.display();
  displayMessage("Bienvenido");
  
  //Serial.println(F("Configuración completa"));
  
  Serial.println("Predicción de valor usando modelo entrenado.");
  Serial.println("Inicializando TensorFlow Lite Micro Interpreter...");

  // Cargar el modelo
  modelAgua = tflite::GetModel(model_tflite);
  if (modelAgua->version() != TFLITE_SCHEMA_VERSION) {
    Serial.println("¡El modelo proporcionado y la versión del esquema no son iguales!");
    while(true);
  }
  modelBrix = tflite::GetModel(model_brix_tflite);
  if (modelBrix->version() != TFLITE_SCHEMA_VERSION) {
    Serial.println("¡El modelo proporcionado y la versión del esquema no son iguales!");
    while(true);
  }
  modelPH = tflite::GetModel(model_ph_tflite);
  if (modelPH->version() != TFLITE_SCHEMA_VERSION) {
    Serial.println("¡El modelo proporcionado y la versión del esquema no son iguales!");
    while(true);
  }
  modelIM = tflite::GetModel(model_IM_tflite);
  if (modelIM->version() != TFLITE_SCHEMA_VERSION) {
    Serial.println("¡El modelo proporcionado y la versión del esquema no son iguales!");
    while(true);
  }
  modelClasificacion = tflite::GetModel(quantized_model_tflite);
  if (modelClasificacion->version() != TFLITE_SCHEMA_VERSION) {
    Serial.println("¡El modelo proporcionado y la versión del esquema no son iguales!");
    while(true);
  }



  // Resolver las operaciones y crear el intérprete
  static tflite::AllOpsResolver resolverAgua;
  static tflite::MicroInterpreter static_interpreterAgua(
      modelAgua, resolverAgua, tensor_arena_agua, kTensorArenaSizeAgua);
  interpreterAgua = &static_interpreterAgua;

  static tflite::AllOpsResolver resolverBrix;
  static tflite::MicroInterpreter static_interpreterBrix(
      modelBrix, resolverBrix, tensor_arena_brix, kTensorArenaSizeBrix);
  interpreterBrix = &static_interpreterBrix;

  static tflite::AllOpsResolver resolverph;
  static tflite::MicroInterpreter static_interpreterPH(
      modelPH, resolverph, tensor_arena_ph, kTensorArenaSizePH);
  interpreterPH = &static_interpreterPH;

  static tflite::AllOpsResolver resolverim;
  static tflite::MicroInterpreter static_interpreterIM(
      modelIM, resolverim, tensor_arena_im, kTensorArenaSizeIM);
  interpreterIM = &static_interpreterIM;

  static tflite::AllOpsResolver resolverClas;
  static tflite::MicroInterpreter static_interpreterClas(
      modelClasificacion, resolverClas, tensor_arena_clas, kTensorArenaSizeClas);
  interpreterClasificacion = &static_interpreterClas;

  // Asignar tensores
  TfLiteStatus allocate_status = interpreterAgua->AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    Serial.println("¡AllocateTensors() falló!");
    while(true);
  }
  TfLiteStatus allocate_statusBrix = interpreterBrix->AllocateTensors();
  if (allocate_statusBrix != kTfLiteOk) {
    Serial.println("¡AllocateTensors() falló!");
    while(true);
  }
  TfLiteStatus allocate_statusph = interpreterPH->AllocateTensors();
  if (allocate_statusph != kTfLiteOk) {
    Serial.println("¡AllocateTensors() falló!");
    while(true);
  }
  TfLiteStatus allocate_statusim = interpreterIM->AllocateTensors();
  if (allocate_statusim != kTfLiteOk) {
    Serial.println("¡AllocateTensors() falló!");
    while(true);
  }
  TfLiteStatus allocate_statusClas = interpreterClasificacion->AllocateTensors();
  if (allocate_statusClas != kTfLiteOk) {
    Serial.println("¡AllocateTensors() falló!");
    while(true);
  }

  // Obtener tensores de entrada y salida
  inputAgua = interpreterAgua->input(0);
  outputAgua = interpreterAgua->output(0);
  // Obtener tensores de entrada y salida
  inputBrix = interpreterBrix->input(0);
  outputBrix = interpreterBrix->output(0);
  // Obtener tensores de entrada y salida
  inputPH = interpreterPH->input(0);
  outputPH = interpreterPH->output(0);
  // Obtener tensores de entrada y salida
  inputIM = interpreterIM->input(0);
  outputIM = interpreterIM->output(0);
  // Obtener tensores de entrada y salida
  inputClasificacion = interpreterClasificacion->input(0);
  outputClasificacion = interpreterClasificacion->output(0);

  Serial.println("Inicialización completada.");
}

int pos = 0;

void loop() {
  
  if (Serial.available() > 0) {
      // Lee el ID enviado desde Python
      String id_str = Serial.readString();
      // Convierte el ID en un entero
      int ultimo_id = id_str.toInt();
      contadorMediciones= ultimo_id;
    }
  // obtiene tecla presionada y asigna a variable
  lectura1 = digitalRead(pulsador1);
  lectura2 = digitalRead(pulsador2);
  
  // comprueba que se haya presionado una tecla
  if (lectura1 == HIGH) {
    // Comienza la secuencia de mediciones
    displayMessage("Inicio de Lectura");
    contadorMediciones += 1;
    for (int i = 0; i < 10; ++i) {
      Serial.print(contadorMediciones);
      Serial.print(" ");
      if (i==1){ 
       //Movemos el servo a los grados que le entreguemos
        servo.write(20);
        //Esperamos 15 milisegundos
        delay(50);
       //}
      }else if (i==2){
         //for (pos = 60; pos <= 120 ; pos += 1) {
         //Movemos el servo a los grados que le entreguemos
          servo.write(40);
          //Esperamos 15 milisegundos
          delay(50);
         //}
      }else if (i==3){
         //for (pos = 120; pos <= 180; pos += 1) {
         //Movemos el servo a los grados que le entreguemos
          servo.write(60);
          //Esperamos 15 milisegundos
          delay(50);
         //}
      }else if (i==4){
         //for (pos = 180; pos >= 90; pos -= 1) {
         //Movemos el servo a los grados que le entreguemos
          servo.write(80);
          //Esperamos 15 milisegundos
          delay(50);
         //}
      }else if (i==5){
         //for (pos = 90; pos >= 0; pos -= 1) {
         //Movemos el servo a los grados que le entreguemos
          servo.write(100);
          //Esperamos 15 milisegundos
          delay(50);
         //}
      }else if (i==6){
         //for (pos = 90; pos >= 0; pos -= 1) {
         //Movemos el servo a los grados que le entreguemos
          servo.write(120);
          //Esperamos 15 milisegundos
          delay(50);
         //}
      }else if (i==7){
         //for (pos = 90; pos >= 0; pos -= 1) {
         //Movemos el servo a los grados que le entreguemos
          servo.write(140);
          //Esperamos 15 milisegundos
          delay(50);
         //}
      }else if (i==8){
         //for (pos = 90; pos >= 0; pos -= 1) {
         //Movemos el servo a los grados que le entreguemos
          servo.write(160);
          //Esperamos 15 milisegundos
          delay(50);
         //}
      }else if (i==9){
         //for (pos = 90; pos >= 0; pos -= 1) {
         //Movemos el servo a los grados que le entreguemos
          servo.write(180);
          //Esperamos 15 milisegundos
          delay(50);
         //}
      }
      
      
      // Obtener y procesar datos para AS7263 (NIR) en el canal 1
      selectI2CChannel(1);
      delay(10);  // Ajusta según sea necesario
      sensorNIR.takeMeasurementsWithBulb();
      if (sensorNIR.getVersion() == SENSORTYPE_AS7263) {
        R=sensorNIR.getCalibratedR();
        Serial.print(sensorNIR.getCalibratedR(), 2);
        
        S=sensorNIR.getCalibratedS();
        Serial.print(" ");
        Serial.print(sensorNIR.getCalibratedS(), 2);
        
        T=sensorNIR.getCalibratedT();
        Serial.print(" ");
        Serial.print(sensorNIR.getCalibratedT(), 2);
        
        U=sensorNIR.getCalibratedU();
        Serial.print(" ");
        Serial.print(sensorNIR.getCalibratedU(), 2);
        
        V=sensorNIR.getCalibratedV();
        Serial.print(" ");
        Serial.print(sensorNIR.getCalibratedV(), 2);

        W=sensorNIR.getCalibratedW();
        Serial.print(" ");
        Serial.print(sensorNIR.getCalibratedW(), 2);
        Serial.print(" ");
      } 
      
      // Obtener y procesar datos para AS7262 (VIS) en el canal 2
      selectI2CChannel(2);
      delay(10);  // Ajusta según sea necesario
      sensorVIS.takeMeasurementsWithBulb();
      if (sensorVIS.getVersion() == SENSORTYPE_AS7262) {
        Violet=sensorVIS.getCalibratedViolet();
        Serial.print(sensorVIS.getCalibratedViolet(), 2);

        Blue=sensorVIS.getCalibratedBlue();
        Serial.print(" ");
        Serial.print(sensorVIS.getCalibratedBlue(), 2);

        Green=sensorVIS.getCalibratedGreen();
        Serial.print(" ");
        Serial.print(sensorVIS.getCalibratedGreen(), 2);

        Yellow=sensorVIS.getCalibratedYellow();
        Serial.print(" ");
        Serial.print(sensorVIS.getCalibratedYellow(), 2);

        Orange=sensorVIS.getCalibratedOrange();
        Serial.print(" ");
        Serial.print(sensorVIS.getCalibratedOrange(), 2);

        Red=sensorVIS.getCalibratedRed();
        Serial.print(" ");
        Serial.print(sensorVIS.getCalibratedRed(), 2);
        Serial.print(" ");
        Serial.println();
      } 

    // Después de obtener las mediciones, suma los valores
    sumR_NIR = sumR_NIR + R;
    sumS_NIR = sumS_NIR + S;
    sumT_NIR = sumT_NIR + T;
    sumU_NIR = sumU_NIR + U;
    sumV_NIR = sumV_NIR + V;
    sumW_NIR = sumW_NIR + W;
  
    sumViolet_VIS = sumViolet_VIS + Violet;
    sumBlue_VIS = sumBlue_VIS + Blue;
    sumGreen_VIS = sumGreen_VIS + Green;
    sumYellow_VIS = sumYellow_VIS + Yellow;
    sumOrange_VIS = sumOrange_VIS + Orange;
    sumRed_VIS = sumRed_VIS + Red;
    }

    // Calcula las medias dividiendo la suma entre el número de repeticiones
    float meanR_NIR = sumR_NIR / 10;
    float meanS_NIR = sumS_NIR / 10;
    float meanT_NIR = sumT_NIR / 10;
    float meanU_NIR = sumU_NIR / 10;
    float meanV_NIR = sumV_NIR / 10;
    float meanW_NIR = sumW_NIR / 10;
    
    float meanViolet_VIS = sumViolet_VIS / 10;
    float meanBlue_VIS = sumBlue_VIS / 10;
    float meanGreen_VIS = sumGreen_VIS / 10;
    float meanYellow_VIS = sumYellow_VIS / 10;
    float meanOrange_VIS = sumOrange_VIS / 10;
    float meanRed_VIS = sumRed_VIS / 10;
    
    // Ejemplo de características de entrada
    float inputValues[12] = {meanR_NIR, meanS_NIR, meanT_NIR, meanU_NIR, meanV_NIR, meanW_NIR, meanViolet_VIS, meanBlue_VIS, meanGreen_VIS, meanYellow_VIS, meanOrange_VIS, meanRed_VIS};
    //float inputValues[12] = {2240.319, 754.018, 199.185, 109.068, 146.565, 87.921, 423.837, 353.905, 484.946, 860.277, 1095.734, 1209.172};
    //float inputValues[12] = {2292.163, 654.679,  173.308,  93.404,  136.742,  78.239, 318.721, 176.154, 663.193, 968.787, 1433.546, 977.016};
    // Escalar los valores de entrada según la media y la desviación estándar
    for (int i = 0; i < 12; i++) {
    inputValues[i] = (inputValues[i] - mediaX[i]) / desviacionEstandarX[i];
    }
    
  // Mostrar valores de entrada escalados en el monitor serial
  Serial.print("Tus valores de entrada escalados: ");
  for (int i = 0; i < 12; i++) {
    Serial.print(inputValues[i], 4); // Ajusta el número según la precisión deseada
    if (i < 11) Serial.print(", ");
  }
  Serial.println();

  // Asignar valores de entrada escalados al tensor de entrada
  for (int i = 0; i < 12; i++) {
    inputAgua->data.f[i] = inputValues[i];
  }
  for (int i = 0; i < 12; i++) {
    inputBrix->data.f[i] = inputValues[i];
  }
  for (int i = 0; i < 12; i++) {
    inputPH->data.f[i] = inputValues[i];
  }
  for (int i = 0; i < 12; i++) {
    inputIM->data.f[i] = inputValues[i];
  }
  for (int i = 0; i < 12; i++) {
    inputClasificacion->data.f[i] = inputValues[i];
  }

  // Invocar el modelo
  TfLiteStatus invoke_status = interpreterAgua->Invoke();
  if (invoke_status != kTfLiteOk) {
    Serial.println("¡Invoke falló!");
    return;
  }
  // Invocar el modelo
  TfLiteStatus invoke_statusBrix = interpreterBrix->Invoke();
  if (invoke_statusBrix != kTfLiteOk) {
    Serial.println("¡Invoke falló!");
    return;
  }
  // Invocar el modelo
  TfLiteStatus invoke_statusPH = interpreterPH->Invoke();
  if (invoke_statusPH != kTfLiteOk) {
    Serial.println("¡Invoke falló!");
    return;
  }
  // Invocar el modelo
  TfLiteStatus invoke_statusIM = interpreterIM->Invoke();
  if (invoke_statusIM != kTfLiteOk) {
    Serial.println("¡Invoke falló!");
    return;
  }
  // Invocar el modelo
  TfLiteStatus invoke_statusClas = interpreterClasificacion->Invoke();
  if (invoke_statusClas != kTfLiteOk) {
    Serial.println("¡Invoke falló!");
    return;
  }

  // Obtener la salida escalada del modelo
  float y_scaled = outputAgua->data.f[0];
  // Obtener la salida escalada del modelo
  float y_scaledBrix = outputBrix->data.f[0];
  // Obtener la salida escalada del modelo
  float y_scaledPH = outputPH->data.f[0];
  // Obtener la salida escalada del modelo
  float y_scaledIM = outputIM->data.f[0];
  
  

   float y_scaledClas = outputClasificacion->data.f[0];
   const char *resultClas= y_scaledClas > 0.5 ? "Amarillo" : "Rojo";
   // Asignar el valor correspondiente basado en el resultado de la clasificación
    float Carbohidratos = (strcmp(resultClas, "Amarillo") == 0) ? 0.29 : 0.27;
    float Proteinas = (strcmp(resultClas, "Amarillo") == 0) ? 16.18 : 18.32;

    // Imprimir el resultado
    Serial.print("Prediction Clasificacion: ");
    Serial.println(resultClas);

    // Imprimir el valor asignado
    Serial.print("Carbohidratos: ");
    Serial.println(Carbohidratos);
    // Imprimir el valor asignado
    Serial.print("Proteinas: ");
    Serial.println(Proteinas);

    // Desescalar la salida para obtener el valor original
  float y_original = (y_scaled *desviacionEstandarYAgua) + mediaYAgua;// Suponiendo que solo es una salida
  float y_originalBrix = (y_scaledBrix * desviacionEstandarYBrix) + mediaYBrix;
  float y_originalPH = (y_scaledPH * desviacionEstandarYPH) + mediaYPH;
  float y_originalIM = (y_scaledIM * desviacionEstandarYIM) + mediaYIM;
  
  // Mostrar la predicción desescalada en el monitor serial
  Serial.print("Predicción del modelo de Agua desescalada: ");
  Serial.println(y_original, 2); // Ajusta el número según la precisión deseada
  Serial.print("Predicción del modelo de °Brix desescalada: ");
  Serial.println(y_originalBrix, 2); // Ajusta el número según la precisión deseada
  Serial.print("Predicción del modelo de pH desescalada: ");
  Serial.println(y_originalPH, 2); // Ajusta el número según la precisión deseada
  Serial.print("Predicción del modelo de IM desescalada: ");
  Serial.println(y_originalIM, 2); // Ajusta el número según la precisión deseada

    resultAgua =y_original;
    resultBrix = y_originalBrix;
    resultPH = y_originalPH;
    resultIM = y_originalIM;
   
        
    // Fin de la secuencia de mediciones
    displayMessage("Lectura Terminada");
    displayCounter(contadorMediciones);
    delay(3000);
    displayMessage2("Cont. Agua: ","Cont. Brix: ","Cont. pH: ","Cont. IM: ", "Clase Chont: " ,resultAgua, resultBrix, resultPH, resultIM,resultClas,"Carbohidratos: ",Carbohidratos,"Proteinas: ",Proteinas);

  }

    R=0, S=0, T=0, U=0, V=0, W=0, Violet= 0, Blue = 0, Green = 0, Yellow = 0, Orange = 0, Red = 0;
    sumR_NIR = 0, sumS_NIR = 0, sumT_NIR = 0, sumU_NIR = 0, sumV_NIR = 0, sumW_NIR = 0;
    sumViolet_VIS = 0, sumBlue_VIS = 0, sumGreen_VIS = 0, sumYellow_VIS = 0, sumOrange_VIS = 0, sumRed_VIS = 0;  
    
  if(lectura2 == HIGH) {
    displayMessage("Toma de medidas Terminada");
    displayMessage("Terminada");
    delay(2000);
    }
  servo.write(0);
  //Esperamos 15 milisegundos
  delay(50);
  display.display();                                                                                                                                                                                        
}

void selectI2CChannel(uint8_t channel) {
  // Seleccionar el canal en el que se conectará el bus I2C
  Wire.beginTransmission(0x70);
  Wire.write(1 << channel);
  Wire.endTransmission();
}

void displayMessage(const char *message) {
  selectI2CChannel(7);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Medicion Chontaduro ");
  display.setCursor(0, 9);
  display.print(message);
  display.display();
}
void displayMessage2(const char *message, const char *message2, const char *message3, const char *message4,const char *message5,float predict , float predict2, float predict3, float predict4,const char *predict5,const char *message6,float predict6,const char *message7,float predict7) {
  selectI2CChannel(7);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Medicion Chontaduro ");
  display.setCursor(0, 8);
  display.print(message5);
  display.print(predict5);
  display.setCursor(0, 16);
  display.print(message);
  display.print(predict);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 24);
  display.print(message2);
  display.print(predict2);
  display.setCursor(0, 32);
  display.print(message3);
  display.print(predict3);
  display.setCursor(0, 40);
  display.print(message4);
  display.print(predict4);
  display.setCursor(0, 48);
  display.print(message6);
  display.print(predict6);
  display.setCursor(0, 56);
  display.print(message7);
  display.print(predict7);
  display.display();
}

void displayCounter(int counter) {
  selectI2CChannel(7);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 16);
  display.print("Muestras: ");
  display.print(counter);
  display.display();
}
