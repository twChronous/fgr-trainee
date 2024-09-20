#include "sensors/APPS.h"
#include "sensors/gyroHandler.h"
#include "communication/canbase.h"
#include "communication/LoRaModule.h"

#include "Mediator.h"
#include "ConcreteMediator.h"


// Instâncias dos componentes
Gyroscope gyroscope;
CanModule canModule;
LoRaModule loRaModule;

Potentiometer potentiometer(A0, A1); // Ajuste para os pinos corretos do potenciômetro

// Mediator que coordena os componentes
ConcreteMediator mediator(&gyroscope, &canModule, &loRaModule, &potentiometer);

void setup() {
    Serial.begin(115200);

    // Configura o giroscópio e o potenciômetro
    gyroscope.setup();
    // O Potentiometer não precisa de setup adicional, apenas leitura
}

void loop() {
    // Lê os dados do giroscópio e notifica o Mediator
    gyroscope.readData();

    // Lê os valores do potenciômetro e notifica o Mediator se necessário
    potentiometer.readValue();

    delay(2000); // Atraso entre leituras
}
