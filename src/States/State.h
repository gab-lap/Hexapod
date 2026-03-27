#ifndef STATE_H
#define STATE_H

#include "StateMachine.h"

template <typename T> class StateMachine; // Forward declaration
template <typename T>

class State {
public:
    T& owner;
    StateMachine<T>& stateMachine;

    State(T& initOwner, StateMachine<T>& initMachine) 
        : owner(initOwner), stateMachine(initMachine) {}
    
    virtual void Enter();
    virtual void Loop();
    virtual void Exit();
    virtual String GetName();
};

#endif
