#ifndef ROBOT_SLEEP_STATE_H
#define ROBOT_SLEEP_STATE_H

#include "State.h"
#include "vectors.h"
#include "config.h"
#include "models.h"

class Robot;

class RobotSleepState : public State<Robot> {
public:
    RobotSleepState(Robot& initOwner, StateMachine<Robot>& initStateMachine)
        : State<Robot> (initOwner, initStateMachine) {}

    void Enter() override;
    void Update() override;
    void Exit() override;
    String GetName() override {
        return "RobotSleepState";
    }
};

#endif