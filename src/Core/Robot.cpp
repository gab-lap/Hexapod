#include "Robot.h"
#include "GaitData.h"

Robot::Robot(RobotPhysicalData initPhysicalData)
    :   physicalData(initPhysicalData),

        stateMachine(),
        walkState(*this, stateMachine)
{
    stateMachine.Initialize(&walkState); // to cahnge with sleep state
    currentGait = &Gaits::Tripod;
}

void Robot::Begin()
{
}

void Robot::Update()
{
}

void Robot::ChangeGait(const GaitData* newGait)
{
    currentGait = newGait;
    Serial.print("Switched to gait: ");
    Serial.println(currentGait->label);
}
