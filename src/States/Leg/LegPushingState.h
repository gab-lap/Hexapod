#ifndef LEG_PUSHING_STATE_H
#define LEG_PUSHING_STATE_H

#include "State.h"

class Leg; // Forward Declaration

class LegPushingState : public State<Leg> {
public:

    LegPushingState(Leg& initOwner, StateMachine<Leg>& initMachine) 
        : State<Leg>(initOwner, initMachine) {}

    void Enter() override;
    void Loop() override;
    void Exit() override;
    String GetName() override {
        String name = "LegPushingState";
        return name;
    }
};

#endif