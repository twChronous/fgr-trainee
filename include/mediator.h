// Mediator.h
#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <Arduino.h>

// Classe base Mediator
class Component; // Declaração adiantada da classe Component

class Mediator {
public:
    virtual void notify(Component* sender, const String& event,
                        float first_pot = 0, float second_pot = 0,
                        float accelX = 0, float accelY = 0, float accelZ = 0,
                        float gyroX = 0, float gyroY = 0, float gyroZ = 0) = 0; // Função virtual pura
};

#endif
