#ifndef EMPTY_LEG_STATE_H
#define EMPTY_LEG_STATE_H

#include "State.h"

class Leg;

class EmptyLegState : public State<Leg> {
public:

    EmptyLegState(Leg& initOwner, StateMachine<Leg>& initMachine) 
        : State<Leg>(initOwner, initMachine) { }

    void Enter() override {}
    void Update() override {}
    void Exit() override {}
    String GetName() override {
        String name = "EmptyLegState";
        return name; 
    }
};

#endif