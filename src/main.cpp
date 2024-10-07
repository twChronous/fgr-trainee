#include "sensors/APPS.h"
#include "sensors/gyroHandler.h"
#include "communication/canbase.h"
#include "communication/LoRaModule.h"

#include "Mediator.h"
#include "ConcreteMediator.h"

Gyroscope gyroscope;
CanModule canModule;
LoRaModule loRaModule;

Potentiometer potentiometer;

// Mediator que coordena os componentes
ConcreteMediator mediator(&gyroscope, &canModule, &loRaModule, &potentiometer);

/**
 * @brief Inicializa a comunicação serial, o giroscópio e o módulo LoRa.
 * 
 * Esta função configura a comunicação serial com uma taxa de transmissão de 115200,
 * configura o giroscópio e inicializa o módulo LoRa para comunicação.
 */

void setup() {
    Serial.begin(115200);

    // Configura o giroscópio e o potenciômetro
    gyroscope.setup();

    loRaModule.begin();
    //canModule.begin();
}

/**
 * @brief Função principal do loop que lê dados dos sensores e introduz um atraso.
 *
 * Esta função executa as seguintes tarefas em um loop:
 * - Lê dados do giroscópio e notifica o Mediator.
 * - Lê valores do potenciômetro e notifica o Mediator, se necessário.
 * - Introduz um atraso de 2000 milissegundos entre as leituras.
 */
void loop() {
    // Lê os dados do giroscópio e notifica o Mediator
    gyroscope.readData();

    // Lê os valores do potenciômetro e notifica o Mediator se necessário
    potentiometer.readValue();

    delay(2000); // Atraso entre leituras
}
