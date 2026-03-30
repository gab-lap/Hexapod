#ifndef ROBOT_WALK_STATE_H
#define ROBOT_WALK_STATE_H

#include "State.h"
#include "vectors.h"
#include "config.h"
#include "models.h"

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

    Vector3 getGaitPoint(Leg* leg, float pushfraction);

private:
    int _points = 1000;

    Vector2 _leftJoystickTargetVector;
    float _leftJoystickTargetMagnitude;

    Vector2 _leftJoystickCurrentVector;
    float _leftJoystickCurrentMagnitude;

    Vector2 _rightJoystickTargetVector;
    float _rightJoystickTargetMagnitude;

    Vector2 _rightJoystickCurrentVector;
    float _rightJoystickCurrentMagnitude;

    float _forwardAmount;
    float _turnAmount;
};

#endif