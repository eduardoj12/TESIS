#include <Wire.h>
#include <AS726X.h>
#include <TCA9548A.h>
#include "Adafruit_SSD1306.h"
#include <ESP32Servo.h>

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

// Parámetros del escalador
const float scaler_mean[12] = {2840.2095125,799.2035125,226.22943749999996,128.1477875,190.97096249999998,109.76795000000001,510.80218749999995,444.16323750000004,1280.729925,1679.37235,1909.2259625,1391.9486125};
const float scaler_scale[12] = {1345.46228198, 340.95047343, 81.11720282, 45.82085479, 84.5806438, 48.81155884, 195.75138768, 216.1018856, 947.6440102, 964.17111919, 972.63274173,529.81119614};

// Parámetros del PCA
const float pca_components[12][12] = {{0.31298941,0.27318245,0.2771994,0.2856616,0.31965561,0.31112907,0.27776945,0.28143452,0.27309828,0.27960743,0.29931757,0.26696569},
{0.12887764,0.39059383,0.34786031,0.31615608,0.13919486,0.22042138,-0.04728213,-0.33415304,-0.40211311,-0.39993543,-0.31318552,-0.09100786},
{-0.18155077,0.20312106,-0.09720562,-0.16544701,-0.24930204,-0.1375686,0.5169343,-0.05571949,-0.27351267,-0.20623655,0.10612494,0.63949352},
{-0.34555132,-0.2500715,0.4383668,0.40126961,-0.20034058,-0.26502265,0.43279397,0.26572545,0.04032758,-0.01568787,-0.13838914,-0.27487782}};
const float pca_mean[12] = {-4.9960036108132046e-17,1.6653345369377347e-17,5.051514762044462e-16,1.7208456881689927e-16,1.887379141862766e-16,-2.6645352591003756e-16,2.997602166487923e-16,-1.9984014443252818e-16,-6.661338147750939e-17,-9.992007221626409e-17,7.771561172376095e-17,-1.2212453270876723e-16};

// Parámetros del modelo de regresión lineal
const float regression_coefAgua[12] = {0.12369767045684991,-0.8868281996927396,-1.6740155476694727,0.558186354084541};
const float regression_coefBrix[12] = {-0.08299066174229128,0.6477400149116025,1.2618113149641184,-0.45466289793356873};
const float regression_interceptAgua = 48.6874075028292;
const float regression_interceptBrix = 12.357370176962238;


// Función para escalar las características
void scale_features(float features[12]) {
    for (int i = 0; i < 12; i++) {
        features[i] = (features[i] - scaler_mean[i]) / scaler_scale[i];
    }
}

// Función para aplicar PCA a las características
void apply_pca(float features[12], float pca_features[12]) {
    for (int i = 0; i < 12; i++) {
        pca_features[i] = 0;
        for (int j = 0; j < 12; j++) {
            pca_features[i] += (features[j] - pca_mean[j]) * pca_components[i][j];
        }
    }
}

// Función para hacer predicciones
float predictAgua(float features[12]) {
    float prediction1 = regression_interceptAgua;
    for (int i = 0; i < 12; i++) {
        prediction1 += regression_coefAgua[i] * features[i];
    }
    return prediction1;
}
// Función para hacer predicciones
float predictBrix(float features[12]) {
    float prediction2 = regression_interceptBrix;
    for (int i = 0; i < 12; i++) {
        prediction2 += regression_coefBrix[i] * features[i];
    }
    return prediction2;
}
float resultAgua =0;
float resultBrix =0;

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
    float features[12] = {meanR_NIR, meanS_NIR, meanT_NIR, meanU_NIR, meanV_NIR, meanW_NIR, meanViolet_VIS, meanBlue_VIS, meanGreen_VIS, meanYellow_VIS, meanOrange_VIS, meanRed_VIS};
    //Prueba
    //float features[12] = {4629.442, 942.47, 259.333, 144.542, 281.257, 147.713, 459.311, 538.497, 2722.046, 2655.515, 2901.792, 1263.449};
    float pca_features[12];

    // Escalar las características
    scale_features(features);

    // Aplicar PCA
    apply_pca(features, pca_features);

    // Hacer predicción
    float resultAgua = predictAgua(pca_features);
    float resultBrix = predictBrix(pca_features);
  
    // Imprimir el resultado
    Serial.print("Predicción: ");
    Serial.print("Contenido de Agua: ");
    Serial.print(resultAgua);
    Serial.println("Contenido de Brix: ");
    Serial.println(resultBrix);
    
    // Fin de la secuencia de mediciones
    displayMessage("Lectura Terminada");
    displayCounter(contadorMediciones);
    delay(3000);
    displayMessage2("Contenido de Agua:","Contenido de Brix:");
    displayPredict(resultAgua, resultBrix);


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
void displayMessage2(const char *message, const char *message2) {
  selectI2CChannel(7);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Medicion Chontaduro ");
  display.setCursor(0, 16);
  display.print(message);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 32);
  display.print(message2);
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
void displayPredict(float predict , float predict2 ) {
  selectI2CChannel(7);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 24);
  display.print(predict);
  display.setCursor(0, 40);
  display.print(predict2);
  display.display();
}
