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

const float coefficientsAgua[12] = {-0.470568824213527, -1.3213401379061616, -0.6075575875074753, 0.946128407899801, 0.7553447939593042, 0.45596753189281725, -0.44602727349745014, 0.6921744799489669, -0.09170742169461993, 1.422270349513134, -0.21168182616992212, -0.7907432538865804};
const float interceptAgua = 48.544313691550918;
const float coefficientsBrix[12] = {0.23478898464817877, 1.0834654097138745, 0.5006011055255243, -0.7732809210368419, -0.6376333113049909, -0.26782420975405846, 0.1706929426368684, -0.25290109095454033, 0.18726094139025815, -1.155958141663847, 0.028967546745144585, 0.7463827464971932};
const float interceptBrix = 12.48912437;


const float coefficients[12] = {-0.470568824213527, -1.3213401379061616, -0.6075575875074753, 0.946128407899801, 0.7553447939593042, 0.45596753189281725, -0.44602727349745014, 0.6921744799489669, -0.09170742169461993, 1.422270349513134, -0.21168182616992212, -0.7907432538865804};
const float X_mean[] = {2894.207621052632, 812.0145263157897, 229.163852631579, 129.1895894736842, 193.0910526315789, 110.8488105263158, 529.3741473684212, 461.3371263157895, 1328.7415263157893, 1720.6807263157893, 1980.5500421052634, 1440.8853263157898};
const float y_mean = 48.54431369155091;
const int num_features = sizeof(coefficients) / sizeof(coefficients[0]);

// Función para predecir usando el modelo PLS
float predictPLS(float features[]) {
  float result = y_mean;
  for (int i = 0; i < num_features; i++) {
    result += (features[i] - X_mean[i]) * coefficients[i];
  }
  return result;
}

// Función para hacer predicciones
float predictAgua(float features[12]) {
    float prediction1 = interceptAgua;
    for (int i = 0; i < 12; i++) {
        prediction1 += coefficientsAgua[i] * features[i];
    }
    return prediction1;
}
// Función para hacer predicciones
float predictBrix(float features[12]) {
    float prediction2 = interceptBrix;
    for (int i = 0; i < 12; i++) {
        prediction2 += coefficientsBrix[i] * features[i];
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
    //float features[12] = {meanR_NIR, meanS_NIR, meanT_NIR, meanU_NIR, meanV_NIR, meanW_NIR, meanViolet_VIS, meanBlue_VIS, meanGreen_VIS, meanYellow_VIS, meanOrange_VIS, meanRed_VIS};
    float features[12] = {4629.442, 942.47, 259.333, 144.542, 281.257, 147.713, 459.311, 538.497, 2722.046, 2655.515, 2901.792, 1263.449};
    // Realizar predicción
    float prediction = predictPLS(features);

  // Imprimir resultado
    Serial.print("Predicción: ");
    Serial.println(prediction);

    
    // Hacer predicción
    resultAgua = predictAgua(features);
    resultBrix = predictBrix(features);
    
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
