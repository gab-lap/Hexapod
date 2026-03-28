#include "Leg.h"
#include "InverseKinematics.h"

Leg::Leg(VirtualServo *j1, VirtualServo *j2, VirtualServo *j3, LegPhysicalData initPhysicalData) 
    : joint1(j1), 
      joint2(j2), 
      joint3(j3),
      physicalData(initPhysicalData),


      stateMachine(),
      sleeping(*this, stateMachine),
      standing(*this, stateMachine),
      pushing(*this, stateMachine),
      lifting(*this, stateMachine)
{
    stateMachine.Initialize(&sleeping); 
}

void Leg::Begin()
{
    joint1->Begin();
    joint2->Begin();
    joint3->Begin();
}

void Leg::MoveToPosition(Vector3 position)
{
    LegAngles angles = ik(position);
    if (angles.isValid()) {
        SetAngles(angles);
        return;
    }
    Serial.println("Input angles are not valid");
}

void Leg::SetAngles(LegAngles angles)
{
    if (angles.isSafe()) {
        joint1->WriteAngle(angles.angleJ1);
        joint2->WriteAngle(angles.angleJ2);
        joint3->WriteAngle(angles.angleJ3);
        return;
    }
    Serial.println("Input angles are not safe");
}

void Leg::Update()
{
    if (stateMachine.currentState != nullptr) {
        stateMachine.currentState->Update();
    }
}
