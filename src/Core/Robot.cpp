#include "Robot.h"
#include "GaitData.h"

Robot::Robot(RobotPhysicalData initPhysicalData, RobotLegs initRobotLegs)
    :   physicalData(initPhysicalData),
        robotLegs(initRobotLegs),

        stateMachine(),
        walkState(*this, stateMachine)
{
    stateMachine.Initialize(&walkState); // to cahnge with sleep state
    currentGait = &Gaits::Tripod;
}

void Robot::Begin()
{
    transmitter.Begin();
}

void Robot::Update()
{
    transmitter.Update();
    if (stateMachine.currentState != nullptr)
        stateMachine.currentState->Update();
}

void Robot::ChangeGait(const GaitData* newGait)
{
    currentGait = newGait;
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

    