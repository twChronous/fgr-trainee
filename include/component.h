// Component.h
#ifndef COMPONENT_H
#define COMPONENT_H

#include "Mediator.h"

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
