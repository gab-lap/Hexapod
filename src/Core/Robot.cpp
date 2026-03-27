#include "Robot.h"

Robot::Robot(RobotPhysicalData initPhysicalData)
    :   physicalData(initPhysicalData),

        stateMachine(),
        walkState(*this, stateMachine)
{
    stateMachine.Initialize(&walkState); // to cahnge with sleep state
}

void Robot::Begin()
{
}

void Robot::Loop()
{
}
