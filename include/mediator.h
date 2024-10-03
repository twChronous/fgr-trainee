#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <Arduino.h>

// Classe base Mediator
class Component; // Declaração adiantada da classe Component

/**
 * @class Mediator
 * @brief Classe base abstrata para o padrão de design Mediator.
 *
 * A classe Mediator define uma interface para comunicação entre componentes.
 * Ela permite que os componentes notifiquem uns aos outros sobre eventos sem ter dependências diretas.
 */
class Mediator {
public:
    virtual void notify(Component* sender, const String& event,
                        float APPSValue = 0, float APPSValueRAW = 0,
                        float accelX = 0, float accelY = 0, float accelZ = 0,
                        float gyroX = 0, float gyroY = 0, float gyroZ = 0) = 0; // Função virtual pura
};

#endif
