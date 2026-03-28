#ifndef LEG_LIFING_STATE_H
#define LEG_LIFING_STATE_H

#include "State.h"

class Leg; // Forward Declaration

class LegLiftingState : public State<Leg> {
public:

    LegLiftingState(Leg& initOwner, StateMachine<Leg>& initMachine) 
        : State<Leg>(initOwner, initMachine) {}

    void Enter() override;
    void Update() override;
    void Exit() override;
    String GetName() override {
        String name = "LegLiftingState";
        return name;
    }
};

#endif