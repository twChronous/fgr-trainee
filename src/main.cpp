#include <Arduino.h>

//Libs Criadas por mim
#include "eventEmitter.h"
#include "gyroHandler.h"

void setup(void) {
    Serial.begin(115200); // iniciar o monitor serial 
    gyroSetup();
    Serial.println("");
    delay(100);
}

void loop() {
  gyroLoop();
}