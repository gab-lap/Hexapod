#ifndef LEG_H
#define LEG_H

#include "models.h"
#include "Servos.h"
#include "vectors.h"
#include "StateMachine.h"
#include "EmptyLegState.h"
#include "LegSleepState.h"
#include "LegLiftingState.h"
#include "LegStandingState.h"
#include "LegPushingState.h"

class Leg {
public:
    StateMachine<Leg> stateMachine;
    LegSleepState sleeping;
    LegStandingState standing;
    LegPushingState pushing;
    LegLiftingState lifting;
    VirtualServo *joint1, *joint2, *joint3;
    float legHeight = 0.0f;
    LegPhysicalData physicalData;

    Leg(VirtualServo *j1, VirtualServo *j2, VirtualServo *j3, LegPhysicalData initPhysicalData);
    void Begin();
    void MoveToPosition(Vector3 position);
    void SetAngles(LegAngles angles);
    void Loop();
};

#endif