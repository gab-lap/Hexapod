#include "Robot.h"
#include "GaitData.h"
#include "Leg.h"

Robot::Robot(RobotPhysicalData initPhysicalData, RobotLegs initRobotLegs)
    :   physicalData(initPhysicalData),
        robotLegs(initRobotLegs),

        stateMachine(),
        walkState(*this, stateMachine),
        sleepState(*this, stateMachine)
{
    stateMachine.Initialize(&sleepState); // to cahnge with sleep state
    currentGait = &Gaits::Tripod;
    // Set pushFraction in all the legs
    for (int i = 0; i < NUM_LEGS; i++) {
        Leg* leg = getLeg(i);
        leg->walkingData.pushFraction = currentGait->pushFraction;
        leg->walkingData.currentLegPosition = Vector3(0, 200, 100);
    }
}

void Robot::Begin()
{
    transmitter.Begin();
}

void Robot::Update()
{
    transmitter.Update();
    //Serial.print(" transmitter.isJ2Clicked(): ");Serial.println(transmitter.isJ2Clicked());

    if(!transmitter.isConnected()) {
        Serial.println(" YEEPING FOR LACK OF CONNECtiON");
        if (stateMachine.currentState != &sleepState) {
            stateMachine.ChangeState(&sleepState);
        }
    }

    if (stateMachine.currentState != nullptr)
        stateMachine.currentState->Update();
}

void Robot::ChangeGait(/*const*/ GaitData* newGait)
{
    currentGait = newGait;
    // update pushFraction in leg every time robot changes state
    for (int i = 0; i < NUM_LEGS; i++) {
        Leg* leg = getLeg(i);
        leg->walkingData.pushFraction = currentGait->pushFraction;
    }
    Serial.print("Switched to gait: ");
    Serial.println(currentGait->label);
}

Leg* Robot::getLeg(int index)
{
    switch(index) {
        case 0: return robotLegs.middleRight;
        case 1: return robotLegs.frontRight;
        case 2: return robotLegs.frontLeft;
        case 3: return robotLegs.middleLeft;
        case 4: return robotLegs.backLeft;
        case 5: return robotLegs.backRight;
        default: return nullptr;
    }
}

    