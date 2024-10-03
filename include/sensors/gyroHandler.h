#ifndef GYROSCOPE_H
#define GYROSCOPE_H

#include "Component.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

/**
 * @class Gyroscope
 * @brief Classe para lidar com operações do sensor giroscópio usando o MPU6050.
 * 
 * Esta classe fornece métodos para inicializar o sensor giroscópio, ler dados e 
 * detectar a direção do movimento com base nas leituras do acelerômetro.
 * 
 * @section Dependencies
 * - Adafruit_MPU6050 library
 * - Serial communication
 * 
 * @section Example
 * @code
 * Gyroscope gyro;
 * gyro.setup();   // Inicializa o giroscópio
 * gyro.readData(); // Lê dados do giroscópio
 * @endcode
 * 
 * @section Methods
 * 
 * @fn Gyroscope::Gyroscope()
 * @brief Construtor padrão para a classe Gyroscope.
 * 
 * Este construtor não recebe parâmetros e inicializa o objeto Gyroscope.
 * 
 * @fn void Gyroscope::setup()
 * @brief Inicializa o sensor giroscópio e define sua configuração.
 * 
 * Este método inicializa o sensor MPU6050, define o alcance do acelerômetro e do giroscópio,
 * e a largura de banda do filtro. Se a inicialização falhar, uma mensagem de erro será
 * exibida e o programa entrará em um loop infinito.
 * 
 * @fn void Gyroscope::readData()
 * @brief Lê dados dos sensores giroscópio e acelerômetro.
 * 
 * Este método recupera dados de aceleração, giroscópio e temperatura do sensor MPU6050. 
 * Os valores de aceleração e rotação são impressos no monitor Serial. Além disso, a 
 * direção do movimento é detectada com base nas leituras do acelerômetro e o mediador 
 * é notificado, se estiver disponível.
 * 
 * @fn String Gyroscope::detectMovementDirection(float accelX, float accelY, float accelZ)
 * @brief Detecta a direção do movimento com base nas leituras do acelerômetro.
 * 
 * @param accelX O valor de aceleração no eixo X (m/s²).
 * @param accelY O valor de aceleração no eixo Y (m/s²).
 * @param accelZ O valor de aceleração no eixo Z (m/s²).
 * @return Uma string representando a direção detectada do movimento, que pode ser
 *         "Forward", "Backward", "Right", "Left", "Up", "Down", ou uma string vazia
 *         se não houver movimento detectado.
 * 
 * Este método compara as leituras do acelerômetro contra um limite definido para 
 * determinar a direção do movimento e retorna a direção correspondente como uma string.
 */

class Gyroscope : public Component {
private:
    Adafruit_MPU6050 mpu;

public:
    Gyroscope() {}

    void setup() {
        if (!mpu.begin()) {
            Serial.println("Falha ao conectar o módulo");
            while (1) {
                delay(10);
            }
        }
        Serial.println("Módulo conectado");

        mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
        mpu.setGyroRange(MPU6050_RANGE_500_DEG);
        mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
    }

    void readData() {
        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp);

        Serial.print("Aceleração X: ");
        Serial.print(a.acceleration.x);
        Serial.print(", Y: ");
        Serial.print(a.acceleration.y);
        Serial.print(", Z: ");
        Serial.print(a.acceleration.z);
        Serial.println(" m/s^2");

        Serial.print("Rotação X: ");
        Serial.print(g.gyro.x);
        Serial.print(", Y: ");
        Serial.print(g.gyro.y);
        Serial.print(", Z: ");
        Serial.print(g.gyro.z);
        Serial.println(" rad/s");

        String movement = detectMovementDirection(a.acceleration.x, a.acceleration.y, a.acceleration.z);
        Serial.println(movement);

        // Notifica o Mediator
        if (mediator) {
            mediator->notify(this, "GyroscopeRead", a.acceleration.x, a.acceleration.y, a.acceleration.z, g.gyro.x, g.gyro.y, g.gyro.z);
        }
    }

    String detectMovementDirection(float accelX, float accelY, float accelZ) {
        float threshold = 1.0; // Limite para detectar movimento
        String Moviment = "";

        if (accelY > threshold) {
            Moviment = "Forward";
        } else if (accelY < -threshold) {
            Moviment = "Backward";
        }

        if (accelX > threshold) {
            Moviment = "Right";
        } else if (accelX < -threshold) {
            Moviment = "Left";
        }

        if (accelZ > threshold) {
            Moviment = "Up";
        } else if (accelZ < -threshold) {
            Moviment = "Down";
        }

        return Moviment;
    }
};

#endif