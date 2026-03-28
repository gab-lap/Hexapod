#ifndef ROBOT_H
#define ROBOT_H

#include "StateMachine.h"
#include "State.h"
#include "RobotWalkState.h"
#include "models.h"
#include "GaitData.h"

class Robot {
public:
    StateMachine<Robot> stateMachine;
    State<Robot>* sleepState;  // change from pointers to normal variables once specific state files are created
    State<Robot>* standingState;
    State<Robot>* idleState;
    RobotWalkState walkState;
    RobotPhysicalData physicalData; // to add more variables, so far only height
    const GaitData* currentGait;
    // add legs, maybe in a struct?

    Robot(RobotPhysicalData initPhysicalData);
    void Begin();
    void Update();
    void ChangeGait(const GaitData* newGait);
};

#endif