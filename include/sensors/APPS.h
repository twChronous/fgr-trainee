// APPS.h
#ifndef APPS_H
#define APPS_H

#include "Component.h"

class Potentiometer : public Component {
private:
    int pin_1;
    int pin_2;
    float lastValue;

public:
    Potentiometer(int pin_1, int pin_2) : pin_1(pin_1), pin_2(pin_2), lastValue(0) {}

    void readValue() {
        // Lê os valores dos potenciômetros e calcula a porcentagem
        float first_pot = (analogRead(pin_1) / 1023.0) * 100;
        float second_pot = (analogRead(pin_2) / 1023.0) * 100;
        // Calcula a diferença absoluta entre os dois potenciômetros
        float difference = abs(first_pot - second_pot);

        if (mediator) {
            if (difference >= 10) {  // Se a diferença for maior que 10%
                lastValue = difference;
                    // Notifica o Mediator sobre a diferença grande como implausibilidade
                return mediator->notify(this, "implausibility");
            }
                // Notifica o Mediator sobre a mudança do potenciômetro, enviando os valores
            return mediator->notify(this, "PotentiometerChange", first_pot, second_pot);
        }
    }
};

#endif
