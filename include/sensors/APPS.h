#ifndef APPS_H
#define APPS_H

#include "CONFIG.h"
#include "Component.h"

/**
 * @class APPS
 * @brief Uma classe para representar um componente potenciômetro com dois pinos analógicos.
 * 
 * Esta classe lê valores de dois potenciômetros e calcula seus percentuais.
 * Também verifica a diferença entre os valores dos dois potenciômetros e notifica
 * um mediador se a diferença for significativa.
 * 
 * @details
 * A classe herda da classe Component e usa dois pinos analógicos para ler os valores
 * dos potenciômetros. Ela calcula os valores percentuais para cada potenciômetro
 * e verifica a diferença entre eles. Se a diferença for menor que 10%, faz a média
 * dos dois percentuais. Se a diferença for maior ou igual a 10%, marca o valor como inválido.
 * Em seguida, a classe notifica um mediador sobre a alteração ou a implausibilidade.
 * 
 * @param pin_1 O pino analógico para o primeiro potenciômetro (0-3.3V).
 * @param pin_2 O pino analógico para o segundo potenciômetro (0-5V).
 * 
 * 
 * @fn APPS::Potentiometer(int pin_1, int pin_2)
 * @brief Constrói um objeto Potenciômetro com os pinos analógicos especificados.
 * 
 * @fn void APPS::readValue()
 * @brief Lê os valores dos potenciômetros e calcula seus percentuais.
 * 
 * Esta função lê os valores analógicos dos dois potenciômetros e calcula seus percentuais.
 * Em seguida, verifica a diferença entre os dois percentuais. Se a diferença for menor que 10%, faz a média dos dois percentuais.
 * Se a diferença for maior ou igual a 10%, marca o valor como inválido.
 * A função então notifica um mediador sobre a alteração ou a implausibilidade.
 */
class Potentiometer : public Component {
public:
    Potentiometer();

    void readValue() {
        int pot1Value = analogRead(POT_3V);
        int pot2Value = analogRead(POT_5V);

        // Cálculo das porcentagens (de 0 a 100%)
        float pot1Percent = (pot1Value / 675.0) * 100.0;
        float pot2Percent = (pot2Value / 1023.0) * 100.0;

        // Calculando a diferença entre os dois potenciômetros
        float difference = abs(pot1Percent - pot2Percent);
        float APPSValueRAW = (pot1Value + pot2Value) / 2.0;
        float APPSValue;
        if (difference < 10.0) {
            // Quando a diferença é menor que 10%, tira a média dos dois
            APPSValue = (pot1Percent + pot2Percent) / 2.0;
        } else {
            // Se a diferença for maior ou igual a 10%, o valor não é válido
            APPSValue = -1; 
        }
        if (mediator) {
            if (APPSValue != -1) {  // Se a diferença for maior que 10%
                    // Notifica o Mediator sobre a diferença grande como implausibilidade
                    return mediator->notify(this, "PotentiometerChange", APPSValue, APPSValueRAW);
            }
                // Notifica o Mediator sobre a mudança do potenciômetro, enviando os valores
                return mediator->notify(this, "implausibility");
        }
    }
};

#endif
