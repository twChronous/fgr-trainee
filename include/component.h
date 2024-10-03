#ifndef COMPONENT_H
#define COMPONENT_H

#include "Mediator.h"

/**
 * @class Component
 * @brief Classe base para componentes que interagem com um mediador.
 *
 * A classe Component fornece uma base para componentes que precisam se comunicar
 * entre si por meio de um mediador. Ela mantém uma referência a um objeto Mediator
 * e fornece um método para definir esse mediador.
 *
 * @protected
 * @var Mediator* mediator
 * Um ponteiro para o mediador que facilita a comunicação entre componentes.
 *
 * @public
 * @fn Component(Mediator* mediator = nullptr)
 * Construtor que inicializa o componente com um mediador opcional.
 * 
 * @param mediator
 * Um ponteiro para um objeto Mediator. O padrão é nullptr se não for fornecido.
 *
 * @fn void setMediator(Mediator* mediator)
 * Define o mediador para o componente.
 * 
 * @param mediator
 * Um ponteiro para um objeto Mediator.
 */
class Component {
protected:
    Mediator* mediator;
    
public:
    Component(Mediator* mediator = nullptr) : mediator(mediator) {}
    
    void setMediator(Mediator* mediator) {
        this->mediator = mediator;
    }
};

#endif
