#ifndef LEG_STANDING_STATE_H
#define LEG_STANDING_STATE_H

#include "State.h"

class Leg; // Forward declaration

class LegStandingState : public State<Leg> {
public:

    LegStandingState(Leg& initOwner, StateMachine<Leg>& initMachine) 
        : State<Leg>(initOwner, initMachine) {}

    void Enter() override;
    void Loop() override;
    void Exit() override;
    String GetName() override {
        String name = "LegStandingState";
        return name;
    }
};

#endif