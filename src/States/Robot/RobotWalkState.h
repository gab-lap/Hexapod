#ifndef ROBOT_WALK_STATE_H
#define ROBOT_WALK_STATE_H

#include "State.h"

class Robot;

class RobotWalkState : public State<Robot> {
public:
    RobotWalkState(Robot& initOwner, StateMachine<Robot>& initStateMachine)
        : State<Robot> (initOwner, initStateMachine) {}

    void Enter() override;
    void Loop() override;
    void Exit() override;
    String GetName() override {
        return "RobotWalkingState";
    }
};

#endif