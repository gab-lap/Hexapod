#ifndef LEG_SLEEP_STATE_H
#define LEG_SLEEP_STATE_H

#include "State.h"

class Leg; // Forward Declaration

class LegSleepState : public State<Leg> {
public:

    LegSleepState(Leg& initOwner, StateMachine<Leg>& initMachine) 
        : State<Leg>(initOwner, initMachine) {}

    void Enter() override;
    void Update() override;
    void Exit() override;
    String GetName() override {
        String name = "LegSleepState";
        return name;
    }
};

#endif