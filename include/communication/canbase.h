#ifndef CANMODULE_H
#define CANMODULE_H

#include "Component.h"
#include <mcp_can.h>
#include <SPI.h>

#define CAN_CS_PIN 10   // Defina o pino CS do MCP2515 (ajuste conforme necessário)
MCP_CAN CAN0(CAN_CS_PIN);  // Instancia o objeto MCP_CAN com o pino CS

/**
 * @class CanModule
 * @brief Uma classe para lidar com a comunicação CAN usando o módulo MCP2515.
 * 
 * Esta classe fornece métodos para inicializar o módulo CAN MCP2515 e enviar mensagens pelo barramento CAN.
 * 
 * 
 * @fn CanModule::CanModule()
 * @brief Construtor padrão para a classe CanModule.
 * 
 * @fn void CanModule::begin()
 * @brief Inicializa o módulo CAN MCP2515 e o configura no modo normal.
 * 
 * Este método inicializa o módulo CAN MCP2515 com uma taxa de transmissão de 500kbps e o configura no modo normal,
 * permitindo enviar e receber mensagens. Ele imprime o status da inicialização no monitor Serial.
 * 
 * @fn void CanModule::sendMessage(const String& message)
 * @brief Envia uma mensagem pelo barramento CAN.
 * 
 * Este método divide a mensagem de entrada em pacotes de até 8 bytes e envia cada pacote pelo barramento CAN.
 * Ele imprime o status de cada transmissão de pacote no monitor Serial.
 * 
 * @param message A mensagem em formato de string a ser enviada pelo barramento CAN.
 */
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
