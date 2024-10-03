#ifndef LORAMODULE_H
#define LORAMODULE_H

#include "Component.h"
#include "SoftwareSerial.h"
SoftwareSerial loraSerial(2,3);

/**
 * @class LoRaModule
 * @brief Uma classe que representa um módulo de comunicação LoRa.
 * 
 * Esta classe fornece funcionalidades para inicializar e enviar mensagens usando um módulo LoRa.
 * Ela herda da classe Component.
 * 
 * @brief Construtor padrão para a classe LoRaModule.
 *
 *
 * @brief Inicializa o módulo LoRa.
 * 
 * Esta função inicializa a comunicação serial para o módulo LoRa com uma taxa de transmissão de 9600.
 *
 * @brief Envia uma mensagem usando o módulo LoRa.
 * 
 * Ela imprime a mensagem no monitor Serial
 * e a envia através da comunicação serial do LoRa.
 * 
 * @param message A mensagem a ser enviada.
 */
class LoRaModule : public Component {
public:
    LoRaModule() {}

    void begin() {
        loraSerial.begin(9600);
    }
    void sendMessage(const String& message) {
        Serial.print("LoRa Message Sent: ");
        Serial.println(message);
        
        loraSerial.println(message);
    }
};

#endif
