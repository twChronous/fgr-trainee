// CanModule.h
#ifndef CANMODULE_H
#define CANMODULE_H

#include "Component.h"
#include <mcp_can.h>
#include <SPI.h>

#define CAN_CS_PIN 10   // Defina o pino CS do MCP2515 (ajuste conforme necessário)
MCP_CAN CAN0(CAN_CS_PIN);  // Instancia o objeto MCP_CAN com o pino CS

class CanModule : public Component {
public:
    CanModule() {}

    void begin() {

    // Inicializa o módulo MCP2515 no baud rate de 500kbps
    if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK) {
        Serial.println("MCP2515 Initialized Successfully!");
    } else {
        Serial.println("Error Initializing MCP2515...");
        while (1);
    }

    // Define o módulo CAN para o modo normal (pode enviar/receber)
    CAN0.setMode(MCP_NORMAL);
    Serial.println("CAN BUS: In Normal Mode");
    }
    void sendMessage(const String& message) {
    int len = message.length();  // Comprimento da string
    int totalPackets = (len + 7) / 8;  // Divide a string em pacotes de até 8 bytes
    
    for (int i = 0; i < totalPackets; i++) {
        byte data[8] = {0};  // Inicializa o buffer de dados
        int startIdx = i * 8;  // Índice inicial do pacote
        
        // Preenche o buffer de dados com parte da string
        for (int j = 0; j < 8 && (startIdx + j) < len; j++) {
            data[j] = message[startIdx + j];
        }

        // Envia o pacote via CAN (ID = 0x100)
        if (CAN0.sendMsgBuf(0x100, 0, 8, data) == CAN_OK) {
            Serial.print("Packet ");
            Serial.print(i + 1);
            Serial.println(" Sent Successfully!");
        } else {
            Serial.print("Error Sending Packet ");
            Serial.println(i + 1);
        }

        delay(100);  // Pequeno atraso entre pacotes para evitar sobrecarga
    }
}
};

#endif
