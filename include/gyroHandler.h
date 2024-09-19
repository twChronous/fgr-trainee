#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

//Variaveis para receber os valores de aceleração dos eixos
int valoranteriorX = 0 ;
int valoranteriorY = 0 ;
int valoranteriorZ = 0 ;

void gyroSetup() {
    //Verifica se o módulo GY-521 (MPU6050) está conectado 
  if (!mpu.begin()) {
    Serial.println("Falha ao conectar o módulo");// caso não encontre
    while (1) {
      delay(10);
    }
  }
  Serial.println("Módulo conectado"); 

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Variação do aceleremetro para: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Variação do Giroscópio para: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filtro: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }
}
String detectMovementDirection(float accelX, float accelY, float accelZ) {
    // Define threshold for detecting movement
    float threshold = 1.0; // You can adjust this value based on the sensitivity you need
    String Moviment = "";
    // Forward/Backward detection (based on Y axis)
    if (accelY > threshold) {
        Moviment = "Forward";
    } else if (accelY < -threshold) {
        Moviment = "Backward";
    }

    // Left/Right detection (based on X axis)
    if (accelX > threshold) {
        Moviment = "Right";
    } else if (accelX < -threshold) {
        Moviment =  "Left";
    }
    // Up/Down detection (based on Z axis)
    if (accelZ > threshold) {
        Moviment =  "Up";
    } else if (accelZ < -threshold) {
        Moviment =  "Down";
    }
    return Moviment;
}
void gyroLoop() {
    //Variáveis para leitura do Acelerometro, Giroscopio e Tempratura.
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  //Imprime os valores do acelerometro no monitor serial
  Serial.print("Aceleração X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");
//Imprime os valores do giroscopio no monitor serial
  Serial.print("Rotação X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");
//Imprime os valores do termometro no monitor serial
  Serial.print("Temperatura: ");
  Serial.print(temp.temperature);
  Serial.println(" °C");

  Serial.println("");
  delay(2000); // Atraso definido em milisegundos entre as leituras ** EDITAVEL**
  Serial.print(detectMovementDirection(a.acceleration.x, a.acceleration.y, a.acceleration.z));
  Serial.println("");
}
