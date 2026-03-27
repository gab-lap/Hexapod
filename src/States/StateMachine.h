#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "Arduino.h"

template <typename T> class State; 

template <typename T>
class StateMachine {
public:
    State<T>* currentState;

    StateMachine() {

    }

    void Initialize(State<T>* initialState) {
        currentState = initialState;
        if (currentState) 
            currentState->Enter();
    }

    void ChangeState(State<T>* nextState) {
        if (currentState) 
            currentState->Exit();

        Serial.println("Previous State: " + currentState->GetName() + ", Next State: " + nextState->GetName());
        currentState = nextState;

        if (currentState) 
            currentState->Enter();
    }
};

#endif