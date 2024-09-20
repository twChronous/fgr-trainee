// LoRaModule.h
#ifndef LORAMODULE_H
#define LORAMODULE_H

#include "Component.h"

class LoRaModule : public Component {
public:
    LoRaModule() {}

    void sendMessage(const String& message) {
        // Simulação de envio de mensagem LoRa
        Serial.print("LoRa Message Sent: ");
        Serial.println(message);
    }
};

#endif
