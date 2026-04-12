#ifndef ROBOT_H
#define ROBOT_H

#include "StateMachine.h"
#include "State.h"
#include "RobotWalkState.h"
#include "models.h"
#include "GaitData.h"
#include "RC_receiver.h"
#include "RobotSleepState.h"

class Robot {
public:
    StateMachine<Robot> stateMachine;
    RobotSleepState sleepState;  // change from pointers to normal variables once specific state files are created
    State<Robot>* standingState;
    State<Robot>* idleState;
    RobotWalkState walkState;
    RobotPhysicalData physicalData; // to add more variables, so far only height
    /*const*/ GaitData* currentGait;
    RC_Transmitter transmitter;
    // add legs, maybe in a struct?
    RobotLegs robotLegs;

    Robot(RobotPhysicalData initPhysicalData, RobotLegs initRobotLegs);
    void Begin();
    void Update();
    void ChangeGait(/*const*/ GaitData* newGait);
    Leg* getLeg(int index);
};

#endif