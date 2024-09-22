// ConcreteMediator.h
#ifndef CONCRETEMEDIATOR_H
#define CONCRETEMEDIATOR_H

#include "Mediator.h"
#include "sensors/APPS.h"
#include "sensors/gyroHandler.h"
#include "communication/canbase.h"
#include "communication/LoRaModule.h"

class ConcreteMediator : public Mediator {
private:
    Gyroscope* gyroscope;
    CanModule* canModule;
    LoRaModule* loRaModule;
    Potentiometer* potentiometer;

public:
    ConcreteMediator(Gyroscope* g, CanModule* can, LoRaModule* loRa, Potentiometer* pot)
        : gyroscope(g), canModule(can), loRaModule(loRa), potentiometer(pot) {
        gyroscope->setMediator(this);
        potentiometer->setMediator(this);
    }

    void notify(Component* sender, const String& event,
                float first_pot = 0, float second_pot = 0,
                float accelX = 0, float accelY = 0, float accelZ = 0,
                float gyroX = 0, float gyroY = 0, float gyroZ = 0) override {

        if (event == "PotentiometerChange") {
            // Exemplo de como os dados podem ser processados para o CAN e LoRa
            String message = "Pot 1: " + String(first_pot) + "%, Pot 2: " + String(second_pot) + "%";
            Serial.println("Evento PotentiometerChange detectado");
            Serial.println(message);

            // Enviar mensagem via CAN e LoRa
            canModule->sendMessage(message);
            loRaModule->sendMessage(message);
        }

        if (event == "GyroscopeRead") {
            String message = "Accel X: " + String(accelX) + " Y: " + String(accelY) + " Z: " + String(accelZ) +
                             " | Gyro X: " + String(gyroX) + " Y: " + String(gyroY) + " Z: " + String(gyroZ);

            canModule->sendMessage(message);
            loRaModule->sendMessage(message);
        }
        if (event == "implausibility") {
            String message = "KILL";
            canModule->sendMessage(message);
            loRaModule->sendMessage(message);
        }
    }
};

#endif
