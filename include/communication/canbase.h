// CanModule.h
#ifndef CANMODULE_H
#define CANMODULE_H

#include "Component.h"
#include <mcp_can.h>
#include <SPI.h>

class CanModule : public Component {
public:
    CanModule() {}

    void sendMessage(const String& message) {
        // Simulação de envio de mensagem CAN
        Serial.print("CAN Message Sent: ");
        Serial.println(message);
    }
};

#endif
