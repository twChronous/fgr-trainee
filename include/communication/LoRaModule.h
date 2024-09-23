// LoRaModule.h
#ifndef LORAMODULE_H
#define LORAMODULE_H

#include "Component.h"
#include "SoftwareSerial.h"
SoftwareSerial loraSerial(2,3);

class LoRaModule : public Component {
public:
    LoRaModule() {}

    void begin() {
        loraSerial.begin(9600);
    }
    void sendMessage(const String& message) {
        // Simulação de envio de mensagem LoRa
        Serial.print("LoRa Message Sent: ");
        Serial.println(message);
        
        loraSerial.println(message);
    }
};

#endif
