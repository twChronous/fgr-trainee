#ifndef CONCRETEMEDIATOR_H
#define CONCRETEMEDIATOR_H

#include "Mediator.h"
#include "sensors/APPS.h"
#include "sensors/gyroHandler.h"
#include "communication/canbase.h"
#include "communication/LoRaModule.h"

/**
 * @class ConcreteMediator
 * @brief Uma implementação concreta da interface Mediator que coordena a comunicação entre vários componentes.
 *
 * Esta classe atua como um mediador para facilitar a comunicação entre diferentes componentes, como Gyroscope, CanModule, 
 * LoRaModule e Potentiometer. Ela recebe eventos desses componentes e os processa conforme necessário.
 *
 * @details
 * A classe ConcreteMediator mantém ponteiros para os componentes que media. Ela se define como o mediador para os 
 * componentes Gyroscope e Potentiometer na sua construção. O método notify é sobrescrito para lidar com eventos específicos 
 * e encaminhar mensagens para o CanModule e o LoRaModule.
 *
 * @note
 * O método notify processa três tipos de eventos: "PotentiometerChange", "GyroscopeRead" e "implausibility". 
 * Dependendo do evento, constrói uma mensagem e a envia via CAN e LoRa.
 *
 * @param gyroscope Ponteiro para o componente Gyroscope.
 * @param canModule Ponteiro para o componente CanModule.
 * @param loRaModule Ponteiro para o componente LoRaModule.
 * @param potentiometer Ponteiro para o componente Potentiometer.
 *
 * @method ConcreteMediator
 * @brief Construtor que inicializa o mediador com os componentes fornecidos.
 * @param g Ponteiro para o componente Gyroscope.
 * @param can Ponteiro para o componente CanModule.
 * @param loRa Ponteiro para o componente LoRaModule.
 * @param pot Ponteiro para o componente Potentiometer.
 *
 * @method notify
 * @brief Lida com eventos dos componentes e encaminha mensagens para CanModule e LoRaModule.
 * @param sender Ponteiro para o componente que enviou o evento.
 * @param event O tipo de evento como uma string.
 * @param APPSValue O valor do APPS (padrão é 0).
 * @param APPSValueRAW O valor bruto do APPS (padrão é 0).
 * @param accelX O valor de aceleração no eixo X (padrão é 0).
 * @param accelY O valor de aceleração no eixo Y (padrão é 0).
 * @param accelZ O valor de aceleração no eixo Z (padrão é 0).
 * @param gyroX O valor do giroscópio no eixo X (padrão é 0).
 * @param gyroY O valor do giroscópio no eixo Y (padrão é 0).
 * @param gyroZ O valor do giroscópio no eixo Z (padrão é 0).
 */
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
                float APPSValue = 0, float APPSValueRAW = 0,
                float accelX = 0, float accelY = 0, float accelZ = 0,
                float gyroX = 0, float gyroY = 0, float gyroZ = 0) override {

        if (event == "PotentiometerChange") {
            // Exemplo de como os dados podem ser processados para o CAN e LoRa
            String message = "Pedal: " + String(APPSValue) + "% | Valor bruto: " + String(APPSValueRAW);
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