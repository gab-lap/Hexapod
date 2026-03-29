#ifndef ROBOT_WALK_STATE_H
#define ROBOT_WALK_STATE_H

#include "State.h"

class Robot;

class RobotWalkState : public State<Robot> {
public:
    RobotWalkState(Robot& initOwner, StateMachine<Robot>& initStateMachine)
        : State<Robot> (initOwner, initStateMachine) {}

    void Enter() override;
    void Update() override;
    void Exit() override;
    String GetName() override {
        return "RobotWalkingState";
    }

private:
    int points = 1000;

    Vector2 _leftJoystickTargetVector;
    float _leftJoystickTargetMagnitude;

    Vector2 _leftJoystickCurrentVector;
    float _leftJoystickCurrentMagnitude;

    Vector2 _rightJoystickTargetVector;
    float _rightJoystickTargetMagnitude;

    Vector2 _rightJoystickCurrentVector;
    float _rightJoystickCurrentMagnitude;
};

#endif